#pragma once
#include <iostream>

//#############################################################################
//# Player class, represents the player, does IO pre and post processing:     #
//#############################################################################

namespace pld {

    struct Player {
    public:
        float score;
        std::string name = "JOLLYWAG";
        std::string crpt_scr = "";
        std::string crpt_nme = "";
        Player() {
            score = 0.0f;
        }
        Player(float score_, std::string name_) {
            this->score = score_;
            this->name = name_;
        }

        //std::string getScoreAsCrptStr() const {
        //    std::string str = "";
        //    for (unsigned int i = 0; i < 4; i++)
        //    {
        //        str += (points.cbt[i] ^ 0b10101100);
        //    }
        //    return str;
        //}
        //void setScoreAsClrFlt() {
        //    //std::cout << "Scr Flt Size: " << crpt_scr.size() << " -cbt: " << std::endl;
        //    points.flt = 0.0f;
        //    for (unsigned int i = 0; i < crpt_scr.size(); i++)
        //    {
        //        if (crpt_scr[i] != '\0') { // && i < 4
        //            points.cbt[i] = crpt_scr[i];
        //            points.cbt[i] ^= 0b10101100;
        //        }
        //    }
        //}
        std::string getNameAsCrptStr() const {
            std::string str = "";
            for (unsigned int i = 0; i < name.size(); i++)
            {
                str += (name[i] ^ 0b10101100);
            }
            return str;
        }
        void setNameAsClrStr() {
            name = "";
            for (unsigned int i = 0; i < crpt_nme.size(); i++)
            {
                name += (crpt_nme[i] ^ 0b10101100);
            }
        }

        void updateNmeScr() {
            //setScoreAsClrFlt();
            setNameAsClrStr();
        }

        friend std::ostream& operator<<(std::ostream& stream, const Player& obj);
        friend std::istream& operator>>(std::istream& stream, Player& obj);
    };

}
