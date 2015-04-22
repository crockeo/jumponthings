#include "game.hpp"

//////////////
// Includes //
#include "texablerender.hpp"
#include "player.hpp"

//////////
// Code //

// Constructing a new game.
Game::Game() {
    addEntity("player");
    getEntity("player").addComponent(new clibgame::CPosition(0, 0, 128, 256));
    getEntity("player").addComponent(new PlayerController(1200, 4, 0, 0));
    getEntity("player").addComponent(new TexableRender(TR_ANIMATION, "player", "testshader",
                                                       "clibgame_position_player",
                                                       0, 0, 128, 256));
}
