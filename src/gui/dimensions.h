#pragma once

struct Dimensions {
    unsigned x;
    unsigned y;

    Dimensions(unsigned int x, unsigned int y) : x(x), y(y) {}

    Dimensions() = default;
};
