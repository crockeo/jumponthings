#include "collidable.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

// Creating a collidable set with an already-defined vector of Rectangles.
CollidableSet::CollidableSet(std::vector<Rectangle> collisions) :
        collisions(collisions) { }

// Creating a collidable set without any default rectangles.
CollidableSet::CollidableSet() { }

// Getting this set's collision rectangles.
std::vector<Rectangle> CollidableSet::getCollisionRectangles() const {
    return collisions;
}

// Adding a new collision rectangle.
void CollidableSet::addCollision(Rectangle r) {
    collisions.push_back(r);
}

// Getting the name of the component.
std::string CollidableSet::getName() const {
    return "collidableSet";
}

// Getting the collision rectangle from a built-in position component.
Rectangle getCollisionRectangle(const clibgame::CPosition& pos) {
    return Rectangle(pos.getX(), pos.getY(),
                     pos.getWidth(), pos.getHeight());
}

// Getting the set of collision rectangles from the ECP.
std::vector<Rectangle> getCollisionRectangles(const clibgame::Entity& caller, const clibgame::ECP& ecp) {
    std::vector<Rectangle> rs;
    for (auto it = ecp.begin(); it != ecp.end(); it++) {
        const clibgame::Entity& e = ecp.getEntity(std::get<0>(*it));
        if (e.getUID() == caller.getUID())
            continue;

        if (e.hasComponent("collidableSet")) {
            const CollidableSet& cs = dynamic_cast<const CollidableSet&>(e.getComponent("collidableSet"));
            for (Rectangle r: cs.getCollisionRectangles())
                rs.push_back(r);
        }

        if (e.hasComponent("clibgame_position")) {
            const clibgame::CPosition& pos = dynamic_cast<const clibgame::CPosition&>(e.getComponent("clibgame_position"));

            if (pos.shouldDoCollide())
                rs.push_back(getCollisionRectangle(pos));
        }
    }

    return rs;
}
