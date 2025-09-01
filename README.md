# 🗓️ Event Reminder System (Qt + C++)

A simple **Event Reminder & Task Manager** built with **C++ and Qt Widgets**.  
The application lets users add, remove, and filter events with descriptions and due dates.  
Events are **automatically saved** to a JSON file and **restored** on the next run.  

---

## ✨ Features
- ➕ **Add Events** with a title, description, date, and completion status.  
- 🖊️ **Edit in place** – double-click cells to edit directly.  
- ✅ **Mark events as completed** (checkbox toggle).  
- 🗑️ **Remove selected events** with confirmation.  
- 🔍 **Filter events** (All, Completed, Pending).  
- 📝 **Word wrapping** in the description column (multi-line support).  
- 💾 **Persistent storage** – events are saved to a JSON file and reloaded automatically.  

---

## 🛠️ Technologies Used
- **C++17**  
- **Qt 5/6 Widgets**  
- **QTableWidget** for task table  
- **QJsonDocument, QJsonArray, QJsonObject** for persistence  
- **QStandardPaths** for cross-platform file storage  

---

## 📂 Project Structure
```plaintext
EventReminderSystem/
│
├── main.cpp                # Application entry point
├── mainwindow.h            # MainWindow class header
├── mainwindow.cpp          # MainWindow logic
├── mainwindow.ui           # Qt Designer UI file
├── EventReminderSystem.pro # Qt project file
├── resources/              # Icons, images, etc. (optional)
└── README.md               # Project documentation


---

## 🚀 Getting Started

### 1️⃣ Clone the repository
```bash
git clone https://github.com/<your-username>/EventReminderSystem.git
cd EventReminderSystem

2️⃣ Open the project

Open the .pro file in Qt Creator, or

Use qmake + make in terminal.

3️⃣ Run the project

qmake && make
./EventReminderSystem   # Linux/Mac
EventReminderSystem.exe # Windows


📁 Where are my events stored?
Events are saved in a JSON file named events.json under your system’s AppData path:

Windows:
C:\Users\<User>\AppData\Roaming\EventReminderSystem\events.json

Linux:
~/.local/share/EventReminderSystem/events.json

macOS:
~/Library/Application Support/EventReminderSystem/events.json

👉 Open it in a text editor to inspect your saved events.

🧪 How to Test Persistence

Run the app and add a few events.

Close the app (this saves to events.json).

Reopen the app → your events should reappear automatically.

Check the events.json file to confirm.
