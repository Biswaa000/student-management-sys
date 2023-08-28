#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <cstring>
int gl = 2;

using namespace std;

class student
{
    int roll;
    char name[40];
    char gender;
    char faculty[10];
    long int contactno;

public:
    void getdata()
    {
    top:
        cout << "\nEnter Roll of Student     :";
        cin >> roll;
        if (searchfile(roll) == 1)
        {
            cout << "\n----ROLL NUMBER ARLEADY Exist.... Enter another correct Roll number..." << endl;
            goto top;
        }

        cout << "\nEnter Name of Student     :";
        cin.ignore();
        cin.getline(name, 40);
        cout << "\nEnter Gender   (M/F)       :";
        cin >> gender;
        cout << "\nEnter Faculty              :";
        cin.ignore();
        cin.getline(faculty, 40);
        cout << "\nEnter Contact No.          : ";
        cin >> contactno;
        cout << endl;
    }

    void showdata()
    {

        cout << endl;
        cout << "---Roll no       :" << roll << endl;
        cout << "---Name          :" << name << endl;
        cout << "---Gender        :" << gender << endl;
        cout << "---faculty       :" << faculty << endl;
        cout << "---Contact no.   :" << contactno << endl;
        cout << endl;
    }

    int search(int r)
    {
        if (roll == r)
            return 1;

        else

            return 0;
    }

    void showRecord();
    void inputRecord();
    void modifydata();
    void deleteRecord();
    void displayRecord();
    void Destroy();
    int searchfile(int);
    int getroll() { return roll; }
};

// ---------------------------------------------------------------------------------------

int student::searchfile(int r)
{
    student pers;
    ifstream file("student.dat", ios::binary);
    while (file.read((char *)&pers, sizeof(pers)))
    {
        if (pers.roll == r)
        {
            file.close();
            return 1; // Roll number found
        }
    }
    file.close();
    return 0; // Roll number not found
}

// ----------------------------------------------------------------------------------------------------

void student::inputRecord()
{
    int no = 0;
    cout << "\n-----Enter the number of student  :";
    cin >> no;
    student pers[no];

    fstream file;
    file.open("student.dat", ios::in | ios::out | ios::binary | ios::app);
    for (int i = 0; i < no; ++i)
    {
        cout << "\t\nEnter student's data:-----" << i + 1 << endl;
        pers[i].getdata();
        file.write((char *)&pers[i], sizeof(pers[i]));
    }

    file.close();
    cout << "\n\nData Successfully Saved to File....\n";
}
// ----------------------------------------------------------------------------------------------------
void student::showRecord()
{
    student pers;
    int Roll, flag = 0;
    fstream file;
    file.open("student.dat", ios::binary | ios::out | ios::in);
    cout << "Enter Roll number:" << endl;
    cin >> Roll;

    do
    {

        if (pers.search(Roll))
        {
            pers.showdata();

            flag = 1;
            break;
        }

    } while (file.read((char *)&pers, sizeof(pers)));

    if (flag == 0)

        cout << "Not found" << endl;

    file.close();
}
// ----------------------------------------------------------------------------------------------------

void student::modifydata()
{
    student pers;

    int n, flag = 0, pos;
    fstream fio;

    fio.open("student.dat", ios::in | ios::out | ios::binary);

    cout << "\n----Enter Roll Number you want to Modify : ";
    cin >> n;

    while (fio.read((char *)&pers, sizeof(pers)))
    {
        pos = fio.tellg();
        if (n == pers.getroll())
        {
            cout << "\tThe Following Roll No. " << n << " will be modified with new data:\n";
            // pers.showRecord();
            cout << "\n\nNow Enter the New Details....\n";
            pers.getdata();
            fio.seekg(pos - sizeof(pers));
            fio.write((char *)&pers, sizeof(pers));
            flag++;
        }
    }
    fio.close();

    if (flag == 0)
        cout << "\tThe Roll No. " << n << " not found....\n\n";
}

// ---------------------------------------------------------------------------------------------

void student::deleteRecord()
{
    int n, flag = 0;
    ifstream fin;
    student pers;
    ofstream fout, tout;

    fin.open("student.dat", ios::in | ios::binary);
    fout.open("TempStud.dat", ios::out | ios::app | ios::binary);
    tout.open("TrashStud.dat", ios::out | ios::app | ios::binary);

    cout << "--Enter Roll Number you want to move to Trash : ";
    cin >> n;

    while (fin.read((char *)&pers, sizeof(pers)))
    {
        if (n == pers.getroll())
        {
            cout << "\tThe Following Roll No. " << n << " has been moved to Trash:\n";
            tout.write((char *)&pers, sizeof(pers));

            flag++;
        }
        else
        {
            fout.write((char *)&pers, sizeof(pers));
        }
    }
    fout.close();
    tout.close();
    fin.close();

    if (flag == 0)
        cout << "The Roll No. " << n << " not found....\n\n";
    remove("student.dat");
    remove("TrashStud.dat");
    rename("TempStud.dat", "student.dat");
}
// ------------------------------------------------------------------------------------------------
void student::displayRecord() // display all records
{
    student pers;
    ifstream fin;
    fin.open("student.dat", ios::in | ios::binary);
    while (fin.read((char *)&pers, sizeof(pers)))
    {
        pers.showdata();
    }
    fin.close();
    cout << "\n\nData Reading from File Successfully Done....\n";
}

// ---------------------------------------------------------------------------------------------

void student::Destroy() // destroy all data
{
    remove("student.dat");
}

// -------------------------------------------------------------------------------------------------

int main()
{
    student pers;
    while (1)

    {
        system("cls");
        system("color f4");
        cout << "\n***************************   STUDENT DATABASE MANAGEMENT SYSTEM   **********************" << endl;

        cout << "\n     1. Input The Record of student " << endl;
        cout << "     2. Search By Roll Number " << endl;
        cout << "     3. Display All Record" << endl;
        cout << "     4. Modify Details" << endl;
        cout << "     5. Delete By Roll Number" << endl;
        cout << "     6. Delete all database  " << endl;
        cout << "     7. Exit " << endl;
        cout << "\n---- Enter the option---:>";

        int choice;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            pers.inputRecord();
            break;
        case 2:
            pers.showRecord();
            break;

        case 3:
            pers.displayRecord();
            break;

        case 4:
            pers.modifydata();
            break;

        case 5:
            pers.deleteRecord();
            break;

        case 6:
        {
            char y[1];
            cout << "Do you want to deletes all database of stutent (y/n)" << endl;
            cin >> y;
            // if(int(y)==121)
            if (y[0] == 'y')
            {
                pers.Destroy();
                cout << "   all deleted..............................." << endl;
            }
            break;
        }

        case 7:
            exit(0);
            break;

        default:
            cout << "\tEnter number between 1-6 only" << endl;
        }
        system("pause");
    }

    return 0;
}