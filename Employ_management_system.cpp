#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <conio.h> 
using namespace std;
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
        cout << "\nEnter Employee Name: ";
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
        cout << "\nEnter Employee Salary: ";
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
        cout << "\nName: " << empName;
        cout << "\nID: " << empId;
        cout << "\nSalary: " << empSalary;
        cout << "\n-----------------------------------\n";
    }

    // Only update NAME and SALARY (not ID)
    void updateData(){
        int choice;
        cout << "\n1. Update Name\n2. Update Salary\nEnter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                setName();
                break;
            case 2:
                setSalary();
                break;
            default:
                cout << "\nInvalid choice!";
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
			cout << "\nUnable to Open the File!";
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
			cout << "\nUnable to Open the File!";
			return;
		}
		for(Employee &employ : employs) {
			string name = employ.getName();
			int id = employ.getId();
			double sal = employ.getSalary();
			myfile << name << " | "<< id << " | "<< sal << endl;
		}
		myfile.close();
		cout << "\nData Saved Successfully.";
	}
	
    bool idChecker(int x){
        for(Employee &employ : employs){
            if(x == employ.getId()){
                cout << "\nID already exists!";
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
            cout << "\nEnter Employee ID: ";
            cin >> id;
        } while(idChecker(id));

        em.setID(id);
        em.setSalary();

        employs.push_back(em);

        cout << "\nEmployee Added Successfully!\n";
    }

    void showEmployData() const{
        if(employs.empty()){
            cout << "\nNo Employees Found!\n";
            return;
        }

        for(const Employee &employ : employs){
            employ.displayEmployData();
        }
    }

    void searchEmploy(){
        int id;
        cout << "\nEnter ID to search: ";
        cin >> id;

        for(const Employee &employ : employs){
            if(id == employ.getId()){
                cout << "\nEmployee Found:\n";
                employ.displayEmployData();
                return;
            }
        }

        cout << "\nEmployee not found!\n";
    }

    void updateEmploy(){
        int id;
        cout << "\nEnter Employee ID to update: ";
        cin >> id;

        for(Employee &employ : employs){
            if(id == employ.getId()){

                int choice;
                cout << "\n1. Update Name/Salary\n2. Update ID\nEnter choice: ";
                cin >> choice;

                if(choice == 1){
                    employ.updateData();
                }
                else if(choice == 2){
                    int newId;
                    do{
                        cout << "\nEnter New ID: ";
                        cin >> newId;
                    } while(idChecker(newId));

                    employ.setID(newId);
                }

                cout << "\nEmployee Updated Successfully!\n";
                return;
            }
        }

        cout << "\nEmployee not found!\n";
    }

    void deleteEmploy(){
        int id;
        cout << "\nEnter ID to delete: ";
        cin >> id;

        for(auto i = employs.begin(); i != employs.end(); i++){
            if(id == i->getId()){
                employs.erase(i);
                cout << "\nEmployee Deleted Successfully!\n";
                return;
            }
        }

        cout << "\nEmployee not found!\n";
    }
};

// Main and _FUNCTIONs

int menu(){
    int choice;
    cout << "\n\n===== Employee Management System =====\n";
    cout << "1. Add Employee\n2. Show Employees\n3. Search\n4. Delete\n5. Update\n6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int main(){
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
                cout << "\nThank you!\n";
                return 0;
            default:
                cout << "\nInvalid choice!";
        }
    }
}

//Password Function
void inputPassword(string &password) {
    char ch;
    password.clear();  // clear previous data

    cout << "\nEnter Password (masking enabled): ";

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
            cout << "*";
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

    cout << "\n************************************* Register a new User.. ************************************************\n";
	string name;
	
    while(true){	
    bool exists = false;
    cout << "\nEnter Username: ";
    getline(cin >> ws, name);   // input into object
    for(const User &user : users){
    	if(name == user.name){
    		cout << "User already exists!...." <<endl;
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
    cout << "\n-------------Registration Successful!------------------------------\n\n";
 	save()   ;
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
