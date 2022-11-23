# prg1f-io

Input / Output library for the PRG1F course

## Usage

Until we understand how to use `FetchContent` from CMakeFiles, you will have to do the following:
In your working directory, make a clone of the library:

```bash
git clone https://github.com/HEIGVD-PRG1-F-2022/prg1f-io
```

And add `prg1f-io/src/display.cpp` to your `add_executable` in your `CmakeLists.txt`.
Now you can use

```c++
#include "prg1f-io/include/display.h"
#include "prg1f-io/include/input.h"
```

in your code.

## Display

### Examples

```c++
#include <thread>
#include "prg1f-io/include/display.h"
#include "prg1f-io/include/input.h"

using namespace std;

int main() {
  Display display(Display::Colors::PINK);

  Display::showText("Test", Display::Colors::GREEN);
  this_thread::sleep_for(1000ms);

  display.saveCursorPosition();
  display.setContent("Hello World!\nteste");
  display.show();
  this_thread::sleep_for(1000ms);

  display.goBackToCursorPosition();
  display.setTextColor(Display::Colors::BLUE);
  display.setContent("bouh");
  display.show();
  this_thread::sleep_for(1000ms);

  display.clear();
  display.show("MAMA");
  this_thread::sleep_for(1000ms);

  vector<vector<string>> grid(6, vector<string>(6, "0"));
  display.DisplayGrid(grid);
  this_thread::sleep_for(1000ms);

  for (auto &row : grid) {
    for (auto &item : row) {
      item = Display::setTextColor("a", Display::Colors::PINK);
    }
  }
  display.DisplayGrid(grid);
  this_thread::sleep_for(1000ms);

  int age = userInputRange<int>("Quel age as-tu ?", 0, 200, "Mauvais entrée");

  string tmp = "Vous avez " +
               Display::setTextColor(to_string(age), Display::Colors::RED) +
               " ans";
  Display::showText(tmp);
  this_thread::sleep_for(1000ms);

  return EXIT_SUCCESS;
}
```

### Images

(Les images ont été prises durant la beta et ne sont pas représentatives du produit final)

![image](https://user-images.githubusercontent.com/46396184/202451747-80dc852e-b7df-4511-9a0b-6907789343b7.png)

![image](https://user-images.githubusercontent.com/46396184/202451486-d65ad651-b26e-4ddf-8b79-2c10e40fdb47.png)
