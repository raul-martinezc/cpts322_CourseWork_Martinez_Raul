//final?
#ifndef uppercase_h
#define uppercase_h

#include <string>
#include <algorithm>

// Core implementation
inline std::string to_uppercase_string(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), ::toupper);
    return value;
}

// Aliases for compatibility
inline std::string uppercase_string(std::string value) { return to_uppercase_string(value); }

#endif