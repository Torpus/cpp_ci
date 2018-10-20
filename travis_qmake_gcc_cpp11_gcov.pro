SOURCES += main.cpp

QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# C++11
QMAKE_CXX = g++-7
QMAKE_LINK = g++-7
QMAKE_CC = gcc-7
QMAKE_CXXFLAGS += -std=c++11