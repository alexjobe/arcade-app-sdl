//
// Created by alex on 12/1/19.
//

#include "Utils.h"
#include <cmath>
#include <algorithm>
#include <cctype>

bool IsEqual(float x, float y)
{
    return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y)
{
    return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y)
{
    return x < y || IsEqual(x, y);
}

float MillisecondsToSeconds(unsigned int milliseconds)
{
    return static_cast<float>(milliseconds) / 1000.0f;
}

unsigned int GetIndex(unsigned int width, unsigned int row, unsigned int col)
{
    return row * width + col;
}

bool StringCompare(const std::string& a, const std::string& b)
{
    if(a.length() == b.length())
    {
        return std::equal(a.begin(), a.end(), b.begin(), [](unsigned char a, unsigned char b) {
           return std::tolower(a) == std::tolower(b);
        });
    }

    return false;
}