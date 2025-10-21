#include "tape.h"
#include "direction.h"
#include "crash.h"

#include <exception>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const int success = 0;

    tape test_tape;
    test_tape.initialize("AABB");

    try
    {
        test_tape.update('B', 'L');
    }
    catch (crash & error)
    {
        cout << error.what() << ".\n";
    }
    catch (bad_alloc &)
    {
        cout << "Allocation error!\n";
    }
    catch (...)
    {
        cout << "Something went wrong!\n";
    }

    test_tape.view();

    return success;
}
