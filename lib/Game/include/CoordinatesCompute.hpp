/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** CoordinatesCompute.hpp.h
*/

#pragma once

#include <cstddef>
#include <utility>

namespace Arcade {

/**
 * Computes the index corresponding to the coordinates x and y in the map
 *
 * @param x The x coordinate
 * @param y The y coordinate
 * @param lineLen length of a line
 * @return The corresponding index
 */
std::size_t computeIndex(unsigned int x, unsigned int y, unsigned int lineLen);
std::pair<unsigned int, unsigned int> computeCoordinates(unsigned int index, unsigned int lineLen);

}