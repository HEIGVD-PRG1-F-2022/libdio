#include "display.h"
#include <functional>
#include <vector>

namespace Display {
    using namespace std;

    template<typename T>
    DString &DString::operator<<(T obj) {
        *this += to_string(obj);
        return *this;
    }

    template<typename T>
    DString displayGrid(const vector<vector<T>> &grid, bool show_grid) {
        return displayGridConvert(
                grid, [](T val) -> DString { return to_string(val); }, show_grid);
    }

    template<typename T>
    DString displayGridConvert(const vector<vector<T>> &grid, function<DString(T)> convert, bool show_grid) {
        vector<vector<DString>> out;
        for (const auto &line: grid) {
            vector<DString> line_out(line.size());
            for (size_t pos = 0; pos < line.size(); pos++) {
                line_out.at(pos) = convert(line.at(pos));
            }
            out.push_back(line_out);
        }
        return displayGrid<DString>(out, show_grid);
    }
}// namespace Display