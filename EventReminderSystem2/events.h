#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDate>

class Event {
public:
    Event(const QString &t = "", const QString &d = "", const QDate &dt = QDate::currentDate(), bool done = false);

    QString title() const;
    QString description() const;
    QDate date() const;
    bool isDone() const;

    void setTitle(const QString &t);
    void setDescription(const QString &d);
    void setDate(const QDate &dt);
    void toggleDone();

private:
    QString m_title;
    QString m_description;
    QDate m_date;
    bool m_done;
};

#endif // EVENT_H
