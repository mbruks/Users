#include "Header.h"

int main() {
	vector<user> arr;
	if (!read("BD.txt", arr)) {
		cout << "ERROR: Can't open file.";
		cout << "Database is empty";
	}

	char c = 'a';

	while (c!='*') {
		cout << "......................." << endl;
		cout << "MENU:" << endl;
		cout << "p - Print users." << endl;
		cout << "a - Add user." << endl;
		cout << "d - Delete user." << endl;
		cout << "c - Change user." << endl;
		cout << "w - Rewrite database." << endl;
		cout << "e - Send e-mail." << endl;
		cout << "s - Sort database." << endl;
		cout << "* - Exit." << endl;
		cout << "......................." << endl;
		cout << "Enter command:" << endl;
		cin >> c;
		switch (c) {
		case 'p': 
			print(arr);
			break;
		case 'a':
			add_user(arr);
			break;
		case 'd':
			delete_user_global(arr);
			break;
		case 'c':
			change_user_global(arr);
			break;
		case 'w':
			write("BD.txt", arr);
			break;
		case 'e':
			send_email();
			break;
		case 's':
			sort_database(arr);
			break;
		default:
			if (c != '*')
				cout << "Wrong command!" << endl;
		}
	}
	
	cout << "Program is completed!" << endl;
	return 0;
}