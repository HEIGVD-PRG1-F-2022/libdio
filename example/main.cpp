#include <libdio/display.h>
#include <libdio/input.h>

using namespace std;

int main() {
    Display display(Display::Colors::PINK);

    Display::showText("Test", Display::Colors::GREEN);

    Display::saveCursorPosition();
    display.setContent("Hello World!\nNext line");
    display.show();

    Display::goBackToCursorPosition();
    display.setTextColor(Display::Colors::BLUE);
    display.setContent("This is blue");
    display.show();

    display.clear();
    display.show("HAL 2000");

    vector<vector<string>> grid(6, vector<string>(6, "0"));
    display.DisplayGrid(grid, false);

    for (auto &row: grid) {
        for (auto &item: row) {
            item = Display::setTextColor("a", Display::Colors::PINK);
        }
    }
    display.DisplayGrid(grid);

    int age = userInputRange<int>("How old are you?", 0, 200, "Bad entry");

    string tmp = "You are " +
                 Display::setTextColor(to_string(age), Display::Colors::RED) +
                 " years old";
    Display::showText(tmp);

    return EXIT_SUCCESS;
}