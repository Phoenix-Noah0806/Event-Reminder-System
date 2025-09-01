#include <iostream>
#include <vector>
using namespace std;
class Event
{
    string title;
    string desc;
    string date;
    bool isCompleted;

public:
    Event(string title, string desc, string date)
    {
        this->title = title;
        this->desc = desc;
        this->date = date;
        this->isCompleted = false;
    }
    string getTitle()
    {
        return this->title;
    }
    string getDesc()
    {
        return this->desc;
    }
    string getDate()
    {
        return this->date;
    }
    bool status()
    {
        return this->isCompleted;
    }
    void changeStatus()
    {
        this->isCompleted = !(this->isCompleted);
    }
};
class reminder
{
    vector<Event> list;

public:
    void addEvent()
    {
        string title;
        string desc;
        string date;
        cout << "---Enter title for Event---" << endl;
        cin >> title;
        cout << "---Enter description for Event---" << endl;
        cin.ignore();
        getline(cin, desc);
        cout << "---Enter date for Event---" << endl;
        cin >> date;
        Event obj(title, desc, date);
        list.push_back(obj);
    }
    void viewEvent()
    {
        if (list.size() == 0)
        {
            cout << "No event found" << endl;
            return;
        }

        for (int i = 0; i < list.size(); i++)
        {
            cout << (i + 1) << ". Event Title: " << list[i].getTitle() << endl;
            cout << "   Description: " << list[i].getDesc() << endl;
            cout << "   Date: " << list[i].getDate() << endl;
            cout << "   Status: " << (list[i].status() ? "Completed" : "Pending") << endl;
            cout << "---------------------------------" << endl;
        }
    }
    void markEventasDone(int index)
    {
        if (index <= 0 || index > list.size())
        {
            cout << "Invalid event index" << endl;
            return;
        }
        list[index - 1].changeStatus();
        cout << "Event status updated successfully" << endl;
        return;
    }
    void viewCompletedEvents()
    {
        if (list.size() == 0)
        {
            cout << "No events found" << endl;
            return;
        }
        int c = 0;
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].status())

            {
                cout << (i + 1) << ". Event Title: " << list[i].getTitle() << endl;
                cout << "   Description: " << list[i].getDesc() << endl;
                cout << "   Date: " << list[i].getDate() << endl;
                cout << "   Status: Completed" << endl;
                cout << "---------------------------------" << endl;
                c++;
            }
        }
        if (c == 0)
        {
            cout << "None of Events are completed yet" << endl;
        }
    }
    void removeEvent(int index)
    {
        if (index <= 0 || index > list.size())
        {
            cout << "Invalid Event Index !!!!" << endl;
            return;
        }
        list.erase(list.begin() + (index - 1));
        cout << "Event removed successfully" << endl;
    }
    bool isEmpty()
    {
        return list.empty();
    }
};
int main()
{
    reminder rm;
    while (true)
    {
        cout << "--- Welcome to Event Reminder Management System---" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. View Events " << endl;
        cout << "3. Remove Events " << endl;
        cout << "4. Change status of an Event " << endl;
        cout << "5. View completed Events " << endl;
        cout << "6. Exit" << endl;

        int ch;
        cin >> ch;

        switch (ch)
        {
        case 1:

            rm.addEvent();
            break;
        case 2:
            rm.viewEvent();
            break;
        case 3:
            if (rm.isEmpty())
            {
                cout << "No Events found , nothing to remove !!!" << endl;
            }
            else
            {
                rm.viewEvent();
                int index;
                cout << "Enter the index to be removed !!!" << endl;
                cin >> index;
                rm.removeEvent(index);
            }

            break;
        case 4:
            rm.viewEvent();
            int index;
            cout << "Enter the index of event to be marked " << endl;
            cin >> index;
            rm.markEventasDone(index);
            break;
        case 5:
            rm.viewCompletedEvents();
            break;
        case 6:
            return 0;
            break;

        default:
            break;
        }
    }

    return 0;
}