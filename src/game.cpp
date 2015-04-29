#include "game.hpp"

//////////////
// Includes //
#include "texablerender.hpp"
#include "collidable.hpp"
#include "texableset.hpp"
#include "tilemap.hpp"
#include "player.hpp"

//////////
// Code //

// Registering the player.
void registerPlayer(Game* game, float x, float y, float w, float h) {
    game->addEntity("player");

    game->getEntity("player").addComponent(new clibgame::CPosition(x, y, w, h, true));
    game->getEntity("player").addComponent(new PlayerController(800, 12, 5, 0, 0));

    TexableSet* ts = new TexableSet("player_standing", "clibgame_position_player",
                                    64, 64, 64, 128);

    ts->addRender("player_standing", TR_TEXTURE, "player_standing", "testshader");
    ts->addRender("player_running", TR_ANIMATION, "player_running", "testshader");
    ts->addRender("player_jumping", TR_TEXTURE, "player_jumping", "testshader");

    game->getEntity("player").addComponent(ts);
}

// Constructing a new game.
Game::Game() {
    loadTileMap("tilemap", *this, "res/tilemap.txt");
    registerPlayer(this, 64, 64, 64, 128);
}
