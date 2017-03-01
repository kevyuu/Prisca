#pragma once

#include "adt.h"
#include "primitive.h"

namespace Prisca {
    namespace Render {
        struct Vertex {
            Vec2 position;
            Color color;
        };

        typedef unsigned int Index;

        struct Command {
            int n_vertex;
            int n_index;
        };

        struct Output {
            Array::Buffer<Render::Vertex> vertexes;
            Array::Buffer<Render::Index> indexes;
            Array::Buffer<Render::Command> commands;
        } g_RenderOutput;

        void Init() {
            Render::Output& ro = g_RenderOutput;
            Array::Init(ro.vertexes);
            Array::Init(ro.indexes);
            Array::Init(ro.commands);
        }

        void Cleanup() {
            Render::Output& ro = g_RenderOutput;
            Array::Cleanup(ro.vertexes);
            Array::Cleanup(ro.indexes);
            Array::Cleanup(ro.commands);   
        }

        void PushLayer() {
            Render::Output& ro = g_RenderOutput;
            Array::Add(ro.commands, 1);
            Array::Last(ro.commands) = {0, 0};
        }

        void NewFrame() {
            Render::Output& ro = g_RenderOutput;
            Array::Clear(ro.vertexes);
            Array::Clear(ro.indexes);
            Array::Clear(ro.commands);
            PushLayer();
        }

        void PushRect(Rect rect, Color color) {     
            Render::Output& ro = g_RenderOutput;

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
}