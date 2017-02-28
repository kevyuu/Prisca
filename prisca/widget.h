#pragma once
#include "prisca.h"

namespace Prisca {
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