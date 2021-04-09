/*
** EPITECH PROJECT, 2021
** file_cpp
** File description:
** HighScore.hpp.h
*/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class HighScore {
private:
    std::string m_file;
    std::vector<std::string> m_content;
    std::vector<std::string> string_to_vector(std::string str, char separator);

public:
    explicit HighScore(const std::string &file = "score.txt");
    ~HighScore();

    void writeNewScore();
    void setNewScore(std::string score);
    void dump();
};



