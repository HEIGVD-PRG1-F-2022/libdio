#include <functional>
#include <libdio/display.h>
#include <libdio/input.h>
#include <thread>
#include <vector>

using namespace std;

int main() {
    Display::init();

    Display::DString display(Display::Color::PINK);
    Display::systemClearScreen();
    display.clearScreen();
    display << "Test\n";
    display.print();

    display.setColor(Display::Color::GREEN) << "In green\n";
    display.print();

    Display::saveCursorPosition();
    display << "Hello World!\nNext line\n";
    display.print();

    this_thread::sleep_for(1000ms);

    Display::restoreCursorPosition();
    display.setColor(Display::Color::RED);
    display << "Goodbye world!\nThis is red\n";
    display.print();

    display << "HAL 2000\n";
    cout << display;

    cout << "I'im red"_red << endl;
    cout << "I'im green"_green << endl;

    cout << Display::DString()
                    .cursorHorizontalAbsolute(8)
                    .append("Tab at 8")
                    .cursorDown()
                    .cursorBack(4)
                    .append("Below to the left")
                    .cursorNextLine(2)
                    .append("Down and a text that will be deleted")
                    .cursorHorizontalAbsolute(1)
                    .cursorForward(4)
                    .cursorDelete(Display::DString::LineDelete::TO_END)
         << endl;
    vector<vector<string>> grid(3, vector<string>(3, "0"));
    cout << Display::displayGrid(grid, false);

    grid.at(1).at(1) = "11";
    Display::displayGridConvert<string>(grid, [](const string &s) -> Display::DString {
        return Display::DString(s == "11" ? Display::Color::GREEN : Display::Color::RED) << s;
    }).print();

    int age = userInputRange<int>("How old are you?", 0, 200, "Bad entry");

    cout << (Display::DString() << "You are " << Display::Color::RED << age << Display::Color::WHITE << " years old\n");

    return EXIT_SUCCESS;
}