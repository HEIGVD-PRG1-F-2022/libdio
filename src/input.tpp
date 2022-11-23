#include <iostream>
#include <limits>
#include <string>

template<typename T>
T userInputRange(std::string msg, T min, T max, std::string err) {
    T val;
    while (true) {
        val = userInput<T>(msg, err);
        if (val >= min && val <= max) {
            return val;
        }
        std::cout << err << std::endl;
    }
}

template<typename T>
T userInput(const std::string &msg, const std::string &err) {
    T x;
    std::cout << msg << std::endl;
    while (true) {
        if (std::cin >> x) {
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << err << std::endl;
        }
    }
    return x;
}
