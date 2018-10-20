#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

double MS_PER_UPDATE = 16.0;

long getCurrentTime()
{
  clock_t t;
  t = clock();
  return t;
}

void processInput()
{
  this_thread::sleep_for(std::chrono::milliseconds(1));
}
void update()
{
  this_thread::sleep_for(std::chrono::milliseconds(3));
}
void render() {
  this_thread::sleep_for(std::chrono::milliseconds(3));
}

int main()
{
  double previous = getCurrentTime();
  double startTime = getCurrentTime();
  double lag = 0.0;
  int renderCount = 0;
  int updateCount = 0;
  int processInputCount = 0;

  for( int a = 0; a < 1000; a = a + 1 ) {
    double current = getCurrentTime();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;
    cout << "lag: " << lag << "\n";
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
    if( getCurrentTime() - startTime > 1000) {
      cout << "input cycles per second: " << processInputCount << "\n";
      cout << "render cycles per seconds " << renderCount;
      cout << "update cycles per seconds " << updateCount;
      processInputCount = 0;
      renderCount = 0;
      updateCount = 0;
    }
  }
}