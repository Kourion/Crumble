#include <iostream>
#include "Player.h"
#include "Random.h"

//#############################################################################
//# IO stream operators for "Player" object.                                  #
//#############################################################################

namespace pld {

std::ostream& operator<<(std::ostream& stream, const pld::Player& obj)
{
    //This formating here with endl is needed.
    stream << obj.score << "\0" << std::endl;
    stream << obj.getNameAsCrptStr();
    return stream;
}

std::istream& operator>>(std::istream& stream, pld::Player& obj)
{
    stream >> obj.score; //obj.score.flt;
    stream >> obj.crpt_nme; //obj.name; 

    return stream;
}
