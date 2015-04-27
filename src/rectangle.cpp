#include "rectangle.hpp"

//////////////
// Includes //
#include <cmath>

//////////
// Code //

// Constructing a new Rectangle.
Rectangle::Rectangle(float x, float y, float w, float h) :
        x(x), y(y),
        w(w), h(h) { }

// An empty Rectangle.
Rectangle::Rectangle() :
        Rectangle(0, 0, 0, 0) { }

// Getting different sides of a rectangle.
float Rectangle::top()     const { return y + h; }
float Rectangle::bottom()  const { return y;     }
float Rectangle::left()    const { return x;     }
float Rectangle::right()   const { return x + w; }

// Finding the center of the Rectangle in the different axes.
float Rectangle::centerX() const { return x + (w / 2.f); }
float Rectangle::centerY() const { return y + (h / 2.f); }

// Finding the distance between this rectangle's center and another's.
float Rectangle::distanceX(const Rectangle& r) const {
    return fabs(centerX() - r.centerX());
}

float Rectangle::distanceY(const Rectangle& r) const {
    return fabs(centerY() - r.centerY());
}

// Finding the direction of a collision - or COL_NONE if no collision
// occurs.
Collision Rectangle::collisionDirection(const Rectangle& r) {
    float dx = distanceX(r) - (w / 2.f) - (r.w / 2.f),
          dy = distanceY(r) - (h / 2.f) - (r.h / 2.f);

    if (dx < 0 && dy < 0) {
        if (dy >= dx || fabs(dx - dy) < 5) {
            if (centerY() < r.centerY())
                return COL_TOP;
            return COL_BOTTOM;
        } else {
            if (centerX() > r.centerX())
                return COL_LEFT;
            return COL_RIGHT;
        }
    }

    return COL_NONE;
}

// Checking if a collision even exists.
bool Rectangle::collides(const Rectangle& r) { return collisionDirection(r) != COL_NONE; }
