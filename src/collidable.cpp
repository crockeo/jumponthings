#include "collidable.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

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

        if (e.hasComponent("clibgame_position")) {
            const clibgame::CPosition& pos = dynamic_cast<const clibgame::CPosition&>(e.getComponent("clibgame_position"));

            if (pos.shouldDoCollide())
                rs.push_back(getCollisionRectangle(pos));
        }
    }

    return rs;
}

// Creating a new CollidableEvent about a
CollidableEvent::CollidableEvent(std::string ownerName, Collision collision, Rectangle rect) :
        eventName("collidable_event_" + ownerName),
        collision(collision),
        rect(rect) { }

// Getting the type of the event. It ought to be
// collidable_event_<entity name>.
std::string CollidableEvent::getEventType() const { return eventName; };

// Getting the set of rectangles that represent revelant collidables in the
// form of a rectangle.
std::vector<Rectangle> Collidable::getCollidables(const clibgame::ECP& ecp) const throw(std::runtime_error) {
    // TODO: Definitely optimize this at some point. Research quad trees.

    std::vector<Rectangle> rs;
    for (auto it = ecp.begin(); it != ecp.end(); it++) {
        const clibgame::Entity& e = ecp.getEntity(std::get<0>(*it));
        if (e.getUID() == getOwner().getUID())
            continue;

        if (e.hasComponent("collidable")) {
            const Collidable& c = dynamic_cast<const Collidable&>(e.getComponent("collidable"));
            rs.push_back(c.getCollisionRectangle());
        }
    }
    
    return rs;
}
// Creating a collidable with the option of whether or not it should check
// for collisions itself.
Collidable::Collidable(bool doCollision) : doCollision(doCollision) { }

// Creating a new collidable.
Collidable::Collidable() : Collidable(true) { }

// Getting the collision rectangle for this collidable.
Rectangle Collidable::getCollisionRectangle() const throw(std::runtime_error) {
    if (!getOwner().hasComponent("clibgame_position"))
        throw std::runtime_error("To be collidable, an entity must also have a clibgame::CPosition");

    const clibgame::CPosition& pos = dynamic_cast<const clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
    return Rectangle(pos.getX()    , pos.getY(),
                     pos.getWidth(), pos.getHeight());
}

// Getting the name of this component.
std::string Collidable::getName() const { return "collidable"; }

// Updating this 
void Collidable::update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
    if (doCollision) {
        std::vector<Rectangle> rectangles;
        Rectangle rectangle;

        try {
            rectangles = getCollidables(ecp);
            rectangle = getCollisionRectangle();
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
            return;
        }

        for (auto r: rectangles) {
            Collision col = rectangle.collisionDirection(r);
            if (col == COL_NONE)
                continue;

            clibgame::ListenerManager::instance().alert(CollidableEvent(getOwner().getUID(),
                                                                        col,
                                                                        r));
            break;
        }
    }
}
