#pragma once
#include "common.h"
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
        Array<RenderVertex> vertexes;
        Array<RenderIndex> indexes;
        Array<RenderCommand> commands;
    } g_RenderOutput;

    void Init() {
        g_RenderOutput.vertexes.Init();
        g_RenderOutput.indexes.Init();
        g_RenderOutput.commands.Init();
    }

    void Cleanup() {
        g_RenderOutput.vertexes.Cleanup();
        g_RenderOutput.indexes.Cleanup();
        g_RenderOutput.commands.Cleanup();   
    }

    void PushLayer() {
        g_RenderOutput.commands.Add(1) = {0, 0};
    }

    void NewFrame() {
        g_RenderOutput.vertexes.Clear();
        g_RenderOutput.indexes.Clear();
        g_RenderOutput.commands.Clear();
        PushLayer();
    }

    void PushRect(Rect rect, Color color) {        
        RenderVertex vertex1 = {rect.min, color};
        RenderVertex vertex2 = {{rect.min.x, rect.max.y}, color};
        RenderVertex vertex3 = {{rect.max.x, rect.min.y}, color};
        RenderVertex vertex4 = {rect.max, color};

        int offset = g_RenderOutput.vertexes.count;

        g_RenderOutput.vertexes.Add(1) = {rect.min, color};
        g_RenderOutput.vertexes.Add(1) = {{rect.min.x, rect.max.y}, color};
        g_RenderOutput.vertexes.Add(1) = {{rect.max.x, rect.min.y}, color};
        g_RenderOutput.vertexes.Add(1) = {rect.max, color};

        g_RenderOutput.indexes.Add(1) = offset;
        g_RenderOutput.indexes.Add(1) = offset + 1;
        g_RenderOutput.indexes.Add(1) = offset + 2;
        g_RenderOutput.indexes.Add(1) = offset + 1;
        g_RenderOutput.indexes.Add(1) = offset + 2;
        g_RenderOutput.indexes.Add(1) = offset + 3;

        g_RenderOutput.commands.Last().n_vertex += 4;
        g_RenderOutput.commands.Last().n_index += 6;
    }


    int Button(int id, Rect rect, Color color) {
        PushRect(rect, color);
        if (rect.Contain(g_UIState.mouse_pos)) {
            g_UIState.hot_id = id;
        } else if (g_UIState.hot_id == id) {
            g_UIState.hot_id = -1;
            g_UIState.active_id = -1;
        }

        if (g_UIState.hot_id == id && g_UIState.mouse_down) {
            g_UIState.active_id = id;
        }
        if (g_UIState.active_id == id && !g_UIState.mouse_down) {
            g_UIState.active_id = -1;
            return true;
        }
        return false;
    }

}