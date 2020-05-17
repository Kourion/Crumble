#pragma once
#include <iostream>

namespace pld {

    typedef union {
        float flt = 0.0f;
        unsigned char cbt[4];
    }player_points;

    struct Player {
    public:
        player_points points;
        std::string name = "JOLLYWAG";
        std::string crpt_scr = "";
        std::string crpt_nme = "";
        Player() {
            points.flt = 0.0f;
        }
        Player(float points, std::string str) {
            this->points.flt = points;
            name = str;
        }

        std::string getScoreAsCrptStr() const {
            std::string str = "";
            for (unsigned int i = 0; i < 4; i++)
            {
                str += (points.cbt[i] ^ 0b10101100);
            }
            return str;
        }
        void setScoreAsClrFlt() {
            //std::cout << "Scr Flt Size: " << crpt_scr.size() << " -cbt: " << std::endl;
            points.flt = 0.0f;
            for (unsigned int i = 0; i < crpt_scr.size(); i++)
            {
                if (crpt_scr[i] != '\0') { // && i < 4
                    points.cbt[i] = crpt_scr[i];
                    points.cbt[i] ^= 0b10101100;
                }
            }
        }
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
            setScoreAsClrFlt();
            setNameAsClrStr();
        }

        friend std::ostream& operator<<(std::ostream& stream, const Player& obj);
        friend std::istream& operator>>(std::istream& stream, Player& obj);
    };

}