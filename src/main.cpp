#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

double MS_PER_UPDATE = 16.0;

long getCurrentTime()
{
  clock_t t = clock();
  return t;
}

void processInput()
{
  this_thread::sleep_for(std::chrono::milliseconds(1));
}
void update()
{
  this_thread::sleep_for(std::chrono::milliseconds(1));
}
void render() {
  this_thread::sleep_for(std::chrono::milliseconds(1));
}

bool checkSecond(double time) {
  return (getCurrentTime() - time) > 1000;
}

int main()
{
  double previous = getCurrentTime();
  double startTime = getCurrentTime();
  double lag = 0.0;
  int renderCount = 0;
  int updateCount = 0;
  int processInputCount = 0;

  for( int a = 0; a < 100; a = a + 1 ) {
    double elapsed = getCurrentTime() - previous;
    cout << "elapsed: " << elapsed << "\n";
    cout << "lag(main loop start): " << lag << "\n";
    previous = getCurrentTime();
    lag += elapsed;
    processInput();
    processInputCount++;

    while (lag >= MS_PER_UPDATE && !checkSecond(startTime))
    {
      cout << "lag(update loop): " << lag << "\n";
      update();
      updateCount++;
      lag = lag - MS_PER_UPDATE;
    }

    render();
    renderCount++;

    if(checkSecond(startTime)) {
      cout << "input cycles per second: " << processInputCount << "\n";
      cout << "render cycles per seconds " << renderCount << "\n";
      cout << "update cycles per seconds " << updateCount << "\n";
      processInputCount = 0;
      renderCount = 0;
      updateCount = 0;
      startTime = getCurrentTime();
    }
  }
}