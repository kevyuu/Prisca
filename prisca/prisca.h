#pragma once
#include "adt.h"
#include <iostream>

namespace Prisca {

    struct Vec2;
    struct Color;
    struct Rect;
    struct UIState;
    struct RenderVertex;
    typedef unsigned int RenderIndex;
    struct RenderCommand;

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

    struct UIState {
        Vec2 mouse_pos;
        bool mouse_down;

        int hot_id, active_id;
    } g_UIState;

    struct RenderVertex {
        Vec2 position;
        Color color;
    };

    struct RenderCommand {
        int n_vertex;
        int n_index;
    };

    struct RenderOutput {
        Array::Buffer<RenderVertex> vertexes;
        Array::Buffer<RenderIndex> indexes;
        Array::Buffer<RenderCommand> commands;
    } g_RenderOutput;

    void Init() {
        RenderOutput& ro = g_RenderOutput;
        Array::Init(ro.vertexes);
        Array::Init(ro.indexes);
        Array::Init(ro.commands);
    }

    void Cleanup() {
        RenderOutput& ro = g_RenderOutput;
        Array::Cleanup(ro.vertexes);
        Array::Cleanup(ro.indexes);
        Array::Cleanup(ro.commands);   
    }

    void PushLayer() {
        RenderOutput& ro = g_RenderOutput;
        Array::Add(ro.commands, 1);
        Array::Last(ro.commands) = {0, 0};
    }

    void NewFrame() {
        RenderOutput& ro = g_RenderOutput;
        Array::Clear(ro.vertexes);
        Array::Clear(ro.indexes);
        Array::Clear(ro.commands);
        PushLayer();
    }

    void PushRect(Rect rect, Color color) {     
        RenderOutput& ro = g_RenderOutput;

        int offset = ro.vertexes.count;
        Array::PushAndBack(ro.vertexes) = {rect.min, color };
        Array::PushAndBack(ro.vertexes) = {{rect.min.x, rect.max.y}, color};
        Array::PushAndBack(ro.vertexes) = {{rect.max.x, rect.min.y}, color};
        Array::PushAndBack(ro.vertexes) = {rect.max, color};

        Array::PushAndBack(ro.indexes) = offset;
        Array::PushAndBack(ro.indexes) = offset + 1;
        Array::PushAndBack(ro.indexes) = offset + 2;
        Array::PushAndBack(ro.indexes) = offset + 1;
        Array::PushAndBack(ro.indexes) = offset + 2;
        Array::PushAndBack(ro.indexes) = offset + 3;

        Array::Last(ro.commands).n_vertex += 4;
        Array::Last(ro.commands).n_index += 6;
    }


    

}