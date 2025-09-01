#include "reminder.h"

void Reminder::addEvent(const Event &e) {
    list.push_back(e);
}

void Reminder::removeEvent(int index) {
    if (index >= 0 && index < (int)list.size()) {
        list.erase(list.begin() + index);
    }
}

void Reminder::markEventAsDone(int index) {
    if (index >= 0 && index < (int)list.size()) {
        list[index].changeStatus();
    }
}

const std::vector<Event>& Reminder::getEvents() const {
    return list;
}

bool Reminder::isEmpty() const {
    return list.empty();
}
