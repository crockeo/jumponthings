#include "player.hpp"

//////////////
// Includes //
#include "collidable.hpp"
#include "texableset.hpp"

//////////
// Code //

const float PLAYER_ACCEL_SPEED       = 1400;
const float PLAYER_DECEL_SPEED       = 12;
const float PLAYER_GRAVITY_SPEED     = 800;
const float PLAYER_JUMP_SPEED        = 400;
const float PLAYER_MAX_SPEED         = 800;
const float PLAYER_JUMP_SPEED_FACTOR = 2;

// Rescaling a value depending on if you're in the air or not.
float PlayerController::jumpSpeed(float value) const {
    return canjump ? value : value / PLAYER_JUMP_SPEED_FACTOR;
}

// Constructing a new PlayerController.
PlayerController::PlayerController(float x, float y) {
    this->x = x;
    this->y = y;

    canjump = true;
}

// Getting the name of the PlayerController component.
std::string PlayerController::getName() const { return "playerController"; }

// Updating this component.
void PlayerController::update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
    clibgame::CPosition& pos = dynamic_cast<clibgame::CPosition&>(getOwner().getComponent("clibgame_position"));
    TexableSet& ts = dynamic_cast<TexableSet&>(getOwner().getComponent("texableSet"));
    bool mx = false;

    // Dealing with horizontal movement.
    if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_D)) {
    } else if (glfwGetKey(window, GLFW_KEY_A)) {
        if (dx > 0)
            dx -= dx * jumpSpeed(PLAYER_DECEL_SPEED) * dt;
        dx -= jumpSpeed(PLAYER_ACCEL_SPEED) * dt;
        if (dx < -PLAYER_MAX_SPEED)
            dx = -PLAYER_MAX_SPEED;

        mx = true;
        ts.setFlip(true, false);
    } else if (glfwGetKey(window, GLFW_KEY_D)) {
        if (dx < 0)
            dx -= dx * jumpSpeed(PLAYER_DECEL_SPEED) * dt;
        dx += jumpSpeed(PLAYER_ACCEL_SPEED) * dt;
        if (dx > PLAYER_MAX_SPEED)
            dx = PLAYER_MAX_SPEED;

        mx = true;
        ts.setFlip(false, false);
    }

    // Dealing with vertical movement.
    dy -= PLAYER_GRAVITY_SPEED * dt * 1.3;
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        if (pos.getY() == 0 || canjump) {
            dy = PLAYER_JUMP_SPEED;
            canjump = false;
        }
    }

    // Performing collision.
    std::vector<Rectangle> others = getCollisionRectangles(getOwner(), ecp);
    Rectangle self = getCollisionRectangle(pos);

    bool anyCollision = false;
    for (Rectangle other: others) {
        switch (self.collisionDirection(other)) {
        case COL_TOP:
            if (dy > 0) {
                dy = 0;
                pos.setY(other.bottom() - pos.getHeight());
                anyCollision = true;
            }
            break;
        case COL_BOTTOM:
            if (dy < 0) {
                canjump = true;
                dy = 0;
                pos.setY(other.top());
                anyCollision = true;
            }
            break;
        case COL_LEFT:
            dx *= -0.3f;
            pos.setX(other.right());
            anyCollision = true;
            break;
        case COL_RIGHT:
            dx *= -0.3f;
            pos.setX(other.left() - pos.getWidth());
            anyCollision = true;
            break;
        case COL_NONE:
            break;
        }
    }

    // Applying movement.
    pos.translate(dx * dt, dy * dt);

    // Applying some animation to the world.
    std::string animation;
    if (!mx) {
        dx -= dx * jumpSpeed(PLAYER_DECEL_SPEED) * dt;
        animation = "player_standing";
    } else
        animation = "player_running";
    if (!canjump && dy != 0)
        animation = "player_jumping";

    clibgame::ListenerManager::instance().alert(TexableSetEvent(getOwner().getUID(), animation));
}
