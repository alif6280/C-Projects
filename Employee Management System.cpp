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
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter position: ";
        getline(cin, position);
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter team: ";
        getline(cin, team);
        cout << "Enter working location: ";
        getline(cin, location);
        cout << "Enter type of employee (e.g.,Full-time, Part-time, Intern): ";
        getline(cin, type);
        cout << "Enter date of joining (DD/MM/YYYY): ";
        getline(cin, joiningDate);
        cout << "Enter salary: ";
        cin >> salary;
        cin.ignore();
    }

    void display(int index)
    {
        cout << "\nEmployee " << index + 1 << " Details:\n";
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Position: " << position << endl;
        cout << "Email: " << email << endl;
        cout << "Team: " << team << endl;
        cout << "Location: " << location << endl;
        cout << "Type: " << type << endl;
        cout << "Joining Date: " << joiningDate << endl;
        cout << "Salary: " << salary << endl;
        cout << "--------------------------\n";
    }

    void writeToFile(ofstream& file)
    {
        file << name << endl<< id << endl<< position << endl<< email << endl<< team << endl<< location << endl<< type << endl
             << joiningDate << endl<< salary << endl;
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
    ofstream file("employees.txt",ios::out|ios::app);
    for (int i = 0; i < total; i++)
    {
        employees[i].writeToFile(file);
    }
    file.close();
}

void loadFromFile()
{
    ifstream file("employees.txt",ios::out|ios::app);
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
    cout << "How many employees do you want to enter? ";
    cin >> user;
    cin.ignore();

    for (int i = total; i < total + user; i++)
    {
        cout << "\nEnter data for employee " << i + 1 << ":\n";
        employees[i].input();
    }
    total += user;
    saveToFile();
}

void show()
{
    loadFromFile();
    if (total != 0)
    {
        for (int i = 0; i < total; i++)
        {
            employees[i].display(i);
        }
    }
    else
    {
        cout << "No employee data available.\n";
    }
    system("pause");
}

void search()
{
    loadFromFile();
    if (total != 0)
    {
        string id;
        cout << "Enter ID to search: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < total; i++)
            {
            if (employees[i].id == id)
            {
                employees[i].display(i);
                system("pause");
                return;
            }
        }
        cout << "Employee not found.\n";
    }
    else
    {
        cout << "No employee data available.\n";
    }
    system("pause");
}

void update()
{
    loadFromFile();
    if (total != 0)
    {
        string id;
        cout << "Enter ID to update: ";
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
                cout << "Employee updated.\n";
                system("pause");
                return;
            }
        }
        cout << "Employee not found.\n";
    } else {
        cout << "No data available.\n";
    }
    system("pause");
}

void updateSalary()
{
    loadFromFile();
    if (total != 0)
    {
        string id;
        cout << "Enter ID to update salary: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < total; i++)
        {
            if (employees[i].id == id)
            {
                cout << "Current Salary: " << employees[i].salary << endl;
                cout << "Enter new salary: ";
                cin >> employees[i].salary;
                cin.ignore();
                saveToFile();
                cout << "Salary updated.\n";
                system("pause");
                return;
            }
        }
        cout << "Employee not found.\n";
    }
    else
    {
        cout << "No data available.\n";
    }
    system("pause");
}

void del()
{
    loadFromFile();
    if (total != 0)
    {
        int choice;
        cout << "Press 1 : Delete specific record\n";
        cout << "Press 2 : Delete all records\n";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string id;
            cout << "Enter ID to delete: ";
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
                    saveToFile();
                    cout << "Record deleted.\n";
                    system("pause");
                    return;
                }
            }
            cout << "Employee not found.\n";
        } else if (choice == 2)
        {
            total = 0;
            saveToFile();
            cout << "All records deleted.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } else {
        cout << "No data available.\n";
    }
    system("pause");
}

void signup()
{
    string username, password;
    cout << "\n--- SIGN UP ---\n";
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Creating account";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        Sleep(300);
    }
    cout << "\nAccount created successfully!\n";
    Sleep(1000);
}

bool signin()
{
    string username, password, fileUsername, filePassword;
    cout << "\n--- LOG IN ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> fileUsername >> filePassword)
    {
        if (username == fileUsername && password == filePassword)
        {
            cout << "Login successful!\n";
            Sleep(1000);
            return true;
        }
    }

    cout << "Invalid credentials.\n";
    Sleep(1000);
    return false;
}

void mainMenu()
{
    char ch;
    while (true)
    {
        system("CLS");
        cout << "====== Employee Management System ======\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Update Salary\n";
        cout << "7. Logout\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
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
            default:
            cout << "Invalid input.\n";
            Sleep(1000);
        }
    }
}

int main()
{
    while (true)
    {
        system("CLS");
        cout << "===== Welcome to Employee Management System =====\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        char choice;
        cin >> choice;

        switch (choice)
        {
            case '1': signup(); break;
            case '2':
                if (signin())
                {
                    loadFromFile();
                    mainMenu();
                }
                break;
            case '3':
                cout << "Exiting program...\n";
                Sleep(1000);
                return 0;
            default:
                cout << "Invalid choice.\n";
                Sleep(1000);
        }
    }
    return 0;
}





