// Original authors:
// - Florian Duruz
// - Aellen Quentin

#include <cstdlib>
#include <iostream>
#include <regex>
#include <utility>

#ifdef _WIN32

#include <windows.h>

int enableVirtualTerminalProcessing() {

    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(stdOut, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (SetConsoleMode(stdOut, mode)) { return 0; }
        }
    }

    return GetLastError();
}

#endif

#include "libdio/display.h"

using namespace std;

const string TOP_LEFT_PIPE = "╔";
const string TOP_RIGHT_PIPE = "╗";
const string HORIZONTAL_PIPE = "═";
const string HORIZONTAL_UP_PIPE = "╩";
const string HORIZONTAL_DOWN_PIPE = "╦";
const string VERTICAL_PIPE = "║";
const string VERTICAL_LEFT_PIPE = "╣";
const string VERTICAL_RIGHT_PIPE = "╠";
const string BOT_LEFT_PIPE = "╚";
const string BOT_RIGHT_PIPE = "╝";
const string CROSS_PIPE = "╬";

const string CSI = "\x1b[";

namespace Display {

    // Removes all ANSI sequences for counting characters.
    string nonANSI(const string &s);

    // Splits a string along the 'sep' string in as many pieces as possible.
    vector<string> split(const string &s, const string &sep);

    DString::DString(const std::string &s) { this->assign(s); }

    DString::DString(Display::Color c) { setColor(c); }

    DString &DString::setColor(Color color) {
        *this += CSI + "38;5;" + to_string(int(color)) + "m";
        return *this;
    }

    DString &DString::operator<<(const DString &obj) {
        *this += obj;
        return *this;
    }
    DString &DString::operator<<(const std::string &obj) {
        *this += obj;
        return *this;
    }
    DString &DString::operator<<(const char obj[]) {
        *this += obj;
        return *this;
    }
    DString &DString::operator<<(const char obj) {
        *this += obj;
        return *this;
    }
    DString &DString::operator<<(const Color &col) {
        setColor(col);
        return *this;
    }

    DString &DString::print() {
        cout << *this;
        reset();
        return *this;
    }

    DString &DString::reset(Color color) {
        clear();
        setColor(color);
        return *this;
    }

    DString &DString::resetColor() { return *this << CSI + "0m"; }

    DString &DString::saveCursorPosition() {
        // While the first is the official ANSI code for saving the cursor position,
        // the latter works in most unix terminals, but not MacOS.
#ifdef __WIN32__
        *this += CSI + "s";
#elif __linux__
        *this += "\x1b"
                 "7";
#endif
        return *this;
    }

    DString &DString::goBackToCursorPosition() {
// While the first is the official ANSI code for restoring the cursor position,
// the latter works in most unix terminals, but not MacOS.
#ifdef __WIN32__
        *this += CSI + "u";
#elif __linux__
        *this += "\x1b"
                 "8";
#endif
        return *this;
    }

    DString &DString::clearScreen() {
        *this += CSI + "2J" + CSI + "H";
        return *this;
    }

    DString &DString::cursorHome() {
        *this += CSI + "H";
        return *this;
    }

    DString &DString::cursorVisible(bool visible) {
        *this += CSI + "?25"s + (visible ? "h" : "l");
        return *this;
    }

    DString &DString::cursorDelete(LineDelete position) {
        *this += CSI + to_string(int(position)) + "K";
        return *this;
    }

    DString &DString::cursorMove(size_t steps, char dir) {
        *this += CSI + (steps != 1 ? to_string(int(steps)) : "") + dir;
        return *this;
    }

    DString &DString::cursorUp(size_t lines) { return cursorMove(lines, 'A'); }

    DString &DString::cursorDown(size_t lines) { return cursorMove(lines, 'B'); }

    DString &DString::cursorForward(size_t columns) { return cursorMove(columns, 'C'); }

    DString &DString::cursorBack(size_t columns) { return cursorMove(columns, 'D'); }

    DString &DString::cursorNextLine(size_t lines) { return cursorMove(lines, 'E'); }

    DString &DString::cursorPreviousLine(size_t lines) { return cursorMove(lines, 'F'); }

    DString &DString::cursorHorizontalAbsolute(size_t column) { return cursorMove(column, 'G'); }

    DString &DString::cursorPosition(size_t x, size_t y) {
        *this += CSI + (y != 1 ? to_string(int(y)) : "") + ";" + (x != 1 ? to_string(int(x)) : "") + "H";
        return *this;
    }


    size_t DString::max_width() const {
        size_t max_width = 0;
        for (const auto &line: split(*this, "\n")) { max_width = max(max_width, nonANSI(line).size()); }
        return max_width;
    }

