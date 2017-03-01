#pragma once
#include <iostream>
#include <string.h>

namespace Prisca {
    namespace Array {
        template <typename T>
        struct Buffer {
            T* element;
            int count;
            int capacity;
        };

        template <typename T>
        void Init(Buffer<T>& buffer) {
            buffer.count = 0;
            buffer.capacity = 100;
            buffer.element = (T*) malloc(buffer.capacity * sizeof(T));
        }

        template <typename T>
        void Cleanup(Buffer<T>& buffer) {
            free(buffer.element);
        }

        template <typename T>
        int Size(Buffer<T>& buffer) {
            return buffer.count;
        }

        template<typename T>
        void Grow(Buffer<T>& buffer, int growth_factor) {
            T* old_element = buffer.element;
            buffer.element = (T*) malloc(growth_factor * buffer.capacity * sizeof(T));
            memcpy(buffer.element, old_element, buffer.capacity * sizeof(T));
            buffer.capacity *= growth_factor;
            free(old_element);
        }

        template<typename T>
        void Shrink(Buffer<T>& buffer) {
            realloc(buffer.element, buffer.count * sizeof(T));
            buffer.capacity = buffer.count;
        }

        template <typename T>
        void Push(Buffer<T>& buffer, T element) {
            if (count == capacity) {
                Grow(buffer, 2);
            }
            buffer.element[count] = element;
            ++buffer.count;
        }

        template <typename T>
        T& PushAndBack(Buffer<T>& buffer) {
            //std::cout<<"PushAndBack"<<std::endl;
            if (buffer.count == buffer.capacity) {
                Grow(buffer, 2);
            }
            ++buffer.count;
            return buffer.element[buffer.count-1];
        }

        template <typename T>
        T& Last(Buffer<T>& buffer) {
            return buffer.element[buffer.count - 1];
        }

        template <typename T>
        void Add(Buffer<T>& buffer, int count) {
            while (buffer.count + count > buffer.capacity) {
                Grow(buffer, 2);
            }
            buffer.count += count;
        }

        template <typename T>
        void Clear(Buffer<T>& buffer) {
            buffer.count = 0;
        }
    }
}