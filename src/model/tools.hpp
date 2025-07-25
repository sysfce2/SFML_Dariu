#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

class Tools {
   public:
    Tools();

    static int getStartSprite(int, int);
    static float ceil_special(float num, float biggerthan);
    static float floor_special(float num, float lessthan);
    static std::string addZero(int seconds);
    static std::string seconds_to_hour(int seconds);
    static int time_dif_in_seconds(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);
    static int wordOccurrence(std::string sentence, std::string word);
    static bool hasString(std::string line, std::string str);
    static std::string get_lines_from_dtm(std::string filename, std::string tag, std::string endLine);
    static uint32_t crc32(const std::string& data);
};
#endif
