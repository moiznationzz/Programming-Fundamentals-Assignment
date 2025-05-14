#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
    string name;
    int id;
    float gpa;

    void input() {
        cout << "Enter student ID: ";
        cin >> id;
        cout << "Enter student GPA: ";
        cin >> gpa;
        cin.ignore();
        cout << "Enter student name: ";
        getline(cin, name);
    }

    void display() const {
        cout << "ID: " << id << " | Name: " << name << " | GPA: " << gpa << endl;
    }

    // Write to file
    void save(ofstream &fout) const {
        fout << id << "," << gpa << "," << name << "\n";
    }

    // Read from file
    static Student load(ifstream &fin) {
        Student s;
        string line;
        getline(fin, line);
        if (!line.empty()) {
            size_t p1 = line.find(',');
            size_t p2 = line.find(',', p1 + 1);
            s.id = stoi(line.substr(0, p1));
            s.gpa = stof(line.substr(p1 + 1, p2 - p1 - 1));
            s.name = line.substr(p2 + 1);
        }
        return s;
    }
};

// Global student list
vector<Student> students;

// Load all from file
void loadFromFile(const string &filename) {
    ifstream fin(filename);
    if (!fin) return;
    students.clear();
    while (fin.peek() != EOF) {
        Student s = Student::load(fin);
        if (!s.name.empty())
            students.push_back(s);
    }
    fin.close();
}

// Save all to file
void saveToFile(const string &filename) {
    ofstream fout(filename);
    for (const auto &s : students)
        s.save(fout);
    fout.close();
}

// Add student
void addStudent() {
    Student s;
    s.input();
    students.push_back(s);
    cout << "Student added!\n";
}

// Delete student by ID
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    auto it = remove_if(students.begin(), students.end(), [id](Student &s) { return s.id == id; });
    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student deleted!\n";
    } else {
        cout << "Student not found!\n";
    }
}

// View all students
void showStudents() {
    if (students.empty()) {
        cout << "No student records!\n";
        return;
    }
    for (const auto &s : students)
        s.display();
}

// Sort by GPA
void sortByGPA() {
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.gpa > b.gpa; });
    cout << "Sorted by GPA (highest first).\n";
}

// Sort by Name
void sortByName() {
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.name < b.name; });
    cout << "Sorted by Name (A-Z).\n";
}

// Search by Name
void searchByName() {
    string key;
    cin.ignore();
    cout << "Enter name to search: ";
    getline(cin, key);
    for (const auto &s : students)
        if (s.name.find(key) != string::npos)
            s.display();
}

// Filter by GPA
void filterByGPA() {
    float minGPA;
    cout << "Enter minimum GPA: ";
    cin >> minGPA;
    for (const auto &s : students)
        if (s.gpa >= minGPA)
            s.display();
}

int main() {
    string filename = "students.txt";
    loadFromFile(filename);

    while (true) {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Sort by GPA\n";
        cout << "5. Sort by Name\n";
        cout << "6. Search by Name\n";
        cout << "7. Filter by GPA\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: showStudents(); break;
            case 3: deleteStudent(); break;
            case 4: sortByGPA(); break;
            case 5: sortByName(); break;
            case 6: searchByName(); break;
            case 7: filterByGPA(); break;
            case 0: saveToFile(filename); return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
