#include "player.hpp"

//////////////
// Includes //
#include "collidable.hpp"
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

    canjump = true;

    clibgame::ListenerManager::instance().registerListener(this, "collidable_event_player");
}

// Getting the name of the PlayerController component.
std::string PlayerController::getName() const { return "playerController"; }

// Updating this component.
void PlayerController::update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
    clibgame::CPosition& position = dynamic_cast<clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
    TexableSet& ts = dynamic_cast<TexableSet&>(getOwner().getComponent("texableSet"));
    bool mx = false;

    if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_D)) {
    } else if (glfwGetKey(window, GLFW_KEY_A)) {
        if (dx > 0)
            dx -= dx * decelSpeed * dt;
        dx -= accelSpeed * dt;
        mx = true;
        ts.setFlip(true, false);
    } else if (glfwGetKey(window, GLFW_KEY_D)) {
        if (dx < 0)
            dx -= dx * decelSpeed * dt;
        dx += accelSpeed * dt;
        mx = true;
        ts.setFlip(false, false);
    }

    dy -= accelSpeed * dt * 1.3;

    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        if (position.getY() == 0 || canjump) {
            dy = 400;
            canjump = false;
        }
    }

    std::string animation;
    if (!mx) {
        dx -= dx * decelSpeed * dt;
        animation = "player_standing";
    } else
        animation = "player_running";
    if (!canjump && dy != 0)
        animation = "player_jumping";

    clibgame::ListenerManager::instance().alert(TexableSetEvent(getOwner().getUID(), animation));
    position.translate(dx * dt, dy * dt);
}

// Alerting this component of events.
void PlayerController::alert(const clibgame::Event&& e) {
    if (e.getEventType() == "collidable_event_player") {
        clibgame::CPosition& position = dynamic_cast<clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
        const CollidableEvent&& ce = dynamic_cast<const CollidableEvent&&>(e);

        switch (ce.collision) {
        case COL_TOP:
            dy = 0;
            position.setY(ce.rect.bottom() - position.getHeight());
            break;
        case COL_BOTTOM:
            canjump = true;
            dy = 0;
            position.setY(ce.rect.top());
            break;
        case COL_LEFT:
            dx *= -0.3f;
            position.setX(ce.rect.right());
            break;
        case COL_RIGHT:
            dx *= -0.3f;
            position.setX(ce.rect.left() - position.getWidth());
            break;
        case COL_NONE:
            canjump = false;
            break;
        }
    }
}
