#ifndef INPUT_HEADER
#define INPUT_HEADER

#include <string>

/**
 * User input
 * @param msg message to display to the user
 * @param err error message in case of wrong type
 * 
*/
template<typename T>
T userInput(std::string msg, std::string err = "Wrong type, please retry");

/**
 * User input with range clamp. This function will not return a value lower than min 
 * and higher than max.
 * @param msg message to display to the user
 * @param min
 * @param max
 * @param err error message in case of wrong type
*/
template<typename T>
T userInputRange(std::string msg, T min, T max, std::string err = "Wrong type, please retry");

#include "../src/input.tpp"

#endif
