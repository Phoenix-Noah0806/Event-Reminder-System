#ifndef EVENT_H
#define EVENT_H

#include <QString>

class Event {
    QString title;
    QString desc;
    QString date;
    bool isCompleted;

public:
    Event(QString t, QString d, QString dt);

    QString getTitle() const;
    QString getDesc() const;
    QString getDate() const;
    bool status() const;

    void changeStatus();
};

#endif // EVENT_H
