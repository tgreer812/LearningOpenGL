// MouseEvent.h

#pragma once

#include "Event.h"

enum class MouseButton {
    Left = 0,
    Right = 1,
    Middle = 2,
    // Add additional mouse buttons if needed
};

//
// Base MouseEvent class
//
class MouseEvent : public Event {
public:
    virtual ~MouseEvent() = default;

    // Common data for all mouse events
    inline int GetX() const { return x; }
    inline int GetY() const { return y; }

protected:
    MouseEvent(int x, int y) : x(x), y(y) {}

    int x, y;
};

//
// MouseMovedEvent
//
class MouseMovedEvent : public MouseEvent {
public:
    MouseMovedEvent(int x, int y, int deltaX, int deltaY)
        : MouseEvent(x, y), deltaX(deltaX), deltaY(deltaY) {}

    std::string GetEventType() const override { return "MouseMovedEvent"; }

    inline int GetDeltaX() const { return deltaX; }
    inline int GetDeltaY() const { return deltaY; }

private:
    int deltaX, deltaY;
};

//
// MouseScrolledEvent
//
class MouseScrolledEvent : public MouseEvent {
public:
    MouseScrolledEvent(int x, int y, float offsetX, float offsetY)
        : MouseEvent(x, y), offsetX(offsetX), offsetY(offsetY) {}

    std::string GetEventType() const override { return "MouseScrolledEvent"; }

    inline float GetOffsetX() const { return offsetX; }
    inline float GetOffsetY() const { return offsetY; }

private:
    float offsetX, offsetY;
};

//
// Base MouseButtonEvent class
//
class MouseButtonEvent : public MouseEvent {
public:
    inline MouseButton GetMouseButton() const { return button; }

protected:
    MouseButtonEvent(int x, int y, MouseButton button)
        : MouseEvent(x, y), button(button) {}

    MouseButton button;
};

//
// MouseButtonPressedEvent
//
class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int x, int y, MouseButton button)
        : MouseButtonEvent(x, y, button) {}

    std::string GetEventType() const override { return "MouseButtonPressedEvent"; }
};

//
// MouseButtonReleasedEvent
//
class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int x, int y, MouseButton button)
        : MouseButtonEvent(x, y, button) {}

    std::string GetEventType() const override { return "MouseButtonReleasedEvent"; }
};
