#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Priority { LOW, MEDIUM, HIGH };

class Task {
public:
    virtual void display() const = 0;
    virtual bool isCompleted() const = 0;
    virtual void markAsCompleted() = 0;
};

class TaskItem : public Task {
private:
    string title;
    string description;
    bool completed;
    Priority priority;

public:
    TaskItem(const string& title, const string& description, Priority priority)
        : title(title), description(description), completed(false), priority(priority) {}

    void display() const override {
        cout << "  Title: " << title
            << "\n  Description: " << description
            << "\n  Completed: " << (completed ? "Yes" : "No")
            << "\n  Priority: " << (priority == Priority::LOW ? "LOW" :
                priority == Priority::MEDIUM ? "MEDIUM" : "HIGH") << "\n";
    }

    bool isCompleted() const override {
        return completed;
    }

    void markAsCompleted() override {
        completed = true;
    }

    Priority getPriority() const {
        return priority;
    }

    friend bool compareTasksByPriority(const TaskItem& a, const TaskItem& b);

    bool operator==(const TaskItem& other) const {
        return priority == other.priority;
    }

    bool operator!=(const TaskItem& other) const {
        return !(*this == other);
    }

    bool operator<(const TaskItem& other) const {
        return priority < other.priority;
    }

    bool operator>(const TaskItem& other) const {
        return priority > other.priority;
    }
};

bool compareTasksByPriority(const TaskItem& a, const TaskItem& b) {
    return a < b;
}

class Note {
    string content;

public:
    Note() = default;
    Note(const string& content) : content(content) {}

    void display() const {
        cout << "Note: " << content << "\n";
    }
};

class TaskList {
    vector<TaskItem> tasks;
    vector<Note> notes;

public:
    void addTask(const TaskItem& task) {
        tasks.push_back(task);
    }

    void addNote(const Note& note) {
        notes.push_back(note);
    }

    void displayAll() const {
        cout << "\nTasks:\n";
        for (const auto& task : tasks) {
            task.display();
            cout << "\n";
        }
        cout << "Notes:\n";
        for (const auto& note : notes) {
            note.display();
            cout << "\n";
        }
    }

    TaskItem& getTask(int index) {
        if (index < 0 || index >= tasks.size()) {
            throw out_of_range("Index out of range");
        }
        return tasks[index];
    }

    Note getNote(int index) const {
        if (index < 0 || index >= notes.size()) {
            throw out_of_range("Index out of range");
        }
        return notes[index];
    }

    static int totalTasks(const TaskList& taskList) {
        return taskList.tasks.size();
    }
};

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Add Task\n";
    cout << "2. Add Note\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Display All Tasks and Notes\n";
    cout << "5. Compare Tasks by Priority\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    TaskList taskList;
    int option;
    do {
        displayMenu();
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1: {
            string title, description;
            int priority;
            cout << "Enter task title: ";
            getline(cin, title);
            cout << "Enter task description: ";
            getline(cin, description);
            cout << "Enter task priority (0: LOW, 1: MEDIUM, 2: HIGH): ";
            cin >> priority;
            cin.ignore();
            taskList.addTask(TaskItem(title, description, static_cast<Priority>(priority)));
            break;
        }
        case 2: {
            string content;
            cout << "Enter note content: ";
            getline(cin, content);
            taskList.addNote(Note(content));
            break;
        }
        case 3: {
            int index;
            cout << "Enter task index to mark as completed: ";
            cin >> index;
            cin.ignore();
            try {
                taskList.getTask(index).markAsCompleted();
            }
            catch (const out_of_range& e) {
                cout << e.what() << "\n";
            }
            break;
        }
        case 4:
            taskList.displayAll();
            break;
        case 5: {
            int index1, index2;
            cout << "Enter first task index to compare: ";
            cin >> index1;
            cout << "Enter second task index to compare: ";
            cin >> index2;
            cin.ignore();
            try {
                TaskItem& task1 = taskList.getTask(index1);
                TaskItem& task2 = taskList.getTask(index2);
                if (compareTasksByPriority(task1, task2)) {
                    cout << "  First task has lower priority.\n";
                }
                else {
                    cout << "  First task has higher priority.\n";
                }
            }
            catch (const out_of_range& e) {
                cout << e.what() << "\n";
            }
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "  Invalid option. Try again.\n";
        }
    } while (option != 0);

    return 0;
}
