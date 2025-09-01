#include "event.h"

Event::Event(const QString &t, const QString &d, const QDate &dt, bool done)
    : m_title(t), m_description(d), m_date(dt), m_done(done) {}

QString Event::title() const { return m_title; }
QString Event::description() const { return m_description; }
QDate Event::date() const { return m_date; }
bool Event::isDone() const { return m_done; }

void Event::setTitle(const QString &t) { m_title = t; }
void Event::setDescription(const QString &d) { m_description = d; }
void Event::setDate(const QDate &dt) { m_date = dt; }
void Event::toggleDone() { m_done = !m_done; }
