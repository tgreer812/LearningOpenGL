// EventDispatcher.cpp

#include "Event.h"

void EventDispatcher::AddListener(const std::string& eventType, EventCallback callback) {
    listeners[eventType].push_back(callback);
}

void EventDispatcher::Dispatch(std::shared_ptr<Event> event) {
    const std::string& eventType = event->GetEventType();
    auto it = listeners.find(eventType);
    if (it != listeners.end()) {
        for (auto& listener : it->second) {
            listener(event);  // Call each registered listener with shared_ptr<Event>
        }
    }
}
