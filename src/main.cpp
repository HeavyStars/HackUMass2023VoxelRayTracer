#include "core/window.hpp"

int main() {
  Window * window;
  window = new Window(800, 600, "window");
  window->run();

  delete window;
  window = NULL;

  return 0;
}