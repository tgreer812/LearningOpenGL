#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

// Base Event class
class Event : public std::enable_shared_from_this<Event> {
public:
    virtual ~Event() = default;

    // A method to uniquely identify the event type
    virtual std::string GetEventType() const = 0;
};

class EventDispatcher {
public:
    using EventCallback = std::function<void(std::shared_ptr<Event>)>;

    // Register a listener for a specific event type
    void AddListener(const std::string& eventType, EventCallback callback);

    // Dispatch an event to the relevant listeners
    void Dispatch(std::shared_ptr<Event> event);

private:
    std::unordered_map<std::string, std::vector<EventCallback>> listeners;
};

