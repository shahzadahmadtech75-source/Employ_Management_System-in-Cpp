#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <conio.h> 
//colors library
#include <windows.h>
#ifndef COMMON_LVB_UNDERSCORE
#define COMMON_LVB_UNDERSCORE 0x8000
#endif
#include "termcolor.hpp"
using namespace std;
// This is great for making colors work on Windows 10/11
bool enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;
    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    return SetConsoleMode(hOut, dwMode);
}

//check empty lines 
		bool is_blank(const string& s) {
    
    return all_of(s.begin(), s.end(), [](unsigned char ch) {
        return isspace(ch);
    });
}
//////////////////Prototypes
// Password Input  Function 
void inputPassword(string &password);
// register user function
void registerUser();
// load users from file to vector
void load();
// login User
int login();
// system flow function
void employeSystem();
//username validation function
bool isValidUsername(string username);
// User Class
class User{
	public:
	string name;
	string password;
};

// users array
vector <User> users;

// save user to file function
void save();

// Class Employe Starts here--------------------------------------
class Employee{
private:
    string empName;
    int empId;
    double empSalary;

public:
    Employee() : empName("Unknown"), empId(0), empSalary(0) {}
	// set name by parameter
	void setNameByPar(string n){
		empName = n;
	}
	// set name by user input
    void setName(){
        cout << termcolor::yellow << "\nEnter Employee Name: " << termcolor::reset;
        getline(cin >> ws, empName);
    }
    //get name
    string getName(){
    	return empName;
	}
	// set ID
    void setID(int id){
        empId = id;
    }
    
//    set Salary by using parameter
void setSalaryByPar(double n){
	empSalary = n;
}
// set Salary by user Input
    void setSalary(){
        cout << termcolor::yellow << "\nEnter Employee Salary: " << termcolor::reset;
        cin >> empSalary;
    }
	//GET SALARY
	double getSalary(){
		return empSalary;
	}
    int getId() const{
        return empId;
    }

    void displayEmployData() const{
        cout << termcolor::cyan << "\nName: " << termcolor::white << empName;
        cout << termcolor::cyan << "\nID: "   << termcolor::white << empId;
        cout << termcolor::cyan << "\nSalary: " << termcolor::green << empSalary;
        cout << termcolor::bright_grey << "\n-----------------------------------\n" << termcolor::reset;
    }

    // Only update NAME and SALARY (not ID)
    void updateData(){
        int choice;
        cout << termcolor::yellow << "\n1. Update Name\n2. Update Salary\n" << termcolor::reset;
        cout << termcolor::yellow << "Enter choice: " << termcolor::reset;
        cin >> choice;

        switch(choice){
            case 1:
                setName();
                break;
            case 2:
                setSalary();
                break;
            default:
                cout << termcolor::red << "\nInvalid choice!" << termcolor::reset;
        }
    }
};

//?Employ Manager class ------------------------------------------
class EmployManager{
    vector<Employee> employs;

public:
	
