#include "collidable.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

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
    std::vector<Rectangle> rs {
        Rectangle(0, -10, 50, 490),
        Rectangle(300, 0, 128, 128)
    };
    
    return rs;
}

// Creating a new collidable.
Collidable::Collidable() { }

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
