#include "rectangle.hpp"

//////////////
// Includes //
#include <cmath>

//////////
// Code //

// Constructing a new Rectangle.
Rectangle::Rectangle(float x, float y, float w, float h) :
        x(x), y(y),
        w(w), h(h){ }

// Getting different sides of a rectangle.
float Rectangle::top()     const { return y + h; }
float Rectangle::bottom()  const { return y;     }
float Rectangle::left()    const { return x;     }
float Rectangle::right()   const { return x + w; }

// Finding the center of the Rectangle in the different axes.
float Rectangle::centerX() const { return x + (w / 2.f); }
float Rectangle::centerY() const { return y + (y / 2.f); }

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
    if (top() > r.bottom() && bottom() < r.top() && left() < r.right() && right() > r.left()) {
        float dx = distanceX(r),
              dy = distanceY(r);

        if (dx <= dy) {
            if (left() <= r.right())
                return COL_LEFT;
            return COL_RIGHT;
        } else {
            if (top() >= r.bottom())
                return COL_TOP;
            return COL_BOTTOM;
        }
    }

    return COL_NONE;
}

// Checking if a collision even exists.
bool Rectangle::collides(const Rectangle& r) { return collisionDirection(r) != COL_NONE; }