	// read from file and store into vector
	void loadData(){
		ifstream myfile("employList.txt");
		if(!myfile.is_open()){
			cout << termcolor::red << "\nUnable to Open the File!" << termcolor::reset;
			return;
		}
		employs.clear();
		string line;
		string name;
		string id;
		string sal;
		while(getline(myfile,line)){
			if(is_blank(line)){
				continue;
			}
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, id, '|');
			getline(ss, sal, '|');

			int Id = stoi(id);
			double Sal = stod(sal);
			Employee emp;
			emp.setNameByPar(name);
			emp.setID(Id);
			emp.setSalaryByPar(Sal);
			employs.push_back(emp);////////////////////////**********************************
		}
		myfile.close();
	}
	// Data saving to file
	void saveData(){
		ofstream myfile("employList.txt");
		if(!myfile.is_open()){
			cout << termcolor::red << "\nUnable to Open the File!" << termcolor::reset;
			return;
		}
		for(Employee &employ : employs) {
			string name = employ.getName();
			int id = employ.getId();
			double sal = employ.getSalary();
			myfile << name << " | "<< id << " | "<< sal << endl;
		}
		myfile.close();
		cout << termcolor::green << termcolor::bold << "\nData Saved Successfully." << termcolor::reset;
	}
	
    bool idChecker(int x){
        for(Employee &employ : employs){
            if(x == employ.getId()){
                cout << termcolor::red << "\nID already exists!" << termcolor::reset;
                return true;
            }
        }
        return false;
    }

    void addEmployee(){
        Employee em;
        em.setName();

        int id;
        do{
            cout << termcolor::yellow << "\nEnter Employee ID: " << termcolor::reset;
            cin >> id;
        } while(idChecker(id));

        em.setID(id);
        em.setSalary();

        employs.push_back(em);

        cout << termcolor::green << termcolor::bold << "\nEmployee Added Successfully!\n" << termcolor::reset;
    }

    void showEmployData() const{
        if(employs.empty()){
            cout << termcolor::red << "\nNo Employees Found!\n" << termcolor::reset;
            return;
        }

        for(const Employee &employ : employs){
            employ.displayEmployData();
        }
    }

    void searchEmploy(){
        int id;
        cout << termcolor::yellow << "\nEnter ID to search: " << termcolor::reset;
        cin >> id;

        for(const Employee &employ : employs){
            if(id == employ.getId()){
                cout << termcolor::green << termcolor::bold << "\nEmployee Found:\n" << termcolor::reset;
                employ.displayEmployData();
                return;
            }
        }

        cout << termcolor::red << "\nEmployee not found!\n" << termcolor::reset;
    }

    void updateEmploy(){
        int id;
        cout << termcolor::yellow << "\nEnter Employee ID to update: " << termcolor::reset;
        cin >> id;

        for(Employee &employ : employs){
            if(id == employ.getId()){

                int choice;
                cout << termcolor::yellow << "\n1. Update Name/Salary\n2. Update ID\nEnter choice: " << termcolor::reset;
                cin >> choice;

                if(choice == 1){
                    employ.updateData();
                }
                else if(choice == 2){
                    int newId;
                    do{
                        cout << termcolor::yellow << "\nEnter New ID: " << termcolor::reset;
                        cin >> newId;
                    } while(idChecker(newId));

                    employ.setID(newId);
                }

                cout << termcolor::green << termcolor::bold << "\nEmployee Updated Successfully!\n" << termcolor::reset;
                return;
            }
        }

        cout << termcolor::red << "\nEmployee not found!\n" << termcolor::reset;
    }

    void deleteEmploy(){
        int id;
        cout << termcolor::yellow << "\nEnter ID to delete: " << termcolor::reset;
        cin >> id;

        for(auto i = employs.begin(); i != employs.end(); i++){
            if(id == i->getId()){
                employs.erase(i);
                cout << termcolor::green << termcolor::bold << "\nEmployee Deleted Successfully!\n" << termcolor::reset;
                return;
            }
        }

        cout << termcolor::red << "\nEmployee not found!\n" << termcolor::reset;
    }
};

// Main and _FUNCTIONs

int menu(){
    int choice;
    cout << termcolor::bold <<  "\n\n===== Employee Management System =====\n\n" << termcolor::reset;
    cout << termcolor::cyan << "1. Add Employee\n";
    cout << "2. Show Employees\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. Update\n";
    cout << termcolor::red << "6. Exit\n" << termcolor::reset;
    cout << termcolor::yellow << "Enter choice: " << termcolor::reset;
    cin >> choice;
    return choice;
}

int main(){
    enableANSI();
    load();

    while (true){
        cout << termcolor::bold << termcolor::green;
        cout << "                          *_______________________________________* " << endl;
        cout << "------------------------- | Welcome to Employee Management System | ---------------------------------------" << endl;
        cout << "                          *---------------------------------------*"  << endl;
        cout << termcolor::reset;

        int choice;
        cout << termcolor::cyan << termcolor::bold;
        cout << "1. Register" << endl;
        cout << "2. Login"    << endl;
        cout << termcolor::red << "3. Exit"     << endl;
        cout << termcolor::reset;
        cout << termcolor::yellow << "Select: " << termcolor::reset;

        // Safe input — prevents crash on bad input
        if (!(cin >> choice)) { 
            cin.clear();
            cin.ignore(1000, '\n');
            cout << termcolor::red << "\nInvalid input! Enter a number.\n" << termcolor::reset;
            continue;
        }


        switch (choice){
            case 1:
                registerUser();
                employeSystem(); 

                break;

            case 2: {
                // FIXED: login failure now gives a real choice  FIXED
                int flag = login();
                if (flag == 1){
                    employeSystem();
                } else {
                    cout << termcolor::yellow << termcolor::bold;
                    cout << "\n1. Try Login Again\n2. Register New Account\n3. Back to Main Menu\n";
                    cout << termcolor::reset;
                    cout << termcolor::yellow << "Select: " << termcolor::reset;
                    int sub;
                    cin >> sub;
                    if (sub == 1){
                        flag = login();
                        if(flag == 1) employeSystem();
                    } else if (sub == 2){
                        registerUser();
                        employeSystem();
                    }
                    // case 3 or anything else ? loops back to main menu
                }

                break;
            }

            case 3:
                cout << termcolor::bold << termcolor::magenta;
                cout << "                          *________________________* "  << endl;
                cout << "------------------------- | Thanks for visiting..  | ---------------------------------------------------" << endl;
                cout << "                          *-----------------------*"   << endl;
                cout << termcolor::reset;
                return 0;

            default:
                cout << termcolor::red << "\nInvalid Choice.. !\n" << termcolor::reset;
                continue;
        }
    }
}
//Password Function
void inputPassword(string &password) {
    char ch;
    password.clear();  // clear previous data

    cout << termcolor::yellow << "\nEnter Password (masking enabled): " << termcolor::reset;

    while (true) {
        ch = _getch();

        if (ch == 13) { // Enter
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << termcolor::bright_grey << "*" << termcolor::reset;
        }
    }

    cout << endl;
}

