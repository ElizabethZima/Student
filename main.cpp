#include <iostream>
#include <vector>
#include <memory>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
private:
    std::vector<std::shared_ptr<Student>> students;

public:
    void addStudent(const Student& student) {
        students.push_back(std::make_shared<Student>(student));
    }

    void removeStudentById(int id) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if ((*it)->id == id) {
                students.erase(it);
                return;
            }
        }
        std::cout << "Student with ID " << id << " not found" << std::endl;
    }

    std::shared_ptr<Student> getStudentById(int id) {
        for (const auto& student : students) {
            if (student->id == id) {
                return student;
            }
        }
        return nullptr;
    }
};

int main() {
    StudentDatabase database;

    Student student1{1, "Alice", 20};
    Student student2{2, "Bob", 21};

    database.addStudent(student1);
    database.addStudent(student2);

    std::shared_ptr<Student> student = database.getStudentById(1);
    if (student) {
        std::cout << "Student with ID 1: " << student->name << ", age: " << student->age << std::endl;
    }

    database.removeStudentById(3); // Student with ID 3 not found
    database.removeStudentById(2);

    student = database.getStudentById(2);
    if (!student) {
        std::cout << "Student with ID 2 not found" << std::endl;
    }

    return 0;
}
