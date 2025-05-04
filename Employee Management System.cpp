#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class Employee
{
public:
    string name, id, position, email;
    string team, location, type;
    string joiningDate;
    int salary;

    void input()
    {
        cout << "Enter employee name: ";
        getline(cin, name);
        cout << "Enter id: ";
        getline(cin, id);
        cout << "Enter position: ";
        getline(cin, position);
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter team: ";
        getline(cin, team);
        cout << "Enter working location: ";
        getline(cin, location);
        cout << "Enter type of employee (e.g., Full-time, Part-time): ";
        getline(cin, type);
        cout << "Enter date of joining (DD/MM/YYYY): ";
        getline(cin, joiningDate);
        cout << "Enter salary: ";
        cin >> salary;
        cin.ignore();
    }

    void display(int index)
    {
        cout << "Data of employee " << index + 1 << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Position: " << position << endl;
        cout << "Email: " << email << endl;
        cout << "Team: " << team << endl;
        cout << "Working Location: " << location << endl;
        cout << "Employee Type: " << type << endl;
        cout << "Date of Joining: " << joiningDate << endl;
        cout << "Salary: " << salary << endl;
        cout << "---------------------------" << endl;
    }

    void writeToFile(ofstream& file)
    {
        file << name << endl
             << id << endl
             << position << endl
             << email << endl
             << team << endl
             << location << endl
             << type << endl
             << joiningDate << endl
             << salary << endl;
    }

    bool readFromFile(ifstream& file)
    {
        if (getline(file, name) &&
            getline(file, id) &&
            getline(file, position) &&
            getline(file, email) &&
            getline(file, team) &&
            getline(file, location) &&
            getline(file, type) &&
            getline(file, joiningDate) &&
            file >> salary)
        {
            file.ignore();
            return true;
        }
        return false;
    }
};

Employee employees[100];
int total = 0;

void saveToFile()
{
    ofstream file("employees.txt");
    for (int i = 0; i < total; i++)
    {
        employees[i].writeToFile(file);
    }
    file.close();
}

void loadFromFile()
{
    ifstream file("employees.txt");
    total = 0;
    while (employees[total].readFromFile(file))
    {
        total++;
    }
    file.close();
}

void empdata()
{
    int user;
    cout << "How many employees data do you want to enter??" << endl;
    cin >> user;
    cin.ignore();

    for (int i = total; i < total + user; i++)
    {
        cout << "\nEnter data of employee " << i + 1 << endl << endl;
        employees[i].input();
    }

    total += user;
    saveToFile();
}

void show() {
    if (total != 0)
    {
        for (int i = 0; i < total; i++)
        {
            employees[i].display(i);
        }
    } else
    {
        cout << "No data is entered" << endl;
    }
}

void search()
{
    if (total != 0)
        {
        string id;
        cout << "Enter id of employee which you want to search" << endl;
        cin >> id;
        cin.ignore();

        for (int i = 0; i < total; i++)
        {
            if (employees[i].id == id)
            {
                employees[i].display(i);
                return;
            }
        }
        cout << "No such record found" << endl;
    } else {
        cout << "No data is entered" << endl;
    }
}

void update()
{
    if (total != 0)
        {
        string id;
        cout << "Enter id of employee which you want to update" << endl;
        cin >> id;
        cin.ignore();

        for (int i = 0; i < total; i++)
            {
            if (employees[i].id == id)
            {
                cout << "\nOld data:\n";
                employees[i].display(i);

                cout << "\nEnter new data:\n";
                employees[i].input();
                saveToFile();
                return;
            }
        }
        cout << "No such record found" << endl;
    } else {
        cout << "No data is entered" << endl;
    }
}

