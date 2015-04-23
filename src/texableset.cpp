#include "texableset.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

// Constructing a new TexableSetEvent.
TexableSetEvent::TexableSetEvent(std::string ownerName, std::string texableName) :
        eventName("texableset_" + ownerName),
        texableName(texableName) { }

// Getting the event name of a TexableSetEvent.
std::string TexableSetEvent::getEventType() const { return eventName; }

// Creating a new, empty texable set with an initial render name that looks
// for CPositionEvents to update information.
TexableSet::TexableSet(std::string initialRender, std::string eventName,
                       float x, float y, float w, float h) :
        initialRender(initialRender),
        eventName(eventName) {
    current = nullptr;
    loaded = false;

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}


// Creating a new, empty texable set with an initial render name.
TexableSet::TexableSet(std::string initialRender,
                       float x, float y, float w, float h) :
        TexableSet(initialRender, "", x, y, w, h) { }

// Destroying this texable set.
TexableSet::~TexableSet() {
    for (auto pair: texables)
        delete std::get<1>(pair);
}

// Adding a kind of render to this TexableSet.
void TexableSet::addRender(std::string name, TRType type, std::string texName, std::string shaderName) throw(std::runtime_error) {
    if (loaded)
        throw std::runtime_error("Cannot add renders after TexableSet has been initialized.");

    bufferedLoads.push_back(std::make_tuple(name, type, texName, shaderName));
}

// Setting the current render.
void TexableSet::setCurrent(std::string name) throw(std::runtime_error) {
    if (texables.find(name) == texables.end())
        throw std::runtime_error("No such texable exists in this TextureSet: " + name);

    current = texables.at(name);
}

// Getting the name of this component.
std::string TexableSet::getName() const { return "texableSet"; }

// Initializing this and all of its sub-components.
void TexableSet::init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
    listenStr = "texableset_" + getOwner().getUID();
    clibgame::ListenerManager::instance().registerListener(this, listenStr);
    loaded = true;

    for (auto tuple: bufferedLoads) {
        TexableRender* tr = new TexableRender(std::get<1>(tuple), std::get<2>(tuple), std::get<3>(tuple), eventName,
                                              x, y, w, h);

        tr->setOwner(&getOwner());
        tr->init(window, ecp, res);

        texables.insert(std::pair<std::string, TexableRender*>(std::get<0>(tuple), tr));
    }

    setCurrent(initialRender);
}

// Rendering the current TexableRender.
void TexableSet::render() const {
    if (current != nullptr)
        current->render();
}

// Alerting this module to any events.
void TexableSet::alert(const clibgame::Event&& e) {
    if (e.getEventType() == listenStr) {
        const TexableSetEvent&& tse = dynamic_cast<const TexableSetEvent&&>(e);
        try {
            setCurrent(tse.texableName);
        } catch (std::runtime_error err) {
            std::cout << "Couldn't change texable: " << err.what() << std::endl;
        }
    }
}
