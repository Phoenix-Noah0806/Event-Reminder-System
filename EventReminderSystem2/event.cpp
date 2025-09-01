#include "event.h"

Event::Event(QString t, QString d, QString dt)
    : title(t), desc(d), date(dt), isCompleted(false) {}

QString Event::getTitle() const { return title; }
QString Event::getDesc() const { return desc; }
QString Event::getDate() const { return date; }
bool Event::status() const { return isCompleted; }
void Event::changeStatus() { isCompleted = !isCompleted; }
