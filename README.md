# prg1f-io
Input / Output library for the PRG1F course

## Usage

Add to CmakeLists:
```
include(FetchContent) # once in the project to include the module

FetchContent_Declare(prg1f-io
                     GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/prg1f-io.git
                     GIT_TAG        hash)
FetchContent_MakeAvailable(prg1f-io)
```

## Display

### Examples

```c++
#include <thread>
#include "../include/display.h"
#include "../include/input.h"

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

    for(auto& row: grid){
        for(auto& item: row) {
            item =  Display::setTextColor("a", Display::Colors::PINK);
        }
    }
    display.DisplayGrid(grid);
    this_thread::sleep_for(1000ms);

    int age = userInputRange<int>(0, 200, "Quel age as-tu ?", "Mauvais entrée");

    string tmp = "Vous avez " + Display::setTextColor(to_string(age), Display::Colors::RED) + " ans";
    Display::showText(tmp);
    this_thread::sleep_for(1000ms);

    return EXIT_SUCCESS;
}
```

### Images
(Les images ont été prises durant la beta et ne sont pas représentatives du produit final)

![image](https://user-images.githubusercontent.com/46396184/202451747-80dc852e-b7df-4511-9a0b-6907789343b7.png)

![image](https://user-images.githubusercontent.com/46396184/202451486-d65ad651-b26e-4ddf-8b79-2c10e40fdb47.png)
