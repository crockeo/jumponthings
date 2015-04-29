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

// TODO: Scrap below this.

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
