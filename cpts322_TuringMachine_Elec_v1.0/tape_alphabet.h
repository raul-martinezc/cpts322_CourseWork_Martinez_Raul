//final?
#ifndef tape_alphabet_h
#define tape_alphabet_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class tape_alphabet
{
private:
    vector<char> alphabet;

public:
    void load(ifstream & definition, bool & valid);
    void view() const;
    bool is_element(const char & value) const;
};

#endif
