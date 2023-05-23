#include "vector.h"

amorfos::Vector2 amorfos::newVector2(float x, float y) {
    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

amorfos::Vector3 amorfos::newVector3(float x, float y, float z) {
    Vector3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

amorfos::Vector2 amorfos::addVector2(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

amorfos::Vector3 amorfos::addVector3(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}