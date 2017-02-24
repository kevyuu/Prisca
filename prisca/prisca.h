#pragma once

namespace Prisca {

    struct Vec2 {
        int x;
        int y;
    }

    struct Color {
        int r;
        int g;
        int b;
    }

    struct Rect {
        Vec2 min;
        Vec2 max;
    }

    struct UIState {
        code
    } g_UIState;

    struct RenderOutput {
        float vertices[1000];
        int n_vertex;
        float index[1000];
        int n_index;
    }

    void Init() {

    }

    void Cleanup() {
        
    }

    int Button(Rect rect, Color color) {

    }

}