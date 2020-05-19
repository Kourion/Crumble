#include <iostream>
#include <fstream>
#include "Core.h"
#include "Reverse.h"

//#############################################################################
//# Highscoore loop handler and load/save functions:                          #
//#############################################################################

pld::State pld::Core::onUserUpdateHighscore(float elapsed_time) {
    if (level.game_over || score.init) {
        score.init = false;
        score.has_printed = false;
        score.entries.clear();
        if (level.player1.name != "") {
            score.entries.insert(std::pair<float, std::string>(level.player1.points.flt, level.player1.name));
        }
        loadHighscorePresets();
        //std::string str_flt = "";
        //str_flt = player1.getScoreAsCrptStr();
        //std::cout << "flt/str/flt: " << player1.score.flt << " - " << str_flt << " - " << player1.getScoreAsClrFlt(str_flt) << std::endl;

        std::ifstream reader;
        reader.open("score.dat", std::ios::in | std::ios::binary);
        if (!reader) {
            std::cerr << "Score file missing, read failure!" << std::endl;
        }
        else {
            Player p;
            //std::cout << "Reader start... " << std::endl;
            while (reader >> p) {
                p.updateNmeScr();
                //std::cout << "Reader: " << p.name << " -> " << p.score.flt << std::endl;
                std::pair<float, std::string> entry(p.points.flt, p.name);
                score.entries.insert(entry);
            }
        }
        reader.close();

        std::ofstream writer;
        writer.open("score.dat", std::ios::out | std::ios::binary | std::ios::trunc);
        if (!writer) {
            std::cerr << "Score file missing, write failure!" << std::endl;
        }
        else {
            for (auto const& [points, name] : score.entries ) {
                //std::cout << "Writer: " << name << " -> " << points << std::endl;
                writer << Player(points, name) << std::endl;
            }
        }
        writer.close();
        //std::cout << "----------------------" << std::endl;
    }
    return showHighscore(elapsed_time);
}

pld::State pld::Core::showHighscore(float fElapsedTime) {
    pld::State next = pld::State::Highscore;
    level.game_over = false;
    
    // MEDO: Highscore table
    float align_x = (float)(ScreenWidth() / 2 - 331.5 * getGlobalScale().x);
    float align_y = 48 * getGlobalScale().y;
    olc::vf2d title_text_pos(align_x, align_y);//ScreenHeight() / 3 - ScreenHeight() / 5 - ScreenHeight() / 10);
    DrawDecal(title_text_pos, dcl_text->at(1).get(), getGlobalScale());
    align_y += ((50 + 140) * getGlobalScale().y);
    olc::vf2d hsc_txt_pos(ScreenWidth() / 2 - (515 / 2) * getGlobalScale().x, align_y);
    //515x88
    DrawDecal(hsc_txt_pos, dcl_text->at(3).get(), getGlobalScale());
    // Adjust y between highscore-title and first entry.
    align_y += (140 * getGlobalScale().y);
    //if (!has_printed_highscore) {
    //    has_printed_highscore = true;
    //
    //   // Print to console:
    //   std::cout << "Printer: " << name << " -> " << points << std::endl;
    //}

    int i = 1;
    int player1_pos = 0;
    float player1_y = align_y;
    //align_x -= 50 * getGlobalScale().x;
    for (auto const& [points, name] : reverse(score.entries) ) {
        // MEDO: print to highscore table.
        std::string entry = getScoreEntry(i, points, name);
        if (i < 11) {
            DrawStringDecal({ align_x, align_y }, entry, olc::Pixel(246, 198, 55), { 3.5f * getGlobalScale().x, 4.5f * getGlobalScale().y });
        }
        if (points == level.player1.points.flt && name == level.player1.name) {
            player1_pos = i;
        }

        i++;
        // Adjust y between each entry.
        align_y += (50 * getGlobalScale().y);
    }
    player1_y += ((520) * getGlobalScale().y);
    DrawStringDecal({ align_x, player1_y }, getScoreEntry(player1_pos, level.player1.points.flt, level.player1.name),
        olc::Pixel(246, 198, 55), { 3.5f * getGlobalScale().x, 4.5f * getGlobalScale().y });

    align_y = player1_y + (50 * getGlobalScale().y);

    next = buttonResign({ align_x, align_y }, {0.5f, 0.5f}, fElapsedTime, next, 6);
    next = buttonRestart({ align_x + 18 * tiles.size * 0.5f, align_y }, { 0.5f, 0.5f }, fElapsedTime, next, 7);

    // MEDO: Give choice between play again and titlescreen.
    if (GetKey(olc::ESCAPE).bPressed) {
        this->escaped_from_state = pld::State::Highscore;
        return pld::State::Settings;
    }
    if (GetKey(olc::T).bPressed) {
        reportStateChange();
        return pld::State::Titlescreen;
    }
    if (GetKey(olc::L).bPressed) {
        reportStateChange();
        return pld::State::Level;
    }
    return next;
}

void pld::Core::loadHighscorePresets() {
    for (Player& p : score.presets)
    {
        std::pair<float, std::string> entry(p.points.flt, p.name);
        score.entries.insert(entry);
    }
}

std::string pld::Core::getScoreEntry(int i, float points, std::string name) {
    std::string entry = std::to_string(i);
    if (entry.size() < 2) { entry += " ";  }
    entry += " " + name;
    while (entry.size() < 17) {
        entry += " ";
    }
    std::string flt = std::to_string(points);
    int pos = (int)flt.find(".");
    entry += flt.substr(0, pos);
    return entry;
}