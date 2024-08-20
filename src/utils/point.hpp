#ifndef INCLUDE_UTILS_POINT_HPP
#define INCLUDE_UTILS_POINT_HPP

#include <SDL2/SDL_rect.h>

typedef SDL_Point Point;
typedef SDL_FPoint FPoint;
typedef SDL_Rect Rect;
typedef SDL_FRect FRect;

constexpr bool operator == (Point const& a,
                            Point const& b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator != (Point const& a,
                            Point const& b)
{
    return !(a == b);
}

constexpr bool operator == (Rect const& a,
                            Rect const& b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

constexpr bool operator != (Rect const& a,
                            Rect const& b)
{
    return !(a == b);
}

constexpr bool operator == (FRect const& a,
                            FRect const& b)
{
    return abs(a.x - b.x) < 0.0001 &&
           abs(a.y - b.y) < 0.0001 &&
           abs(a.w - b.w) < 0.0001 &&
           abs(a.h - b.h) < 0.0001;
}

constexpr bool operator != (FRect const& a,
                            FRect const& b)
{
    return !(a == b);
}



constexpr Point operator + (Point a, Point const& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

constexpr Point operator - (Point a, Point const& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

constexpr Point operator * (Point a, float b)
{
    a.x *= b;
    a.y *= b;
    return a;
}


constexpr FPoint operator + (FPoint a, FPoint const& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

constexpr FPoint operator - (FPoint a, FPoint const& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

constexpr FPoint operator * (FPoint a, float b)
{
    a.x *= b;
    a.y *= b;
    return a;
}



constexpr Rect operator *= (Rect& a, float scalar)
{
    a.x *= scalar;
    a.y *= scalar;
    a.w *= scalar;
    a.h *= scalar;
    return a;
}


constexpr FRect operator *= (FRect& a, float scalar)
{
    a.x *= scalar;
    a.y *= scalar;
    a.w *= scalar;
    a.h *= scalar;
    return a;
}


constexpr FPoint norm(FPoint a)
{
    float base = sqrt(a.x * a.x + a.y * a.y);
    a.x /= base;
    a.y /= base;
    return a;
}

#endif // INCLUDE_UTILS_POINT_HPP
