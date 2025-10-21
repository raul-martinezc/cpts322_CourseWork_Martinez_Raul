//verified on 4/14
#include "transition.h"
#include "direction.h"

#include <string>

using namespace std;

transition::transition(string source_state,
                        char read_character,
                        string destination_state,
                        char write_character,
                        direction move_direction):

                        source(source_state),
                        read(read_character),
                        destination(destination_state),
                        write(write_character),
                        move(move_direction)
{

}

string transition::source_state() const
{

    return source;
}


char transition::read_character() const
{
    
    return read;
}

string transition::destination_state() const
{

    return destination;
}

char transition::write_character() const
{

    return write;
}

direction transition::move_direction() const
{

    return move;
}