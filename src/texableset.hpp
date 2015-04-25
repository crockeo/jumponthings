#ifndef _TEXABLE_SET_HPP_
#define _TEXABLE_SET_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <clibgame.hpp>
#include <exception>
#include <tuple>

#include "texablerender.hpp"

//////////
// Code //

// A TexableSetEvent is used to communicate that a TexableSet ought to change
// its texable to another.
class TexableSetEvent : public clibgame::Event {
private:
    const std::string eventName;

public:
    const std::string texableName;

    // Constructing a new TexableSetEvent.
    TexableSetEvent(std::string, std::string);

    // Getting the event name of a TexableSetEvent.
    virtual std::string getEventType() const override;
};

// A set of TexableRenders that can be switched between.
class TexableSet : public clibgame::Component,
                   public clibgame::Listener {
private:
    const std::string initialRender, eventName;

    std::vector<std::tuple<std::string, TRType, std::string, std::string>> bufferedLoads;
    std::unordered_map<std::string, TexableRender*> texables;
    TexableRender* current;
    std::string listenStr;
    bool flipx, flipy;
    float x, y, w, h;
    bool loaded;

public:
    // Creating a new, empty texable set with an initial render name that looks
    // for CPositionEvents to update information.
    TexableSet(std::string, std::string,
               float, float, float, float);

    // Creating a new, empty texable set with an initial render name.
    TexableSet(std::string,
               float, float, float, float);

    // Destroying this texable set.
    ~TexableSet();

    // Removing the copy constructor and assignment operator.
    TexableSet(const TexableSet&) = delete;
    TexableSet& operator=(const TexableSet&) = delete;

    // Adding a kind of render to this TexableSet.
    void addRender(std::string, TRType, std::string, std::string) throw(std::runtime_error);

    // Setting the current render.
    void setCurrent(std::string) throw(std::runtime_error);

    // Attempting to flip the X or Y axis. If done, the engine will assume that
    // the texture coordinates are in the shape of a rectangle in the order:
    // bottom left, bottom right, top right, top left.
    void setFlip(bool, bool);

    // Getting the name of this component.
    virtual std::string getName() const override;

    // Initializing this and all of its sub-components.
    virtual void init(GLFWwindow*, const clibgame::ECP&, const clibgame::Res&) override;

    // Rendering the current TexableRender.
    virtual void render() const override;

    // Alerting this module to any events.
    virtual void alert(const clibgame::Event&&) override;
};

#endif
