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
    void addStudent(int id, const std::string& name, int age) {
        auto student = std::make_shared<Student>();
        student->id = id;
        student->name = name;
        student->age = age;
        students.push_back(student);
    }

    void removeStudent(int id) {
        students.erase(
            std::remove_if(students.begin(), students.end(),
                [id](const std::shared_ptr<Student>& student) {
                    return student->id == id;
                }),
            students.end());
    }

    std::shared_ptr<Student> getStudent(int id) {
        auto it = std::find_if(students.begin(), students.end(),
            [id](const std::shared_ptr<Student>& student) {
                return student->id == id;
            });
        if (it != students.end()) {
            return *it;
        }
        else {
            return nullptr;
        }
    }
};

int main() {
    StudentDatabase database;

    database.addStudent(1, "Ivanov", 20);
    database.addStudent(2, "Petrov", 22);
    database.addStudent(3, "Sidorov", 21);

    std::shared_ptr<Student> student = database.getStudent(2);
    if (student != nullptr) {
        std::cout << "ID: " << student->id << ", Name: " << student->name << ", Age: " << student->age << std::endl;
    }
    else {
        std::cout << "The student was not found." << std::endl;
    }

    database.removeStudent(2);

    student = database.getStudent(2);
    if (student != nullptr) {
        std::cout << "ID: " << student->id << ", Name: " << student->name << ", Age: " << student->age << std::endl;
    }
    else {
        std::cout << "The student was not found." << std::endl;
    }

    return 0;
}
