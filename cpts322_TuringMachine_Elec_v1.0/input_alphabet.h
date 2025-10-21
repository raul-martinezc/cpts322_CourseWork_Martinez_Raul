//final?
#ifndef input_alphabet_h
#define input_alphabet_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class input_alphabet
{
private:
    std::vector<char> alphabet;

public:
    void load(std::ifstream& definition, bool& valid);
    void view() const;
    bool is_element(const char& value) const;
};

#endif

