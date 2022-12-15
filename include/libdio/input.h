#ifndef LIBDIO_INPUT_H
#define LIBDIO_INPUT_H

#include <string>

/**
 * User input
 * @param msg message to display to the user
 * @param err error message in case of wrong type
 */
template<typename T>
T userInput(const std::string &msg, const std::string &err = "Wrong type, please retry");

/**
 * User input with range clamp. This function will not return a value lower than
 * min and higher than max.
 * @param msg message to display to the user
 * @param min minimum value, inclusive
 * @param max maximum value, inclusive
 * @param err error message in case of wrong type
 */
template<typename T>
T userInputRange(const std::string &msg, T min, T max, const std::string &bad_range, const std::string &err = "Wrong type, please retry");

#include "../../src/input.tpp"

#endif
