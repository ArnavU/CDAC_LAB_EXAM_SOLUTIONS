#include <iostream>
using namespace std;

namespace exceptions {
    class InvalidStudentTypeException {
        private: 
        string message;
        public:
        InvalidStudentTypeException(const string &message) { this->message = message; }
        string getMessage() { return this->message; }
    };

    class MaxStudentException {
        private:
        string message;
        public: 
        MaxStudentException(const string& message) { this->message = message; }
        string getMessage() { return this->message; }
    };

    class StudentNotFoundException {
        private:
        string message;
        public: 
        StudentNotFoundException(const string& message) { this->message = message; }
        string getMessage() { return this->message; }
    };

    class StudentIdAlreadyExistException {
        private:
        string message;
        public: 
        StudentIdAlreadyExistException(const string& message) { this->message = message; }
        string getMessage() { return this->message; }
    };

    class InvalidMenuChoiceException {
        private:
        string message;
        public: 
        InvalidMenuChoiceException(const string& message) { this->message = message; }
        string getMessage() { return this->message; }
    };
}

using namespace exceptions;

class Student {
    int studentId;
    string studentName, mobileNo;

    public:
    Student() : studentId(0), studentName(""), mobileNo("") {}
    Student(int studentId, string name, string mobileNo) : studentId(studentId), studentName(name), mobileNo(mobileNo) {}
    void setStudentId(int studentId) { this->studentId = studentId; }
    void setStudentName(int studentName) { this->studentName = studentName; }
    void setMobileNo(int mobileNo) { this->mobileNo = mobileNo; }
    int getStudentId() const { return studentId; }
    string getStudentName() const { return studentName; }
    string getMobileNo() const { return mobileNo; }

    virtual void acceptRecord(Student* stu[], int idx) {
        cout<<"Enter student details: "<<endl;
        cout<<"Student id: ";
        cin>>studentId;
        for(int i=0; i<idx; i++) {
            if(stu[i]->getStudentId() == studentId) {
                delete stu[i];
                throw StudentIdAlreadyExistException("Id already exists");
            }
        }
        cout<<"Student name: ";
        cin>>studentName;
        cout<<"Mobile no.: ";
        cin>>mobileNo;
    }

    virtual void displayRecord() const {
        cout<<"\nStudent: "<<studentId<<endl;
        cout<<"Name: "<<studentName<<endl;
        cout<<"Mobile no: "<<mobileNo<<endl;
    }

};

class RegularStudent : public Student {
    int semister;
    static const string studentType;

    public:
    RegularStudent() : semister(0) {}
    RegularStudent(int studentId, string studentName, string mobileNo, int semister) : Student(studentId, studentName, mobileNo), semister(semister) {}

    void setSemister(int semister) { this->semister = semister; }
    int getSemister() const { return semister; }
    string getStudentType() const { return studentType; }

    void acceptRecord(Student* stu[], int idx) {
        Student::acceptRecord(stu, idx);
        cout<<"Semister: ";
        cin>>semister;
    }

    void displayRecord() const {
        Student::displayRecord();
        cout<<"Student type: "<<studentType<<endl;
        cout<<"Semister: "<<semister<<endl;
    }

};
const string RegularStudent :: studentType = "Regular Student";

class DistanceStudent : public Student {
    string studyCenter;
    static const string studentType;

    public:
    DistanceStudent() : studyCenter("") {}
    DistanceStudent(int studentId, string studentName, string mobileNo, string studyCenter) : Student(studentId, studentName, mobileNo), studyCenter(studyCenter) {}

    void setStudyCenter(string studyCenter) { this->studyCenter = studyCenter; }
    string getStudyCenter() const { return this->studyCenter; }
    string getStudentType() const { return studentType; }

    void acceptRecord(Student* stu[], int idx) {
        Student::acceptRecord(stu, idx);
        cout<<"Study center: ";
        cin>>studyCenter;
    }

    void displayRecord() const {
        Student::displayRecord();
        cout<<"Student type: "<<studentType<<endl;
        cout<<"Study center: "<<studyCenter<<endl;
    }
};
const string DistanceStudent :: studentType = "Distance Student";

int menuList() {
    int choice;
    cout<<"\nEnter your choice: "<<endl;
    cout<<"0. End."<<endl;
    cout<<"1. Add new student."<<endl;
    cout<<"2. Display all students."<<endl;
    cout<<"3. Search by ID."<<endl;
    cout<<"4. Display type."<<endl;
    cout<<"5. Display regular students."<<endl;
    cin>>choice;
    return choice;
}

