#include <cstring>
#include <fstream>
#include <iostream>
using std::cin, std::cout, std::endl, std::string, std::ofstream;

struct student {
    char name[50];
    char section;
    int attendance;
    char Uniroll_no[15];
    double maths;
    double english;
    double science;
    double computer_science;
    double percent;
};

void addReport(FILE *fp, student s, long int size);
void listReport(FILE *fp, student s, long int size, double pass_per);
void modifyReport(FILE *fp, student s, long int size);
void deleteReport(FILE *fp, FILE *ft, student s, long int size);
void setPassPercentage(double *pass_per);
void getAverage(FILE *fp, student s, long int size);
void exportReport(FILE *fp, student s, long int size, double pass_per);
void viewFailedStudents(FILE *fp, student s, long int size, double pass_per);

int main() {

    struct student s;
    long int size = sizeof(s);
    FILE *fp, *ft;

    double pass_per = 40.0;

    char choice, new_uniId[15];
    
    // declaration for .txt file
    fp = fopen("C:\\Users\\AB\\Desktop\\Mini Project\\Record.txt", "rb+");

    if (fp == NULL) {

        fp = fopen("C:\\Users\\AB\\Desktop\\Mini Project\\Record.txt", "wb+");

        if (fp == NULL) {
            cout << strerror(errno);
            puts("\nError. Cannot open file!");
            return 0;
        }
    }

    while (1) {
        system("cls");

        cout << "\t\t------ STUDENT REPORT CARD MANAGEMENT SYSTEM ------";
        cout << "\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Reports";
        cout << "\n \t\t\t 2. List   Reports";
        cout << "\n \t\t\t 3. Modify Reports";
        cout << "\n \t\t\t 4. Delete Reports";
        cout << "\n \t\t\t 5. Set Pass Percentage";
        cout << "\n \t\t\t 6. Get Average";
        cout << "\n \t\t\t 7. Export Reports";
        cout << "\n \t\t\t 8. View Failed Students";
        cout << "\n \t\t\t 9. Exit Program";
        cout << "\n\n";
        cout << "\t\t\t Enter Your Choice -- ";
        fflush(stdin);

        choice = getchar();
        switch (choice) {

            case '1':  
                addReport(fp, s, size);
                break;

            case '2':  
                listReport(fp, s, size, pass_per);
                break;

            case '3':  
                modifyReport(fp, s, size);
                break;

            case '4':  
                deleteReport(fp, fp, s, size);
                break;

            case '5': 
                setPassPercentage(&pass_per);
                break;

            case '6':  
                getAverage(fp, s, size);
                break;

            case '7':  
                exportReport(fp, s, size, pass_per);
                break;

            case '8':
                viewFailedStudents(fp, s, size, pass_per);
                break;

            case '9':
                fclose(fp);
                exit(0);

            default: 
                cout << "\n-----------------------\n";
                cout << "Invaild Input. Try again.";
                cout << "\n-----------------------\n\n";
        } // switch ends
        fflush(stdin);
    }

    system("pause");
    return 0;
}

void addReport(FILE *fp, student s, long int size) {

    fseek(fp, 0, SEEK_END);
    char another = 'Y';

    while (another == 'Y' || another == 'y') {
        system("cls");
        fflush(stdin);
        cout << "Enter the Name : ";
        cin.getline(s.name, 50);
        cout << "Enter the Unique Roll No.   :";
        cin.getline(s.Uniroll_no, 15);
        cout << "Enter the Section    : ";
        s.section = getchar();
        cout << "Enter the attendance of student (out of 100): ";
        cin >> s.attendance;

        cout << "\n\nEnter the Marks obtained in  :-\n";
        cout << "Mathematics: ";
        cin >> s.maths;
        cout << "\nEnglish  : ";
        cin >> s.english;
        cout << "\nScience  :";
        cin >> s.science;
        cout << "\nComputer Science :";
        cin >> s.computer_science;
        s.percent = (s.maths + s.english + s.science + s.computer_science) / 4.0;
        fwrite(&s, size, 1, fp);
        cout << "\n\nAdd Another Record (Y/N) ";
        fflush(stdin);
        another = getchar();
    }
}

