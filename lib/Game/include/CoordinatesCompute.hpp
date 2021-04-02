/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** CoordinatesCompute.hpp.h
*/

#pragma once

#include <cstddef>

namespace Arcade {

/**
 * Computes the index corresponding to the coordinates x and y in the map
 *
 * @param x The x coordinate
 * @param y The y coordinate
 * @param lineLen length of a line
 * @return The corresponding index
 */
std::size_t computeCoordinates(unsigned int x, unsigned int y, unsigned int lineLen);

}