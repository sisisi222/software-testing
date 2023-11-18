#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
//test
// Student object to store in studentsInfo.csv
class Student {
private:
  string _name;
  string _uid;
  string _email;
  int _presentationGrade;
  int _essayGrade;
  int _projectGrade;

public:
  // Constructor for student object
  Student(string name, string uid, string email, int presentationGrade,
          int essayGrade, int projectGrade)
      : _name(name), _uid(uid), _email(email),
        _presentationGrade(presentationGrade), _essayGrade(essayGrade),
        _projectGrade(projectGrade){};

  // Getter and setter for student name
  string getName() { return _name; }
  void setName(string name) { _name = name; }

  // Getter and setter for student UID
  string getUID() { return _uid; }
  void setUID(string uid) { _uid = uid; }

  // Getter and setter for student email
  string getEmail() { return _email; }
  void setEmail(string email) { _email = email; }

  // Getter and setter for student presentation grade
  int getPresentationGrade() { return _presentationGrade; }
  void setPresentationGrade(int presentationGrade) {
    _presentationGrade = presentationGrade;
  }

  // Getter and setter for student essay grade
  int getEssayGrade() { return _essayGrade; }
  void setEssayGrade(int essayGrade) { _essayGrade = essayGrade; }

  // Getter and setter for student project grade
  int getProjectGrade() { return _projectGrade; }
  void setProjectGrade(int projectGrade) { _projectGrade = projectGrade; }

  // Prints all student info as a string
  void toString() {
    cout << "UID: " << _uid << "\n"
         << "Name: " << _name << "\n"
         << "Email: " << _email << "\n"
         << "Grade Presentation: " << to_string(_presentationGrade) << "\n"
         << "Grade Essay: " << to_string(_essayGrade) << "\n"
         << "Grade Project: " << to_string(_projectGrade) << "\n";
  }
};


bool readFile(vector<Student> &students, string fileName) {
    ifstream fin;
    fin.open(fileName);
    string line, temp;
    int lineNum = 0;

    getline(fin, line); // Skip header
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> row;

        while (getline(ss, temp, ',')) {
            row.push_back(temp); 
        }

        if (row.size() != 6) {
            cout << "Incorrect number of fields in line " << lineNum + 1 << ": " << line << "\\n";
            return false;
        }

        try {
            Student newStudent(row[0], row[1], row[2], stoi(row[3]), stoi(row[4]), stoi(row[5]));
            students.push_back(newStudent);
        } catch (const std::invalid_argument &e) {
            cout << "Invalid argument in line " << lineNum + 1 << ": " << line << "\\n";
            return false;
        } catch (const std::out_of_range &e) {
            cout << "Out of range error in line " << lineNum + 1 << ": " << line << "\\n";
            return false;
        }

        lineNum++;
    }

    fin.close();

    return true;
}

// Writes to studentsInfo.csv
bool writeFile(vector<Student> &students, string fileName) {
  ofstream fout;
  fout.open(fileName);

  // Write header line
  fout << "Name,ID,Email,Presentation,Essay,Term Project\n";

  // Write student data
  for (Student student : students) {
    fout << student.getName() << "," << student.getUID() << ","
         << student.getEmail() << "," << student.getPresentationGrade() << ","
         << student.getEssayGrade() << "," << student.getProjectGrade() << "\n";
  }

  fout.close();

  return true;
}


// Searches for a student by name
int searchStudentByName(vector<Student> &students, string name) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i].getName() == name) {
      return i;
    }
  }

  return -1;
}

// Searches for a student by UID
int searchStudentByUID(vector<Student> &students, string uid) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i].getUID() == uid) {
      return i;
    }
  }

  return -1;
}

// Searches for a student by email
int searchStudentByEmail(vector<Student> &students, string email) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i].getEmail() == email) {
      return i;
    }
  }

  return -1;
}

// Checks for valid name input
bool validateName(string input) {
  if (input.size() == 0 || input == " ") {
    return false;
  }

  if (input.size() > 40) {
    cout << "Names must be 40 characters or less."
         << "\n";
    return false;
  }

  return true;
}

// Checks for valid UID input
bool validateUID(string input) {
  if (input.size() != 9) {
    cout << "UID must be exactly 9 characters."
         << "\n";
    return false;
  }

  if (input[0] != 'U') {
    cout << "UID must start with capital U."
         << "\n";
    return false;
  }

  return true;
}

// Checks for duplicate UID input
bool duplicateUID(vector<Student> &students, string uid) {
  if (searchStudentByUID(students, uid) != -1) {
    cout << "Duplicate UID, please input a new UID."
         << "\n";
    return true;
  }

  return false;
}

// Checks for valid email input
bool validateEmail(string input) {
  // Regex pattern ensures email has '@' and '.'
  const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

  if (input.size() == 0 || input == " ") {
    return false;
  }

  if (input.size() > 40) {
    cout << "Emails must be 40 characters or less."
         << "\n";
    return false;
  }

  if (!regex_match(input, pattern)) {
    cout << "Invalid email format. Please include '@' address and '.' domain."
         << "\n";
    return false;
  }

  return true;
}

