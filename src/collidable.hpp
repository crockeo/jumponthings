#ifndef _COLLIDABLE_HPP_
#define _COLLIDABLE_HPP_

//////////////
// Includes //
#include <clibgame.hpp>
#include <exception>

#include "rectangle.hpp"

//////////
// Code //

// A set of collisions.
class CollidableSet : public clibgame::Component {
private:
    std::vector<Rectangle> collisions;

public:
    // Creating a collidable set with an already-defined vector of Rectangles.
    CollidableSet(std::vector<Rectangle>);

    // Creating a collidable set without any default rectangles.
    CollidableSet();

    // Getting this set's collision rectangles.
    std::vector<Rectangle> getCollisionRectangles() const;

    // Adding a new collision rectangle.
    void addCollision(Rectangle);

    // Getting the name of the component.
    virtual std::string getName() const override;
};

// Getting the collision rectangle from a built-in position component.
Rectangle getCollisionRectangle(const clibgame::CPosition&);

// Getting the set of collision rectangles from the ECP.
std::vector<Rectangle> getCollisionRectangles(const clibgame::Entity&, const clibgame::ECP&);

#endif
