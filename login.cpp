#include <iostream>
#include <string>
#include <vector>
#include <conio.h>   // for _getch()
#include <fstream>
using namespace std;

class User {
public:
    string name;
    string password;
};

vector<User> users;

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
//Save function
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


int main() {
	while(true){	
	int c;
	cout << "Select: " << endl;
	cout << "1. Register " << endl;
	cout << "2. Exit " << endl;
	cout << "Enter your Choice: ";
	cin >> c;
	if(c == 1){
		registerUser();
		
	}else{
		return 0;
	}
	    
}
    return 0;
}
