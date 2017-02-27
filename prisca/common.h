#pragma once

namespace Prisca {

    template <class T>
    struct Array {
        T* element;
        int capacity;
        int count;

        void Init() {
            capacity = 100;
            count = 0;
            element = (T*) malloc(capacity * sizeof(T));
        }

        void Cleanup() {
            free(element);
        }

        void Grow(int grow_factor) {
            T* old_element = element;
            element = (T*) malloc(grow_factor * capacity * sizeof(T));
            memcpy(element, old_element, capacity * sizeof(T));
            capacity *= grow_factor;
            free(old_element);
        }

        void Shrink() {
            realloc(element, count * sizeof(T));
            capacity = count;
        }

        void Push(T element) {
            if (count == capacity) {
               Grow(2);
            }
            element[count] = element;
            ++count;
        }

        T& Add(int num) {
            if (count + num > capacity) {
                Grow(2);
            }

            count += num;

            return element[count - num];
        }

        void Clear() {
            count = 0;
        }

        T& Last() {
            return element[count - 1];
        }

        T& Get(int index) {
            return element[index];
        }        
    };
    
}

