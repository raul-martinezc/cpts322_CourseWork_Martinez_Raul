//final?
#include <iostream>
#include <string>
#include <cctype>  // for toupper, tolower, isalnum, isspace

using namespace std;

// Returns a trimmed copy of the input string
string trim(const string& str, const string& whitespace = " \t")
{
    const size_t str_begin = str.find_first_not_of(whitespace);
    if (str_begin == string::npos)
        return "";  // no content

    const size_t str_end = str.find_last_not_of(whitespace);
    const size_t str_range = str_end - str_begin + 1;

    return str.substr(str_begin, str_range);
}

// Returns a copy of the string in uppercase
string to_uppercase_copy(const string& input)
{
    string result = input;
    for (char& c : result)
        c = toupper(c);
    return result;
}

// Returns a copy of the string in lowercase
string to_lowercase_copy(const string& input)
{
    string result = input;
    for (char& c : result)
        c = tolower(c);
    return result;
}

// Keeps only alphanumeric and whitespace characters in a string
string keep_alphanumeric_whitespace(const string& input)
{
    string result;
    for (char c : input)
    {
        if (isalnum(c) || isspace(c))
            result += c;
    }
    return result;
}
