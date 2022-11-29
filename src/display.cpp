// Original authors:
// - Florian Duruz
// - Aellen Quentin

#include <iostream>
#include <utility>
#include <stdlib.h>

#ifdef _WIN32

#include <windows.h>

int enableVirtualTerminalProcessing() {

  HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  if (stdOut != INVALID_HANDLE_VALUE) {
    DWORD mode = 0;
    if (GetConsoleMode(stdOut, &mode)) {
      mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      if (SetConsoleMode(stdOut, mode)) {
        return 0;
      }
    }
  }

  return GetLastError();
}
#endif

#include "../include/display.h"

void Display::setTerminalUtf8() {
#ifdef _WIN32
    enableVirtualTerminalProcessing();
    SetConsoleOutputCP(CP_UTF8);
#endif
}

Display::Display(Colors defaultTextColor) {
    Display::setTerminalUtf8();
    this->setTextColor(defaultTextColor);
}

void Display::setTextColor(Display::Colors color) {
    this->prefix = "\x1b[38;5;" + std::to_string(color) + "m";
    this->suffix = "\x1b[0m";
}

void Display::saveCursorPosition() { std::cout << "\033[s"; }

void Display::goBackToCursorPosition() { std::cout << "\033[u"; }

void Display::show() {
    std::cout << this->prefix << this->content << this->suffix << std::endl;
}

void Display::show(std::string text) {
    setContent(std::move(text));
    show();
}

void Display::showText(std::string text, Display::Colors color) {
    Display::setTerminalUtf8();
    std::cout << Display::setTextColor(std::move(text), color) << std::endl;
}

void Display::setContent(std::string string) {
    this->content = std::move(string);
}

void Display::clear() {
#ifdef _WIN32
    system("cls");
#elif __unix__
    system("clear");
#endif
}

std::string Display::drawInBetween(size_t sizeHorizontal) {
    std::string line;
    line.append(VERTICAL_RIGHT_PIPE);
    for (size_t i = 1; i < sizeHorizontal; ++i) {
        if (i % 4 != 0)
            line.append(HORIZONTAL_PIPE);
        else
            line.append("╬");
    }
    line.append(VERTICAL_LEFT_PIPE);
    return line;
}

std::string Display::drawTopFrame(size_t sizeHorizontal) {
    std::string line;
    line.append(TOP_LEFT_PIPE);

    for (size_t i = 1; i < sizeHorizontal; ++i) {
        if (i % 4 != 0)
            line.append(HORIZONTAL_PIPE);
        else
            line.append(HORIZONTAL_DOWN_PIPE);
    }
    line.append(TOP_RIGHT_PIPE);
    return line;
}

std::string Display::drawBottomFrame(size_t sizeHorizontal) {
    std::string line;
    line.append(BOT_LEFT_PIPE);

    for (size_t i = 1; i < sizeHorizontal; ++i) {
        if (i % 4 != 0)
            line.append(HORIZONTAL_PIPE);
        else
            line.append(HORIZONTAL_UP_PIPE);
    }
    line.append(BOT_RIGHT_PIPE);
    return line;
}

void Display::DisplayGrid(const std::vector<std::vector<std::string>> &grid,
                          bool border, bool insideSeparation) {
    size_t horizontalSize = grid[0].size() * 4;

    if (border) {
        std::cout << drawTopFrame(horizontalSize) << std::endl;
    }
    for (size_t y = 0; y < grid.size(); ++y) {
        if (border) {
            if (y != 0) {
                std::cout << drawInBetween(horizontalSize) << std::endl;
            }
            std::cout << VERTICAL_PIPE << ' ';
        }
        for (size_t x = 0; x < grid.at(0).size(); ++x) {
            if (!grid.at(y).at(x).empty()) {
                std::cout << grid.at(y).at(x);
            } else {
                std::cout << " ";
            }
            if (insideSeparation) {
                if (border && x != grid.at(0).size() - 1)
                    std::cout << ' ' << VERTICAL_PIPE << ' ';
                else
                    std::cout << ' ';
            }
        }
        if (border) {
            std::cout << VERTICAL_PIPE;
        }
        std::cout << std::endl;
    }
    if (border) {
        std::cout << drawBottomFrame(horizontalSize) << std::endl;
    }
}

std::string Display::setTextColor(std::string text, Display::Colors color) {
    text = "\x1b[38;5;" + std::to_string(color) + "m" + text + "\x1b[0m";
    return text;
}
