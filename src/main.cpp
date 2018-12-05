#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

double MS_PER_UPDATE = 16.0;

long getCurrentTime()
{
  return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void initializeGame()
{
  // TODO do stuff
}

void processInput()
{
  this_thread::sleep_for(chrono::milliseconds(2));
}

void update()
{
  this_thread::sleep_for(chrono::milliseconds(5));
}

void render()
{
  this_thread::sleep_for(chrono::milliseconds(6));
}

bool checkSecond(double time)
{
  return (getCurrentTime() - time) > 1000;
}

void gameLoop()
{
  long previous = getCurrentTime();
    long startTime = getCurrentTime();
    double lag = 0.0;
    int renderCount = 0;
    int updateCount = 0;
    int processInputCount = 0;

    for(int a = 0; a < 1000; a = a + 1)
    {
      long elapsed = getCurrentTime() - previous;
      previous = getCurrentTime();
      lag += elapsed;
      processInput();
      processInputCount++;

      while (lag >= MS_PER_UPDATE)
      {
        update();
        updateCount++;
        lag -= MS_PER_UPDATE;
      }

      render();
      renderCount++;

      if(checkSecond(startTime))
      {
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

int main()
{
  initializeGame();
  gameLoop();
}