    size_t DString::count_lines() const {
        return size_t(std::count_if(begin(), end(), [](char c) -> bool { return c == '\n'; }));
    }

    vector<string> split(const string &s, const string &sep) {
        vector<string> ret;
        size_t last = 0;
        size_t next = 0;
        while ((next = s.find(sep, last)) != string::npos) {
            ret.push_back(s.substr(last, next - last));
            last = next + 1;
        }
        ret.push_back(s.substr(last));
        return ret;
    }

    // Returns the string without any ANSI sequences
    string nonANSI(const string &s) { return regex_replace(s, regex("\x1b.*?[a-zA-Z]"), ""); }

    void init() {
#ifdef _WIN32
        enableVirtualTerminalProcessing();
        SetConsoleOutputCP(CP_UTF8);
#endif
    }

    void systemClearScreen() {
#ifdef _WIN32
        system("cls");
#elif __unix__
        system("clear");
#endif
    }

    void saveCursorPosition() { DString().saveCursorPosition().print(); }

    void restoreCursorPosition() { DString().goBackToCursorPosition().print(); }

    void clearScreen() { DString().clearScreen().print(); }

    string drawFrame(string first, const string &middle, const string &last, const string &space, size_t cells, size_t width) {
        string line = move(first);
        string spaces;
        for (size_t i = 0; i <= width + 1; i++) { spaces += space; }
        for (size_t i = 1; i < cells; i++) { line += spaces + middle; }
        return line + spaces + last;
    }

    string drawInBetween(size_t cells, size_t width) {
        return drawFrame(VERTICAL_RIGHT_PIPE, CROSS_PIPE, VERTICAL_LEFT_PIPE, HORIZONTAL_PIPE, cells, width);
    }

    string drawTopFrame(size_t cells, size_t width) {
        return drawFrame(TOP_LEFT_PIPE, HORIZONTAL_DOWN_PIPE, TOP_RIGHT_PIPE, HORIZONTAL_PIPE, cells, width);
    }

    string drawBottomFrame(size_t cells, size_t width) {
        return drawFrame(BOT_LEFT_PIPE, HORIZONTAL_UP_PIPE, BOT_RIGHT_PIPE, HORIZONTAL_PIPE, cells, width);
    }

    template<>
    DString displayGrid<DString>(const vector<vector<DString>> &grid, bool show_grid) {
        size_t max_width = 0, max_height = 0;
        for (const auto &line: grid) {
            for (const auto &cell: line) {
                max_width = max(max_width, cell.max_width());
                max_height = max(max_height, cell.count_lines());
            }
        }
        size_t cells = grid[0].size();

        DString out;

        if (show_grid) { out << drawTopFrame(cells, max_width) + "\n"; }

        for (size_t y = 0; y < grid.size(); ++y) {
            if (show_grid) {
                if (y != 0) { out << drawInBetween(cells, max_width) + "\n"; }
                out << Color::WHITE << VERTICAL_PIPE << " ";
            }
            for (size_t x = 0; x < grid.at(0).size(); ++x) {
                const DString &cell = grid.at(y).at(x);
                string filler(max_width - cell.max_width() + 1, ' ');
                out << cell << filler;
                if (show_grid && x != grid.at(0).size() - 1) { out << Color::WHITE << VERTICAL_PIPE << " "; }
            }
            if (show_grid) { out << Color::WHITE << VERTICAL_PIPE; }
            out << "\n";
        }

        if (show_grid) { out << drawBottomFrame(cells, max_width) + "\n"; }
        return out;
    }

    template<>
    DString displayGrid<string>(const vector<vector<string>> &grid, bool show_grid) {
        return displayGridConvert<string>(
                grid, [](const string &val) -> DString { return DString() << val; }, show_grid);
    }
}// namespace Display

Display::DString getDStringColored(const char *s, size_t len, Display::Color color) {
    Display::DString d;
    d.setColor(color);
    d.append(string(s, s + len));
    return d;
}

Display::DString operator"" _white(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::WHITE); }

Display::DString operator"" _yellow(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::YELLOW); }

Display::DString operator"" _orange(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::ORANGE); }

Display::DString operator"" _red(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::RED); }

Display::DString operator"" _aqua(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::AQUA); }

Display::DString operator"" _pink(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::PINK); }

Display::DString operator"" _green(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::GREEN); }

Display::DString operator"" _blue(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::BLUE); }

Display::DString operator"" _black(const char *s, size_t len) { return getDStringColored(s, len, Display::Color::BLACK); }