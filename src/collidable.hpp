#ifndef _COLLIDABLE_HPP_
#define _COLLIDABLE_HPP_

//////////////
// Includes //
#include <clibgame.hpp>
#include <exception>

#include "rectangle.hpp"

//////////
// Code //

// An event meant to propagate the information regaring a 
class CollidableEvent : public clibgame::Event {
private:
    const std::string eventName;
    
public:
    const Collision collision;
    const Rectangle rect;

    // Creating a new CollidableEvent about a
    CollidableEvent(std::string, Collision, Rectangle);

    // Getting the type of the event. It ought to be
    // collidable_event_<entity name>.
    virtual std::string getEventType() const override;
};

// A component to deal with collisions - it alerts a CollidableEvent whenever
// it collides with something.
class Collidable : public clibgame::Component {
private:
    // Getting the set of rectangles that represent revelant collidables in the
    // form of a rectangle.
    std::vector<Rectangle> getCollidables(const clibgame::ECP&) const throw(std::runtime_error);

    const bool doCollision;

public:
    // Creating a collidable with the option of whether or not it should check
    // for collisions itself.
    Collidable(bool);

    // Creating a new collidable.
    Collidable();

    // Getting the collision rectangle for this collidable.
    Rectangle getCollisionRectangle() const throw(std::runtime_error);

    // Getting the name of this component.
    virtual std::string getName() const override;

    // Updating this 
    virtual void update(GLFWwindow*, const clibgame::ECP&, float) override;
};

#endif
