#include "player.hpp"

//////////////
// Includes //
#include "texableset.hpp"

//////////
// Code //

// Constructing a new PlayerController.
PlayerController::PlayerController(float accelSpeed, float decelSpeed, float minSpeed,
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
    clibgame::CPosition& position = dynamic_cast<clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
    bool mx = false;

    if (glfwGetKey(window, GLFW_KEY_A)) {
        if (dx > 0)
            dx -= dx * decelSpeed * dt;
        dx -= accelSpeed * dt;
        mx = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D)) {
        if (dx < 0)
            dx -= dx * decelSpeed * dt;
        dx += accelSpeed * dt;
        mx = true;
    }

    if (position.getY() > 0)
        dy -= accelSpeed * dt * 2;
    else if (position.getY() < 0) {
        dy = 0;
        position.setY(0);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        if (position.getY() == 0)
            dy = 600;
    }

    std::string animation;
    if (!mx) {
        dx -= dx * decelSpeed * dt;
        animation = "player_standing";
    } else
        animation = "player_running";
    if (dy != 0)
        animation = "player_jumping";

    clibgame::ListenerManager::instance().alert(TexableSetEvent(getOwner().getUID(), animation));
    position.translate(dx * dt, dy * dt);
}
