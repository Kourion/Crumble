#include <iostream>
#include "Player.h"
#include "Random.h"

//#############################################################################
//# IO stream operators for "Player" object.                                  #
//#############################################################################

std::ostream& pld::operator<<(std::ostream& stream, const Player& obj)
{
    //This formating here with endl is needed.
    stream << obj.getScoreAsCrptStr() << "\0" << std::endl;
    stream << obj.getNameAsCrptStr();
    return stream;
}

std::istream& pld::operator>>(std::istream& stream, Player& obj)
{
    stream >> obj.crpt_scr; //obj.score.flt;
    stream >> obj.crpt_nme; //obj.name; 

    return stream;
}