#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>

//////////
// Code //

class PlayerController : public clibgame::Component {
private:
    float  x,  y;
    float dx, dy;
    bool canjump;

    // Rescaling a value depending on if you're in the air or not.
    float jumpSpeed(float) const;

public:
    // Constructing a new PlayerController.
    PlayerController(float, float);

    // Getting the name of the PlayerController component.
    std::string getName() const;

    // Updating this component.
    void update(GLFWwindow*, const clibgame::ECP&, float);
};

#endif
