#include "game.hpp"

//////////////
// Includes //
#include "texablerender.hpp"
#include "collidable.hpp"
#include "texableset.hpp"
#include "player.hpp"

//////////
// Code //

// Constructing a new game.
Game::Game() {
    addEntity("player");
    getEntity("player").addComponent(new clibgame::CPosition(0, 0, 128, 256));
    getEntity("player").addComponent(new PlayerController(1200, 6, 10, 0, 0));
    getEntity("player").addComponent(new Collidable());

    TexableSet* ts = new TexableSet("player_standing", "clibgame_position_player",
                                    0, 0, 128, 256);

    ts->addRender("player_standing", TR_TEXTURE, "player_standing", "testshader");
    ts->addRender("player_running", TR_ANIMATION, "player_running", "testshader");
    ts->addRender("player_jumping", TR_TEXTURE, "player_jumping", "testshader");

    getEntity("player").addComponent(ts);

    addEntity("rect");
    getEntity("rect").addComponent(new TexableRender(TR_TEXTURE, "dirt", "testshader",
                                                     0, -10, 50, 490));

    addEntity("rect2");
    getEntity("rect2").addComponent(new TexableRender(TR_TEXTURE, "dirt", "testshader",
                                                      300, 0, 128, 128));

    addEntity("background");
    getEntity("background").addComponent(new TexableRender(TR_TEXTURE, "blue_desert", "testshader",
                                                           0, 0, 1028, 1028));
}
