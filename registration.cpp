#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <conio.h>
using namespace std;
		bool is_blank(const string& s) {
    
    return all_of(s.begin(), s.end(), [](unsigned char ch) {
        return isspace(ch);
    });
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

//	void loadData(){
//		ifstream myfile("employList.txt");
//		if(!myfile.is_open()){
//			cout << "\nUnable to Open the File!";
//			return;
//		}
//		employs.clear();
//		string line;
//		string name;
//		string id;
//		string sal;
//		while(getline(myfile,line)){
//			if(is_blank(line)){
//				continue;
//			}
//			stringstream ss(line);
//			getline(ss, name, '|');
//			getline(ss, id, '|');
//			getline(ss, sal, '|');
//
//			int Id = stoi(id);
//			double Sal = stod(sal);
//			Employee emp;
//			emp.setNameByPar(name);
//			emp.setID(Id);
//			emp.setSalaryByPar(Sal);
//			employs.push_back(emp);////////////////////////**********************************
//		}
//		myfile.close();
//	}


class User{
	public:
	string name;
	string password;
};
vector <User> users;
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
//        stringstream ss(line);
//        ss >> username >> pass;   // ? FIX
//
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
void login(){
	string name,pass;
	cout << "Login : "<<endl;
	cout << "Enter username: ";
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
		cout << "Login Successful." << endl;
	}else{
			cout << "User not Found!" << endl;
		}
			
}
//int login_user() {
//    char username[CREDENTIAL_LENGTH];
//    char password[CREDENTIAL_LENGTH];
//
//    printf("\nEnter Username: ");
//    fgets(username, CREDENTIAL_LENGTH, stdin);
//    fix_input(username);
//
//    input_password(password);
//
//    for (int i = 0; i < user_count; i++) {
//        if (strcmp(username, users[i].username) == 0 &&
//            strcmp(password, users[i].password) == 0) {
//            return i;
//        }
//    }
//    return -1;
//}


int main(){
	load()	;
	login();
//	for(User u : users){
//		cout << u.name << " " << u.password << endl;;
//	}

	return 0;
}
