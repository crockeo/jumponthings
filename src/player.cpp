#include "player.hpp"

//////////
// Code //

// Constructing a new PlayerController.
PlayerController::PlayerController(float accelSpeed, float decelSpeed,
                                   float x, float y) :
        accelSpeed(accelSpeed),
        decelSpeed(decelSpeed) {
    this->x = x;
    this->y = y;
}

// Getting the name of the PlayerController component.
std::string PlayerController::getName() const { return "playerController"; }

// Updating this component.
void PlayerController::update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
    bool mx = false,
         my = false;

    if (glfwGetKey(window, GLFW_KEY_W)) {
        dy += accelSpeed * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S)) {
        dy -= accelSpeed * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A)) {
        dx -= accelSpeed * dt;
        mx = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D)) {
        dx += accelSpeed * dt;
        mx = true;
    }

    if (!mx)
        dx -= dt * dx * decelSpeed;
    if (!my)
        dy -= dt * dy * decelSpeed;

    clibgame::CPosition& position = dynamic_cast<clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
    position.translate(dx, dy);
}
