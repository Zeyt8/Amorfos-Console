#include "vector.h"

amorfos::Vector2 amorfos::newVector2(int x, int y) {
    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

amorfos::Vector3 amorfos::newVector3(int x, int y, int z) {
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

uint16_t amorfos::Vector3ToColor(Vector3 vector) {
    uint16_t result = 0;
    result |= (uint16_t)vector.x << 11;
    result |= (uint16_t)vector.y << 5;
    result |= (uint16_t)vector.z;
    return result;
}

uint16_t amorfos::Vector3ToColor(float r, float g, float b) {
    uint16_t result = 0;
    result |= (uint16_t)r << 11;
    result |= (uint16_t)g << 5;
    result |= (uint16_t)b;
    return result;
}