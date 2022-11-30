#include <functional>
#include <libdio/display.h>
#include <libdio/input.h>
#include <thread>
#include <vector>

using namespace std;

int main() {
    Display::init();

    Display::DString display(Display::Color::PINK);
    display += "Test\n";
    display.print();

    display.setColor(Display::Color::GREEN) += "In green\n";
    display.print();

    Display::saveCursorPosition();
    display += "Hello World!\nNext line\n";
    display.print();

    this_thread::sleep_for(1000ms);

    Display::restoreCursorPosition();
    display.setColor(Display::Color::RED);
    display += "This is red\n";
    display.print();

    display.clearScreen();
    display << "HAL 2000\n";
    cout << display;

    vector<vector<string>> grid(3, vector<string>(3, "0"));
    cout << Display::displayGrid(grid, false);

    grid.at(1).at(1) = "11";
    Display::displayGrid(grid, function<Display::DString(string)>([](string s) -> Display::DString {
                             return Display::DString(s == "11" ? Display::Color::GREEN : Display::Color::RED) << s;
                         }))
            .print();

    int age = userInputRange<int>("How old are you?", 0, 200, "Bad entry");

    cout << (Display::DString() << "You are " << Display::Color::RED << age << Display::Color::WHITE << " years old\n");

    return EXIT_SUCCESS;
}