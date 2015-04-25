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
    TexableSet& ts = dynamic_cast<TexableSet&>(getOwner().getComponent("texableSet"));
    bool mx = false;

    if (glfwGetKey(window, GLFW_KEY_A)) {
        if (dx > 0)
            dx -= dx * decelSpeed * dt;
        dx -= accelSpeed * dt;
        mx = true;
        ts.setFlip(true, false);
    }

    if (glfwGetKey(window, GLFW_KEY_D)) {
        if (dx < 0)
            dx -= dx * decelSpeed * dt;
        dx += accelSpeed * dt;
        mx = true;
        ts.setFlip(false, false);
    }

    if (position.getY() > 0)
        dy -= accelSpeed * dt * 1.3;
    else if (position.getY() < 0) {
        dy = 0;
        position.setY(0);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        if (position.getY() == 0)
            dy = 800;
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
