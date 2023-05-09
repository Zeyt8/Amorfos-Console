#pragma once

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

Vector2 newVector2(int x, int y);

Vector3 newVector3(int x, int y, int z);

Vector2 addVector2(Vector2 a, Vector2 b);

Vector3 addVector3(Vector3 a, Vector3 b);