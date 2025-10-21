//final?
#ifndef states_h
#define states_h

#include "state.h"
#include <vector>
#include <fstream>
#include <string>

class states
{
public:
    void load(std::ifstream& definition, bool& valid);
    void view() const;
    int size() const;
    std::string element(int index) const;
    bool is_element(const std::string& state) const;

private:
    std::vector<state> state_list;
};

#endif
