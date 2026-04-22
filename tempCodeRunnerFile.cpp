
		
		void updateData(){
			string name;
			int newId;
			double newSalary;
				int input;
				cout << "\nWhat you want to update: \n1. Name\n2. ID\n3. Salary\n4. All\nEnter your Choice:  ";
				cin >> input;
				if(input < 1 || input > 4){
					cout << "\nInvalid Choice!";
				}else{
				
				switch(input){
					case 1:
					
					cout << "\nEnter New Name: ";
					getline(cin >> ws,name);
					empName = name;
					break;
				case 2:
					
					cout << "\nEnter New ID: ";
					cin >> newId;
					empId = newId;
					break;
				case 3:
					
					cout << "\nEnter new Salary: ";
					cin >> newSalary;
					empSalary = newSalary;
					break;
					case 4:
						setName();
						setID(newId);
						setSalary();
						break;
				default:
					cout << "\nNo update!";
			}
}
		}