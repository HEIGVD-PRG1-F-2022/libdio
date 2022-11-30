// Original authors:
// - Florian Duruz
// - Aellen Quentin

#ifndef LIBDIO_DISPLAY_H
#define LIBDIO_DISPLAY_H

#include <string>
#include <vector>
#include <iostream>

namespace Display {

    enum class Color {
        WHITE = 15,
        YELLOW = 226,
        ORANGE = 214,
        RED = 196,
        AQUA = 122,
        PINK = 207,
        GREEN = 40,
        BLUE = 21,
        BLACK = 16
    };

    // DString represents a colored string. Upon creation, it is initialised with
    // a white text color.
    class DString {
        std::string out;
        friend std::ostream& operator<<(std::ostream& os, const DString& obj);

    public:
        explicit DString(Color c = Color::WHITE);
        DString& setColor(Color color);

        DString& operator+=(const DString &ds);
        friend DString operator+(DString left, const DString &right);
        DString& operator+=(const std::string &ds);
        friend DString operator+(DString left, const std::string &right);

        DString& operator<<(const DString& obj);
        DString& operator<<(const std::string& obj);
        DString& operator<<(const char obj[]);
        DString& operator<<(const Color& col);
        template<typename T>
        DString& operator<<(T obj);

        // Prints the string and clears DString.
        void print();

        // Resets the string.
        void reset(Color color = Color::WHITE);

        DString& saveCursorPosition();
        DString& goBackToCursorPosition();
        DString& clearScreen();

        // Returns the maximum line-length of this string.
        size_t max_width();
        // Returns the number of lines in this string
        size_t count_lines();
    };

    std::vector<std::string> split(std::string s, std::string sep, size_t max_sep = 0);

    void init();
    void saveCursorPosition();
    void restoreCursorPosition();
    void clearScreen();
    void systemClearScreen();

    template<typename T>
    DString displayGrid(const std::vector<std::vector<T>> &grid, bool show_grid = true);
    template<>
    DString displayGrid<std::string>(const std::vector<std::vector<std::string>> &grid, bool show_grid);
    template<>
    DString displayGrid<DString>(const std::vector<std::vector<DString>> &grid, bool show_grid);
    template<typename T>
    DString displayGrid(const std::vector<std::vector<T>> &grid, std::function<DString(T)> convert, bool show_grid = true);
}

#include "display.tpp"

#endif// LIBDIO_DISPLAY_H
