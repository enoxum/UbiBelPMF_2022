#include "string_utility.h"

std::vector<std::string> team_game::splitLine(std::string line) {
    std::string spaceDelimiter = " ";
    std::vector<std::string> words{};

    size_t pos = 0;
    while ((pos = line.find(spaceDelimiter)) != std::string::npos) {
        if (line.substr(0, pos) != "")
        {
            words.push_back(line.substr(0, pos));
        }
        line.erase(0, pos + spaceDelimiter.length());
    }

    // last word must be added
    words.push_back(line);

    return words;
}