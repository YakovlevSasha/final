#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>

using namespace std;

struct ToDo {
    string title;
    int priority;
    string description;
    string dueDate; // формат YYYY-MM-DD HH:MM
};

vector<ToDo> toDoList;

void addToDo() {
    ToDo newToDo;
    cout << "--> Введіть назву: ";
    cin.ignore();
    getline(cin, newToDo.title);
    cout << "--> Введіть пріоритет (1-5): ";
    cin >> newToDo.priority;
    cout << "--> Введіть опис: ";
    cin.ignore();
    getline(cin, newToDo.description);
    cout << "--> Введіть дату і час виконання (YYYY-MM-DD HH:MM): ";
    getline(cin, newToDo.dueDate);
    toDoList.push_back(newToDo);
}

void deleteToDo() {
    int index;
    cout << "--> Введіть індекс завдання для видалення: ";
    cin >> index;
    if (index >= 0 && index < toDoList.size()) {
        toDoList.erase(toDoList.begin() + index);
        cout << "** Завдання видалено." << endl;
    }
    else {
        cout << "** Невірний індекс." << endl;
    }
}

void editToDo() {
    int index;
    cout << "--> Введіть індекс завдання для редагування: ";
    cin >> index;
    if (index >= 0 && index < toDoList.size()) {
        cout << "--> Введіть нову назву: ";
        cin.ignore();
        getline(cin, toDoList[index].title);
        cout << "--> Введіть новий пріоритет (1-5): ";
        cin >> toDoList[index].priority;
        cout << "--> Введіть новий опис: ";
        cin.ignore();
        getline(cin, toDoList[index].description);
        cout << "--> Введіть нову дату і час виконання (YYYY-MM-DD HH:MM): ";
        getline(cin, toDoList[index].dueDate);
        cout << "** Завдання відредаговано." << endl;
    }
    else {
        cout << "** Невірний індекс." << endl;
    }
}

void searchToDo() {
    int option;
    string searchStr;
    int searchPriority;

    cout << "Пошук за:  [1]Назвою [2]Пріоритетом [3]Описом [4]Датою виконання\n";
    cout << "--> Введіть опцію: ";
    cin >> option;

    cin.ignore();

    switch (option) {
    case 1:
        cout << "--> Введіть назву для пошуку: ";
        getline(cin, searchStr);
        for (const auto& task : toDoList) {
            if (task.title.find(searchStr) != string::npos) {
                cout << "Знайдено: " << task.title << ", Пріоритет: " << task.priority
                    << ", Виконати до: " << task.dueDate << endl;
            }
        }
        break;
    case 2:
        cout << "--> Введіть пріоритет для пошуку: ";
        cin >> searchPriority;
        for (const auto& task : toDoList) {
            if (task.priority == searchPriority) {
                cout << "Знайдено: " << task.title << ", Пріоритет: " << task.priority
                    << ", Виконати до: " << task.dueDate << endl;
            }
        }
        break;
    case 3:
        cout << "--> Введіть опис для пошуку: ";
        getline(cin, searchStr);
        for (const auto& task : toDoList) {
            if (task.description.find(searchStr) != string::npos) {
                cout << "Знайдено: " << task.title << ", Пріоритет: " << task.priority
                    << ", Виконати до: " << task.dueDate << endl;
            }
        }
        break;
    case 4:
        cout << "--> Введіть дату для пошуку (YYYY-MM-DD): ";
        getline(cin, searchStr);
        for (const auto& task : toDoList) {
            if (task.dueDate.substr(0, 10) == searchStr) {
                cout << "Знайдено: " << task.title << ", Пріоритет: " << task.priority
                    << ", Виконати до: " << task.dueDate << endl;
            }
        }
        break;
    default:
        cout << "** Невірна опція." << endl;
    }
}

