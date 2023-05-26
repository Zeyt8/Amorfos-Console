#pragma once

#include <stdint.h>

namespace amorfos
{
    template <typename T>
    struct Vector2 {
        T x;
        T y;
    };

    template <typename T>
    struct Vector3 {
        T x;
        T y;
        T z;
    };

    template <typename T> Vector2<T> newVector2(T x, T y) {
        Vector2<T> vector;
        vector.x = x;
        vector.y = y;
        return vector;
    }

    template <typename T> Vector3<T> newVector3(T x, T y, T z) {
        Vector3<T> vector;
        vector.x = x;
        vector.y = y;
        vector.z = z;
        return vector;
    }

    template <typename T> Vector2<T> addVector2(Vector2<T> a, Vector2<T> b) {
        Vector2<T> vector;
        vector.x = a.x + b.x;
        vector.y = a.y + b.y;
        return vector;
    }

    template <typename T> Vector3<T> addVector3(Vector3<T> a, Vector3<T> b) {
        Vector3<T> vector;
        vector.x = a.x + b.x;
        vector.y = a.y + b.y;
        vector.z = a.z + b.z;
        return vector;
    }
}