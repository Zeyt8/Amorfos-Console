#include "vector.h"

Vector2 newVector2(int x, int y) {
    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

Vector3 newVector3(int x, int y, int z) {
    Vector3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Vector2 addVector2(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vector3 addVector3(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}