// Checks for duplicate email input
bool duplicateEmail(vector<Student> &students, string email) {
  if (searchStudentByEmail(students, email) != -1) {
    cout << "Duplicate UID, please input a new UID."
         << "\n";
    return true;
  }

  return false;
}

// Checks for valid grade input
bool validateGrade(int input) {
  if (input < 0 || input > 4) {
    return false;
  }

  return true;
}

// Adds new student to StudentsInfo.csv
bool addStudent(vector<Student> &students) {
  string name, uid, email;
  int presentationGrade, essayGrade, projectGrade;
  cout << "Please enter the student's info:\n";

  while (true) {
    cout << "Name: ";
    getline(cin, name);
    if (!validateName(name)) {
      cout << "Invalid Name. Please enter a valid name."
           << "\n";
      continue;
    }
    break;
  }

  while (true) {
    cout << "UID: ";
    getline(cin, uid);
    if (!validateUID(uid)) {
      cout << "Invalid UID. Please enter a valid UID."
           << "\n";
    } else if (!duplicateUID(students, uid)) {
      break;
    }
  }

  while (true) {
    cout << "Email: ";
    getline(cin, email);
    if (!validateEmail(email)) {
      cout << "Invalid Email. Please enter a valid email."
           << "\n";
    } else if (!duplicateEmail(students, email)) {
      break;
    }
  }

  while (true) {
    cout << "Presentation Grade: ";
    cin >> presentationGrade;
    if (!validateGrade(presentationGrade)) {
      cout << "Invalid grade. Please enter a valid grade."
           << "\n";
      continue;
    }
    break;
  }

  while (true) {
    cout << "Essay Grade: ";
    cin >> essayGrade;
    if (!validateGrade(essayGrade)) {
      cout << "Invalid grade. Please enter a valid grade."
           << "\n";
      continue;
    }
    break;
  }

  while (true) {
    cout << "Project Grade: ";
    cin >> projectGrade;
    if (!validateGrade(projectGrade)) {
      cout << "Invalid grade. Please enter a valid grade."
           << "\n";
      continue;
    }
    break;
  }

  Student newStudent(name, uid, email, presentationGrade, essayGrade,
                     projectGrade);
  students.push_back(newStudent);

  cout << "New student successfully added!"
       << "\n";

  return true;
}

// Deletes student from studentsInfo.csv
bool deleteStudent(vector<Student> &students) {
  string deleteUID;

  cout << "Please enter the UID of the student you would like to delete: ";
  cin >> deleteUID;

  int studentIndex = searchStudentByUID(students, deleteUID);
  if (studentIndex == -1) {
    cout << "Student with the provided UID was not found!"
         << "\n";
    return false;
  }

  students.erase(students.begin() + studentIndex);
  cout << "Student successfully deleted!"
       << "\n";

  return true;
}

// Displays update menu options
void displayUpdateMenu() {
  cout << "Choose an option to update:"
       << "\n";
  cout << "0. View updated info"
       << "\n";
  cout << "1. Update name"
       << "\n";
  cout << "2. Update UID"
       << "\n";
  cout << "3. Update email"
       << "\n";
  cout << "4. Update presentation grade"
       << "\n";
  cout << "5. Update essay grade"
       << "\n";
  cout << "6. Update project grade"
       << "\n";
  cout << "7. Done."
       << "\n"
       << "\n";
}

