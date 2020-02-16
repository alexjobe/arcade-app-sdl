//
// Created by alex on 12/1/19.
//

#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <string>

static const float EPSILON = 0.0001f;

const float PI = 3.14159;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MillisecondsToSeconds(unsigned int milliseconds);

unsigned int GetIndex(unsigned int width, unsigned int row, unsigned int col);

bool StringCompare(const std::string& a, const std::string& b);

#endif //UTILS_UTILS_H
