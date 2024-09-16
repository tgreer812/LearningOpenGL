// KeyEvent.h

#pragma once

#include "Event.h"
#include "GLFW/glfw3.h"

enum class KeyAction {
    Press = 0,
    Release = 1,
    Repeat = 2
};

class KeyEvent : public Event {
public:
    int key;
    int scancode;
    KeyAction action;
    int mods;

    KeyEvent(int key, int scancode, KeyAction action, int mods)
        : key(key), scancode(scancode), action(action), mods(mods) {}

    std::string GetEventType() const override {
        return "KeyEvent";
    }
};