void listReport(FILE *fp, student s, long int size, double pass_per) {

    system("cls");
    rewind(fp);
    cout << "--- View the Reports in the Database ---";
    cout << "\n";

    while (fread(&s, size, 1, fp) == 1) {
        cout << "\n";
        cout << "\n" << s.name;
        cout << "\nSection:" << s.section << "\tUnique Roll No." << s.Uniroll_no << endl;
        cout << "\nAttendance: " << s.attendance << endl;

        cout << "\nMathematics: " << s.maths;
        cout << "\nEnglish  : " << s.english;
        cout << "\nScience  :" << s.science;
        cout << "\nComputer Science :" << s.computer_science;
        if (s.percent < pass_per)
            cout << "\n\nOVERALL PERCENTAGE: " << s.percent << "%" << "\tFAIL";
        else
            cout << "\n\nOVERALL PERCENTAGE: " << s.percent << "%" << "\tPASS";
        cout << "\n--------------------------------------------\n";
    }
    cout << "\n\n";
    system("pause");
}
void modifyReport(FILE *fp, student s, long int size) {

    system("cls");
    char new_uniId[15], another = 'Y';

    while (another == 'Y' || another == 'y') {
        cout << "\n Enter the Unique Roll No. of the student : ";
        cin >> new_uniId;

        rewind(fp);
        while (fread(&s, size, 1, fp) == 1) {
            if (strcmp(s.Uniroll_no, new_uniId) == 0) {
                fflush(stdin);
                cout << "Enter the new Name : ";
                cin.getline(s.name, 50);
                cout << "Enter the new Section   : ";
                s.section = getchar();
                fseek(fp, -size, SEEK_CUR);
                fwrite(&s, size, 1, fp);
                break;
            }
        }
        cout << "\n Modify Another Record (Y/N) ";
        fflush(stdin);
        another = getchar();
    }
}

void deleteReport(FILE *fp, FILE *ft, student s, long int size) {

    system("cls");
    char new_uniId[15], another = 'Y';

    while (another == 'Y' || another == 'y') {
        cout << "\n Enter the Unique Roll no. of the student to delete : ";
        cin >> new_uniId;

        ft = fopen("C:\\Users\\AB\\Desktop\\Mini Project\\temp.dat", "wb");

        rewind(fp);
        while (fread(&s, size, 1, fp) == 1)

            if (strcmp(s.Uniroll_no, new_uniId) != 0) {
                fwrite(&s, size, 1, ft);
            }
        fclose(fp);
        fclose(ft);
        remove("C:\\Users\\AB\\Desktop\\Mini Project\\Record.txt");
        rename("C:\\Users\\AB\\Desktop\\Mini Project\\temp.dat", "C:\\Users\\AB\\Desktop\\Mini Project\\Record.txt");

        fp = fopen("C:\\Users\\AB\\Desktop\\Mini Project\\Record.txt", "rb+");
        cout << "\nReport Deleted.\n";
        cout << "\n Delete Another Record (Y/N) ";
        fflush(stdin);
        another = getchar();
    }
}

void setPassPercentage(double *pass_per) {

    system("cls");
    int temp;

    cout << "\nEnter the new pass percentage: ";
    cin >> temp;
    *pass_per = temp;
}

void getAverage(FILE *fp, student s, long int size) {

    system("cls");
    rewind(fp);
    int n = 0, avg_Math = 0, avg_eng = 0, avg_sci = 0, avg_cs = 0, avg_atd = 0, avg_per = 0;

    while (fread(&s, size, 1, fp) == 1) {
        n++;
        avg_atd += s.attendance;
        avg_Math += s.maths;
        avg_eng += s.english;
        avg_sci += s.science;
        avg_cs += s.computer_science;
        avg_per += s.percent;
    }
    cout << "\nAverage Attendance of Students: " << avg_atd / n;
    cout << "\n\nAverage Marks:- \n";
    cout << "\n"<< "Mathematics: " << avg_Math / n;
    cout << "\nEnglish: " << avg_eng / (n);
    cout << "\nScience: " << avg_sci / (n);
    cout << "\nComputer Science: " << avg_cs / (n);

    cout << "\n\n" << "Average Percentage of Students: " << avg_per / n << endl;
    system("pause");
}
void exportReport(FILE *fp, student s, long int size, double pass_per) {
    // file declaration for excel file
    ofstream myfile;
    myfile.open("student_reports.csv");

    rewind(fp);
    string result;
    myfile << "Name"<< ","<< "Section"<< "," << "Roll No."<< ","<< "Maths"<< ","<< "English";
    myfile << ","<< "Science"<< ","<< "CS" << ","<< "Attendance"<< ","<< "Percentage"<< "," << "Result" << endl;
    myfile << endl;

    while (fread(&s, size, 1, fp) == 1) {
        if (s.percent >= pass_per)
            result = "PASS";
        else
            result = "FAIL";

        myfile << s.name << "," << s.section << "," << s.Uniroll_no << "," << s.maths << "," << s.english;
        myfile << "," << s.science << "," << s.computer_science << "," << s.attendance << "," << s.percent << "," << result << endl;
    }

    system("cls");
    cout << "Reports exported!\n" << endl;
    system("pause");
}

void viewFailedStudents(FILE *fp, student s, long int size, double pass_per) {
    
    system("cls");
    string result;
    rewind(fp);
    
    while (fread(&s, size, 1, fp) == 1) {
        if (s.percent < pass_per) {
            result = "FAIL";
            cout << "Name: " << s.name;
            cout << "\nSection: " << s.section;
            cout << "\nUnique Roll No.: " << s.Uniroll_no;
            cout << "\n--------------------\n";
        }
    }
    system("pause");
}