//
// Created by adrie on 12/04/2023.
//

#include "AnimationsMaths.hpp"

float myLerp(float a, float b, float t) {
    return (1.0f - t) * a + t * b;
}
