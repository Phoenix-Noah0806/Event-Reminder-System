#ifndef REMINDER_H
#define REMINDER_H

#include "event.h"
#include <vector>

class Reminder {
    std::vector<Event> list;

public:
    void addEvent(const Event &e);
    void removeEvent(int index);
    void markEventAsDone(int index);

    const std::vector<Event>& getEvents() const;
    bool isEmpty() const;
};

#endif // REMINDER_H
