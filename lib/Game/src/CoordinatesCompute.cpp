/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** CoordinatesCompute.cpp.c
*/

#include "CoordinatesCompute.hpp"

std::size_t Arcade::computeCoordinates(unsigned int x, unsigned int y, unsigned int lineLen)
{
    return ((y + 1) * lineLen + x);
}