// Updates student in studentsInfo.csv
bool updateStudentInfo(vector<Student> students) {
  string UpdateUID;

  cout << "Please enter the UID of the student you want to update: ";
  cin >> UpdateUID;

  int studentIndex = searchStudentByUID(students, UpdateUID);
  if (studentIndex == -1) {
    cout << "Student with the provided UID was not found!"
         << "\n";
    return false;
  }

  int updateChoice = -1;

  cout << "Here is the student's info:"
       << "\n"
       << "\n";
  students[studentIndex].toString();
  cout << "\n";

  while (updateChoice != 7) {
    cout << "What info would you like to change?"
         << "\n";
    displayUpdateMenu();

    cout << "> ";
    cin >> updateChoice;
    cout << "\n";

    switch (updateChoice) {
    case 0: {
      cout << "========================"
           << "\n";
      students[studentIndex].toString();
      cout << "========================"
           << "\n"
           << "\n";

      break;
    }
    case 1: {
      string updatedName;
      cin.ignore();

      while (true) {
        cout << "Please input the updated name: ";
        getline(cin, updatedName);

        if (!validateName(updatedName)) {
          cout << "Invalid name. Please provide a valid name."
               << "\n";
          continue;
        }

        break;
      }

      students[studentIndex].setName(updatedName);
      break;
    }
    case 2: {
      string updatedUID;
      bool isUIDValid = false;

      while (!isUIDValid) {
        cout << "Please enter a new UID: ";
        cin >> updatedUID;

        if (!validateUID(updatedUID)) {
          cout << "Invalid UID. Please provide a valid UID."
               << "\n";
        } else if (duplicateUID(students, updatedUID)) {
          cout << "UID already exists. Please choose a different one."
               << "\n";
        } else {
          isUIDValid = true;
        }
      }

      students[studentIndex].setUID(updatedUID);
      break;
    }
    case 3: {
      string updatedEmail;
      bool isEmailValid = false;

      while (!isEmailValid) {
        cout << "Please enter a new email: ";
        cin >> updatedEmail;

        if (!validateEmail(updatedEmail)) {
          cout << "Invalid email. Please provide a valid email."
               << "\n";
        } else if (duplicateEmail(students, updatedEmail)) {
          cout << "Email already exists. Please choose a different one."
               << "\n";
        } else {
          isEmailValid = true;
        }
      }

      students[studentIndex].setEmail(updatedEmail);
      break;
    }
    case 4: {
      int updatedPresentationGrade;
      bool isGradeValid = false;

      while (!isGradeValid) {
        cout << "Please input the updated presentation grade: ";
        cin >> updatedPresentationGrade;

        if (!validateGrade(updatedPresentationGrade)) {
          cout << "Invalid grade. Please provide a valid grade."
               << "\n";
          continue;
        }

        isGradeValid = true;
      }

      students[studentIndex].setPresentationGrade(updatedPresentationGrade);
      break;
    }
    case 5: {
      int updatedEssayGrade;
      bool isGradeValid = false;

      while (!isGradeValid) {
        cout << "Please enter the updated essay grade: ";
        cin >> updatedEssayGrade;

        if (!validateGrade(updatedEssayGrade)) {
          cout << "Invalid grade. Please provide a valid grade."
               << "\n";
          continue;
        }

        isGradeValid = true;
      }

      students[studentIndex].setEssayGrade(updatedEssayGrade);
      break;
    }
    case 6: {
      int updatedProjectGrade;
      bool isGradeValid = false;

      while (!isGradeValid) {
        cout << "Please input the updated project grade: ";
        cin >> updatedProjectGrade;

        if (!validateGrade(updatedProjectGrade)) {
          cout << "Invalid grade. Please provide a valid grade."
               << "\n";
          continue;
        }

        isGradeValid = true;
      }

      students[studentIndex].setProjectGrade(updatedProjectGrade);
      break;
    }
    case 7: {
      cout << "Student successfully updated!"
           << "\n"
           << "\n";
      break;
    }
    default: {
      cout << "Invalid choice. Please enter a valid choice."
           << "\n";
      break;
    }
    }
  }
  writeFile(students, "studentsInfo.csv");

  return true;
}

// Displays main menu options
void displayMainMenu() {
  cout << "\n";
  cout << "Please choose one of our options below:"
       << "\n";
  cout << "\n";
  cout << "======================"
       << "\n";
  cout << "1. Add a student"
       << "\n";
  cout << "2. Delete a student"
       << "\n";
  cout << "3. Get student info"
       << "\n";
  cout << "4. Update student info"
       << "\n";
  cout << "5. Exit the program"
       << "\n";
  cout << "======================"
       << "\n"
       << "\n";
  cout << "Enter your choice: ";
}

// Starts program by prompting user with what to do
int main() {
  vector<Student> students;
  readFile(students, "studentsInfo.csv");
  int choice = 0;

  cout << "Welcome to the class-roll maintenance system by Team Polk!"
       << "\n";

  while (choice != 5) {
    displayMainMenu();

    cin >> choice;
    if (!cin){
      cin.clear(); // clear any error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }


    switch (choice) {
    case 1: { // Adds a new student to studentsInfo.csv
      cin.ignore();
      addStudent(students);
      break;
    }
    case 2: { // Deletes student from studentsInfo.csv
      deleteStudent(students);
      break;
    }
    case 3: { // Print all info of a student
      string getInfoUID;
      cout << "Please enter the UID of the student you would like to get the "
              "info of: ";
      cin >> getInfoUID;

      int studentIndex = searchStudentByUID(students, getInfoUID);
      if (studentIndex == -1) {
        cout << "Student UID not found!"
             << "\n";
        break;
      }

      cout << "\n"
           << "========================"
           << "\n";
      students[studentIndex].toString();
      cout << "========================"
           << "\n"
           << "\n";

      break;
    }
    case 4: { // Updates a student's info
      updateStudentInfo(students);
      break;
    }
    case 5: {
      writeFile(students, "studentsInfo.csv");
      cout << "Thank you for using the class-roll maintenance by Team Polk!"
           << "\n";
      break;
    }
    default: {
      cout << "Invalid choice! Please choose again."
           << "\n";
    }
    }
  }

  return 0;
}
