#pragma once

struct Vec2 {
    float x;
    float y;
};

struct Color {
    float r;
    float g;
    float b;
    float a;
};

struct Rect {
    Vec2 min;
    Vec2 max;

    bool Contain(Vec2 point) {
        if (point.x < min.x) return false;
        if (point.x > max.x) return false;
        if (point.y < min.y) return false;
        if (point.y > max.y) return false;
        return true;
    }
};