// *********************(getting instance of student type) factory design patter ******************** 
class StudentFactory {
    public:
    static Student* getInstance(int choice) {
        Student* stu = NULL;
        switch(choice) {
            case 1:
                stu = new RegularStudent();
                break;
            case 2:
                stu = new DistanceStudent();
                break;
        }
        return stu;
    }
};

namespace helpers {
    int inputStudentType() {
        int choice;
        cout<<"\n1. Regular Student. "<<endl;
        cout<<"2. Distance Student. "<<endl;
        cin>>choice;
        if(choice>2 || choice<1) {
            throw InvalidStudentTypeException("Invalid student type.");
        } 
        return choice;
    }

    void displayAllStudents(Student* stu[], int idx) {
        cout<<"\nDisplaying all students: "<<endl;
        for(int i=0; i<idx; i++) {
            // if(dynamic_cast<RegularStudent*>(stu[i]) != NULL) {
            //     stu[i]->displayRecord();
            // } else if(dynamic_cast<DistanceStudent*>(stu[i]) != NULL) {
            //     stu[i]->displayRecord();
            // }
            stu[i]->displayRecord();
        }
    }

    Student* searchStudentById(Student* stu[], int idx) {
        cout<<"\nEnter student id: ";
        int id;
        cin>>id;
        for(int i=0; i<idx; i++) {
            if(stu[i]->getStudentId() == id) {
                return stu[i];
            }
        }
        return nullptr;
    }

    string findStudentType(Student* student) {
        string studentType = "";
        if(dynamic_cast<RegularStudent*>(student)!=nullptr) {
            RegularStudent* reg = dynamic_cast<RegularStudent*>(student);
            studentType = reg->getStudentType();
        } else if(dynamic_cast<DistanceStudent*>(student)!=nullptr) {
            DistanceStudent* dist = dynamic_cast<DistanceStudent*>(student);
            studentType = dist->getStudentType();
        }
        return studentType;
    }
}
using namespace helpers;

int main() {
    int choice;
    Student* stu[5];
    int idx = 0;
    int st;
    Student* student;
    string studentType;
    while((choice = menuList()) != 0) {
        try {
            switch(choice) {
                case 1: // input student
                    if(idx>=5) {
                        throw MaxStudentException("Maximum 5 students reachec.");
                    }
                    st = inputStudentType();
                    stu[idx] = ::StudentFactory::getInstance(st);
                    stu[idx]->acceptRecord(stu, idx);
                    idx++;
                    break;                
                case 2: // display all students
                    displayAllStudents(stu, idx);
                    break;
                case 3: // Search student by id
                    student = searchStudentById(stu, idx);
                    if(student != nullptr) {
                        student->displayRecord();
                    } else {
                        throw StudentNotFoundException("No student found with give id");
                    }
                    break;
                case 4: // display student type by id
                    student = searchStudentById(stu, idx);
                    if(student != nullptr) {
                        studentType = findStudentType(student);
                        cout<<"Student type is: "<<studentType<<endl;
                    } else {
                        throw StudentNotFoundException("No student found with give id");
                    }
                    break;
                case 5: // display regular students
                    for(int i=0; i<idx; i++) {
                        cout<<"\n\nDisplaying regular students: "<<endl;
                        if(findStudentType(stu[i]) == "Regular Student") {
                            stu[i]->displayRecord();
                            cout<<endl;
                        }
                    }
                    break;
                default: 
                    throw InvalidMenuChoiceException("Invalid menue selected.");
            }
        } catch(InvalidStudentTypeException &ex) {
            cout<<ex.getMessage()<<endl;
        } catch(MaxStudentException &ex) {
            cout<<ex.getMessage()<<endl;
        } catch(StudentNotFoundException &ex) {
            cout<<ex.getMessage()<<endl;
        } catch(StudentIdAlreadyExistException &ex) {
            cout<<ex.getMessage()<<endl;
        } catch(InvalidMenuChoiceException &ex) {
            cout<<ex.getMessage()<<endl;
        } catch(...) {
            cout<<"Some unknown exception occured!!!";
        }
    }

    // deallocating memory
    for(int i=0; i<idx; i++) {
        delete stu[i];
    }

    return 0;
}