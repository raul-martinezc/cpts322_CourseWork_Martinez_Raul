//final?
#ifndef string_play_h
#define string_play_h

#include <string>
#include <cctype>

// Trims whitespace from both ends of the input string
std::string trim(const std::string& str, const std::string& whitespace = " \t");

// Returns a new string converted to uppercase
std::string to_uppercase_copy(const std::string& input);

// Returns a new string converted to lowercase
std::string to_lowercase_copy(const std::string& input);

// Returns a new string with only alphanumeric and whitespace characters
std::string keep_alphanumeric_whitespace(const std::string& input);

#endif