void updateSalary()
{
    if (total != 0)
        {
        string id;
        cout << "Enter the ID of the employee whose salary you want to update: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < total; i++)
        {
            if (employees[i].id == id)
            {
                cout << "\nCurrent Salary of " << employees[i].name << ": " << employees[i].salary << endl;
                cout << "Enter new salary: ";
                cin >> employees[i].salary;
                cin.ignore();
                saveToFile();
                cout << "Salary updated successfully.\n";
                return;
            }
        }
        cout << "No such record found.\n";
    } else {
        cout << "No data is entered.\n";
    }
}

void del() {
    if (total != 0)
        {
        int press;
        cout << "Press 1 : Delete specific record" << endl;
        cout << "Press 2 : Delete full record" << endl;
        cin >> press;
        cin.ignore();

        if (press == 1)
            {
            string id;
            cout << "Enter id of employee which you want to delete" << endl;
            cin >> id;
            cin.ignore();

            for (int i = 0; i < total; i++)
                {
                if (employees[i].id == id)
                {
                    for (int j = i; j < total - 1; j++)
                    {
                        employees[j] = employees[j + 1];
                    }
                    total--;
                    cout << "Record deleted successfully.\n";
                    saveToFile();
                    return;
                }
            }
            cout << "No such record found" << endl;
        } else if (press == 2)
        {
            total = 0;
            cout << "All records are deleted" << endl;
            saveToFile();
        } else
        {
            cout << "Invalid Input" << endl;
        }
    }
    else
    {
        cout << "No data is entered" << endl;
    }
}

void signup()
{
    string username, password;
    cout << "\n\t--- SIGN UP ---" << endl;
    cout << "\tEnter new username: ";
    cin >> username;
    cout << "\tEnter new password: ";
    cin >> password;

    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "\tCreating account, please wait";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        Sleep(500);
    }
    cout << "\n\tAccount created successfully!" << endl;
    Sleep(1500);
}

bool signin()
{
    string username, password;
    string fileUsername, filePassword;
    cout << "\n\t--- SIGN IN ---" << endl;
    cout << "\tEnter username: ";
    cin >> username;
    cout << "\tEnter password: ";
    cin >> password;

    ifstream inFile("users.txt");
    while (inFile >> fileUsername >> filePassword)
    {
        if (username == fileUsername && password == filePassword)
        {
            cout << "\tLogin successful!" << endl;
            Sleep(1000);
            return true;
        }
    }

    cout << "\tInvalid login. Please try again." << endl;
    Sleep(1500);
    return false;
}

void mainMenu()
{
    char ch;
    while (true)
        {
        system("CLS");
        cout << "-------Employee Management System--------" << endl;
        cout << "\nPress 1 : Add Employee" << endl;
        cout << "Press 2 : Display all Employees" << endl;
        cout << "Press 3 : Search Employee" << endl;
        cout << "Press 4 : Update Employee" << endl;
        cout << "Press 5 : Delete Employee" << endl;
        cout << "Press 6 : Update Salary" << endl;
        cout << "Press 7 : Logout" << endl;
        cout << "Press 8 : Exit" << endl;

        cin >> ch;
        cin.ignore();
        system("CLS");

        switch (ch)
        {
            case '1': empdata(); break;
            case '2': show(); break;
            case '3': search(); break;
            case '4': update(); break;
            case '5': del(); break;
            case '6': updateSalary(); break;
            case '7': return;
            case '8': exit(0);
            default: cout << "\aInvalid Input" << endl;
        }
    }
}

int main()
{
    loadFromFile();
    while (true)
        {
        system("CLS");
        cout << "_______ Employee Management System _______" << endl;
        cout << "\tPress 1 : Sign Up" << endl;
        cout << "\tPress 2 : Sign In" << endl;
        cout << "\tPress 3 : Exit" << endl;
        cout << "\tEnter your choice: ";
        char choice;
        cin >> choice;

        switch (choice)
        {
            case '1':
                signup();
                break;
            case '2':
                if (signin())
                {
                    mainMenu();
                }
                break;
            case '3':
                cout << "\nExiting program...";
                Sleep(1000);
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
                Sleep(1000);
        }
    }

    return 0;
}

