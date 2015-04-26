#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>

//////////
// Code //

class PlayerController : public clibgame::Component,
                         public clibgame::Listener {
private:
    const float accelSpeed,
                decelSpeed;

    float  x,  y;
    float dx, dy;

public:
    // Constructing a new PlayerController.
    PlayerController(float, float, float,
                     float, float);

    // Getting the name of the PlayerController component.
    std::string getName() const;

    // Updating this component.
    void update(GLFWwindow*, const clibgame::ECP&, float);

    // Alerting this component of events.
    virtual void alert(const clibgame::Event&&) override;
};

#endif
