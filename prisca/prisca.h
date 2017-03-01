#pragma once
#include "adt.h"
#include "primitive.h"
#include "render.h"
#include "widget.h"
#include <iostream>

namespace Prisca {

    struct UIState {
        Vec2 mouse_pos;
        bool mouse_down;

        int hot_id, active_id;
    } g_UIState;    

}