//
// Project name : LAB 05 - Refactor
// Project members :
// - Florian Duruz
// - Aellen Quentin
//

#ifndef REFACTOR_DISPLAY_H
#define REFACTOR_DISPLAY_H

#include <string>
#include <vector>


class Display {

    const std::string TOP_LEFT_PIPE    = "╔";
    const std::string TOP_RIGHT_PIPE   = "╗";
    const std::string HORIZONTAL_PIPE  = "═";
    const std::string VERTICAL_PIPE    = "║";//(char)186u;
    const std::string BOT_LEFT_PIPE    = "╚";
    const std::string BOT_RIGHT_PIPE   = "╝";

    std::string prefix;
    std::string suffix;
    std::string content;


private:
    std::string drawInBetween(int sizeHorizontal);
    std::string drawTopFrame(int sizeHorizontal);
    std::string drawBottomFrame(int sizeHorizontal);

    static void setTerminalUtf8();

public:
    enum Colors {
        WHITE = 15,
        PINK = 207,
        RED = 196,
        GREEN = 40,
        BLUE = 21,
        BLACK = 16
    };

    explicit Display(Colors defaultTextColor = Colors::WHITE);

    void setTextColor(Colors color);

    static std::string setTextColor(std::string text, Colors color);

    void saveCursorPosition();

    void goBackToCursorPosition();

    void show();

    void show(std::string text);

    static void showText(std::string text, Colors color = Colors::WHITE);

    void setContent(std::string string);

    void clear();

    void DisplayGrid(const std::vector<std::vector<std::string>> &grid, bool border = true, bool insideSeparation = true);
};

#endif // REFACTOR_DISPLAY_H
