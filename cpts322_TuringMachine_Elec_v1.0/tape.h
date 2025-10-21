//verified on 4/14
#ifndef tape_h
#define tape_h

#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "direction.h"

#include <string>
#include <fstream>

using namespace std;

class tape
{
private:
    string cells;
    int current_cell;
    char blank_character;

public:
    tape();

    void load(ifstream& definition, bool& valid);

    void validate(const input_alphabet& input_alphabet,
                  const tape_alphabet& tape_alphabet,
                  bool& valid) const;

    void view() const;

    void initialize(string input_string);

    void update(char write_character,
                direction move_direction);

    string left(int maximum_number_of_cells) const;

    string right(int maximum_number_of_cells) const;

    char current_character() const;

    bool is_first_cell() const;

    char get_blank_character() const;

};

#endif