void displayToDoList(int period) {
    string today = "2024-06-25"; // поточна дата(приклад)
    string currentYear = today.substr(0, 4);
    string currentMonth = today.substr(5, 2);
    string currentDay = today.substr(8, 2);
    cout << endl;
    for (const auto& task : toDoList) {
        bool display = false;
        string taskYear = task.dueDate.substr(0, 4);
        string taskMonth = task.dueDate.substr(5, 2);
        string taskDay = task.dueDate.substr(8, 2);
        switch (period) {
        case 1: // День
            if (taskYear == currentYear && taskMonth == currentMonth && taskDay == currentDay) {
                display = true;
            }
            break;
        case 2: // Тиждень
            if (taskYear == currentYear && taskMonth == currentMonth && stoi(taskDay) >= stoi(currentDay) && stoi(taskDay) < stoi(currentDay) + 7) {
                display = true;
            }
            break;
        case 3: // Місяць
            if (taskYear == currentYear && taskMonth == currentMonth) {
                display = true;
            }
            break;
        }
        if (display) {
            cout << "Назва: " << task.title << ", Пріоритет: " << task.priority
                << ", Виконати до: " << task.dueDate << endl;
        }
    }
    cout << endl;
}

void sortToDoList(int criterion) {
    switch (criterion) {
    case 1: // Сортування за пріоритетом
        sort(toDoList.begin(), toDoList.end(), [](const ToDo& a, const ToDo& b) {
            return a.priority < b.priority; 
            });
        break;
    case 2: // Сортування за датою та часом виконання
        sort(toDoList.begin(), toDoList.end(), [](const ToDo& a, const ToDo& b) {
            return a.dueDate < b.dueDate; 
            });
        break;
    default:
        cout << "** Невірний критерій." << endl; 
    }
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) { 
        for (const auto& task : toDoList) {
            file << task.title << '\n'; 
            file << task.priority << '\n'; 
            file << task.description << '\n';
            file << task.dueDate << '\n'; 
        }
        file.close(); 
        cout << "** Завдання збережено у файл." << endl; 
    }
    else {
        cout << "** Неможливо відкрити файл." << endl; 
    }
}

void loadFromFile(const string& filename) {
    ifstream file(filename); 
    if (file.is_open()) { 
        toDoList.clear();
        ToDo task;
        while (getline(file, task.title)) { 
            file >> task.priority;
            file.ignore();
            getline(file, task.description);
            getline(file, task.dueDate); 
            toDoList.push_back(task); 
        }
        file.close(); 
        cout << "** Завдання завантажено з файлу." << endl; 
    }
    else {
        cout << "** Неможливо відкрити файл." << endl; 
    }
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << " Програма «Список справ»\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    int option;
    do {
        cout << "-------------------------\n" << "[1]Додати завдання\n[2]Видалити завдання\n[3]Редагувати завдання\n[4]Пошук завдання\n[5]Показати список завдань\n[6]Сортувати список завдань\n[7]Зберегти у файл\n[8]Завантажити з файлу\n[0]Вийти\n" << "-------------------------\n" ;
        cout << "--> Введіть опцію: ";
        cin >> option;
        switch (option) {
        case 1: addToDo(); break;
        case 2: deleteToDo(); break;
        case 3: editToDo(); break;
        case 4: searchToDo(); break;
        case 5: {
            int period;
            cout << "Показати на: [1]День [2]Тиждень [3]Місяць\n";
            cout << "--> Введіть період: ";
            cin >> period;
            displayToDoList(period);
            break;
        }
        case 6: {
            int criterion;
            cout << "Сортувати за: [1]Пріоритет [2]Дата виконання\n";
            cout << "--> Введіть критерій: ";
            cin >> criterion;
            sortToDoList(criterion);
            break;
        }
        case 7: saveToFile("saves.txt"); break;
        case 8: loadFromFile("saves.txt"); break;
        case 0: cout << "Вихід...\n"; break;
        default: cout << "** Невірна опція.\n";
        }
    } while (option != 0);
    return 0;
}
