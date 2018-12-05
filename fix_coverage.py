import argparse
import subprocess

def demangle(symbol):
    return subprocess.check_output(['c++filt', '-n', symbol.strip()]).decode().strip()

def filter_lcov(lines, verbose=False):
    defs, srcfile = {}, ''
    for line in lines:
        if line.startswith('SF:'):
            defs = {}
            srcfile = line[3:].strip()
        elif line.startswith('end_of_record'):
            defs = {}
        elif line.startswith('FN:'):
            lineno, symbol = line[3:].split(',')
            defs[lineno] = demangle(symbol)
        elif line.startswith('DA:'):
            lineno = line[3:].split(',')[0]
            if lineno in defs:
                if verbose:
                    print(f'Ignoring: {srcfile}:{lineno}:{defs[lineno]}')
                continue
        yield line

def main():
    p = argparse.ArgumentParser()
    p.add_argument('input', type=str)
    p.add_argument('output', type=str)
    p.add_argument('--verbose', '-v', action='store_true')
    args = p.parse_args()
    with open(args.input, 'r') as fin:
        lines = list(fin)
    with open(args.output, 'w') as fout:
        for line in filter_lcov(lines, verbose=args.verbose):
            fout.write(line)

if __name__ == '__main__':
    main()