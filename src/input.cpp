#include <iostream>
#include <limits>
#include <string>

template<typename T>
T userInputRange(std::string msg, T min, T max, std::string err="Wrong type, please retry") {
    T val = userInput(msg, err);
    val = std::clamp(val, min, max);
    
    return val;
}

template<typename T>
T userInput(std::string msg, std::string err="Wrong type, please retry") {
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