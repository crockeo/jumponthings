#include "game.hpp"

//////////////
// Includes //
#include "player.hpp"

//////////
// Code //

// Constructing a new game.
Game::Game() {
    addEntity("player");
    getEntity("player").addComponent(new clibgame::CPosition(0, 0, 32, 64));
    getEntity("player").addComponent(new PlayerController(300, 2, 0, 0));
}