// save user to file
void save(){
	ofstream loginFile("login.txt");
	if(!loginFile.is_open()){
		return;
	}
	for( const auto &user: users){
		loginFile << user.name  << "|" << user.password << endl;
	}
	loginFile.close();
}

//Register user
void registerUser() {
    User u;  // ? create object first

    cout << termcolor::bold << termcolor::magenta << "\n************************************* Register a new User.. ************************************************\n" << termcolor::reset;
	string name;
	
    while(true){	
    bool exists = false;
//    check validation
    do {
        cout << termcolor::yellow<<"Enter Username (min 5 chars, not pure numbers): " << termcolor::reset;
        getline(cin >> ws , name);
    } while (!isValidUsername(name));
    for(const User &user : users){
    	if(name == user.name){
    		cout << termcolor::red << "\nUser already exists!...." << termcolor::reset <<endl;
			exists = true;
			break;
		}
		
	}
	if(exists){
		continue;
	}else{
			u.name = name;
			break;}
}

    inputPassword(u.password);    // input password

    users.push_back(u);           // ? store in vector
    cout << termcolor::bold << termcolor::green;
    cout << "                          *_______________________________* "<<endl;
    cout << "------------------------- | User Registered Successfully! | ------------------------------------" << endl;
    cout << "                          *-------------------------------*"<<endl;
    cout << termcolor::reset;
    
 	save();
}

// load users from file to vector
void load() {
    ifstream file("login.txt");
    if (!file.is_open()) {
        return;
    }

    users.clear();

    string line;
    string username;
    string pass;

    while (getline(file, line)) {
    		if(is_blank(line)){
				continue;
			}
			stringstream ss(line);
			getline(ss, username, '|');
			getline(ss, pass, '|');
        User u;
        u.name = username;
        u.password = pass;
		if((!u.name.empty()) && (!u.password.empty())){
			users.push_back(u);
		}else{
			continue;
		}
        
    }

    file.close();
}

// login user
int login(){
	string name,pass;
	cout << termcolor::bold;
	cout << "                          *_________________________* "<<endl;
    cout << "------------------------- | Enter Login Information | -------------------------------------------" << endl;
    cout << "                          *-------------------------*"<<endl;
    cout << termcolor::reset;
	cout << termcolor::yellow << "Enter username: " << termcolor::reset;
	getline(cin >> ws,name);
	inputPassword(pass);
	int check = 0;
	for(const User &user : users){
		if(name == user.name && pass == user.password){
		check = 1;		
		break;
		}
	}
	if(check == 1){
		cout << termcolor::bold << termcolor::green;
		cout << "                          *______________________________* "<<endl;
        cout << "------------------------- | User Logged in Successfully! | -------------------------------------------" << endl;
        cout << "                          *------------------------------*"<<endl;
        cout << termcolor::reset;
        return 1;
	}else{
		cout << termcolor::bold << termcolor::red;
		cout << "                          *_________________* "<<endl;
        cout << "------------------------- | User Not Found! | -------------------------------------------" << endl;
        cout << "                          *-----------------*"<<endl;
        cout << termcolor::reset;
        return -1;
		}
			
}
 //Employee management flow function
 void employeSystem(){
    EmployManager em;
	em.loadData();
    while(true){
        int n = menu();

        switch(n){
            case 1: em.addEmployee(); break;
            case 2: em.showEmployData(); break;
            case 3: em.searchEmploy(); break;
            case 4: em.deleteEmploy(); break;
            case 5: em.updateEmploy(); break;
            case 6:
            	em.saveData();
                cout << termcolor::bold << termcolor::magenta << "\nThank you!\n" << termcolor::reset;
                return;
            default:
                cout << termcolor::red << "\nInvalid choice!" << termcolor::reset;
        }
    }
 }
 
 
 
 
 
// validation of username and password

// ? CHECK 1: Username Validator
bool isValidUsername(string username) {
    
    if (username.length() < 5) {
        cout << "? Username too short! Must be at least 5 characters.\n\n";
        return false;
    }

    
    bool hasLetter = false;
    for (char ch : username) {
        if (isalpha(ch)) {  // isalpha() checks if character is a letter
            hasLetter = true;
            break;
        }
    }

    if (!hasLetter) {
        cout << "? Username cannot be purely numbers! Must contain at least one letter.\n";
        return false;
    }

    return true;
}

