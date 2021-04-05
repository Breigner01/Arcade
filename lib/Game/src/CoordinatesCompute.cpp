/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** CoordinatesCompute.cpp.c
*/

#include "CoordinatesCompute.hpp"

extern "C" std::size_t Arcade::computeIndex(unsigned int x, unsigned int y, unsigned int lineLen)
{
    return (y * (lineLen + 1) + x);
}

extern "C" std::pair<unsigned int, unsigned int> computeCoordinates(unsigned int index, unsigned int lineLen)
{
    unsigned int y = index / (lineLen + 1);
    unsigned int x = index - y;

    return (std::make_pair(x, y));
}