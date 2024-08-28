#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


double gradeToPoint(string grade) {
    if (grade == "A" || grade == "a") return 4.0;
    else if (grade == "A-" || grade == "a-") return 3.7;
    else if (grade == "B+" || grade == "b+") return 3.3;
    else if (grade == "B" || grade == "b") return 3.0;
    else if (grade == "B-" || grade == "b-") return 2.7;
    else if (grade == "C+" || grade == "c+") return 2.3;
    else if (grade == "C" || grade == "c") return 2.0;
    else if (grade == "C-" || grade == "c-") return 1.7;
    else if (grade == "D+" || grade == "d+") return 1.3;
    else if (grade == "D" || grade == "d") return 1.0;
    else if (grade == "F" || grade == "f") return 0.0;
    else {
        cout << "Invalid grade entered!" << endl;
        return -1.0; 
    }
}


double calculateSemesterGPA(int numCourses) {
    vector<double> creditHours(numCourses);
    vector<string> grades(numCourses);
    double totalGradePoints = 0;
    double totalCredits = 0;

  
    for (int i = 0; i < numCourses; ++i) {
        cout << "Enter the credit hours for course " << i + 1 << ": ";
        cin >> creditHours[i];
        cout << "Enter the grade received for course " << i + 1 << " (e.g., A, B+, C, etc.): ";
        cin >> grades[i];

        double gradePoint = gradeToPoint(grades[i]);
        if (gradePoint < 0) return -1.0;

        totalGradePoints += gradePoint * creditHours[i];
        totalCredits += creditHours[i];
    }

    double GPA = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits for this semester: " << totalCredits << endl;
    cout << "Total Grade Points for this semester: " << totalGradePoints << endl;
    cout << "GPA for this semester: " << GPA << endl;

    return GPA;
}


void calculateCGPA() {
    int numSemesters;
    cout << "Enter the number of semesters: ";
    cin >> numSemesters;

    double totalGradePoints = 0;
    double totalCredits = 0;

    for (int semester = 1; semester <= numSemesters; ++semester) {
        cout << "\n--- Semester " << semester << " ---\n";
        int numCourses;
        cout << "Enter the number of courses for semester " << semester << ": ";
        cin >> numCourses;

        double GPA = calculateSemesterGPA(numCourses);
        if (GPA < 0) return; 


        totalGradePoints += GPA * numCourses;
        totalCredits += numCourses;
    }

    double CGPA = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\nTotal Courses across all semesters: " << totalCredits << endl;
    cout << "Total Grade Points across all semesters: " << totalGradePoints << endl;
    cout << "Cumulative GPA (CGPA): " << CGPA << endl;
}

int main() {
    char choice;
    do {
        calculateCGPA();
        cout << "\nDo you want to calculate CGPA for another student? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Exiting the program." << endl;
    return 0;
}
