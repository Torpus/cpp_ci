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
  this_thread::sleep_for(std::chrono::milliseconds(3));
  cout << "processInput()\n";
}
void update()
{
  this_thread::sleep_for(std::chrono::milliseconds(0));
  cout << "update()\n";
}
void render(double lag) {
  this_thread::sleep_for(std::chrono::milliseconds(4));
  cout << "render()\n";
}

int main()
{
  double previous = getCurrentTime();
  double lag = 0.0;
  for( int a = 0; a < 10; a = a + 1 ) {  {
    double current = getCurrentTime();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;
    cout << "lag: " << lag;
    cout <<"ms_per_update: " << MS_PER_UPDATE << "\n";
    processInput();

    while (lag >= MS_PER_UPDATE)
    {
      update();
      lag -= MS_PER_UPDATE;
    }

    render(lag / MS_PER_UPDATE);
  }
}