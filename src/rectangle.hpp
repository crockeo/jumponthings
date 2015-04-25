#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

// The direction of a collision.
enum Collision {
    COL_TOP,
    COL_BOTTOM,
    COL_LEFT,
    COL_RIGHT,
    COL_NONE
};

// A const representation of a Rectangle.
struct Rectangle {
    const float x, y, w, h;

    // Constructing a new Rectangle.
    Rectangle(float, float, float, float);

    // Getting different sides of a rectangle.
    float top()    const;
    float bottom() const;
    float left()   const;
    float right()  const;

    // Finding the center of the Rectangle in the different axes.
    float centerX() const;
    float centerY() const;

    // Finding the distance between this rectangle's center and another's.
    float distanceX(const Rectangle&) const;
    float distanceY(const Rectangle&) const;

    // Finding the direction of a collision - or COL_NONE if no collision
    // occurs.
    Collision collisionDirection(const Rectangle&);

    // Checking if a collision even exists.
    bool collides(const Rectangle&);
};

#endif
