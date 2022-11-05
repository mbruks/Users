#include "Functions.h"

ostream& operator<<(ostream& os, const user& us) {
	os << us.last << ' ' << us.name << ' ' << us.middle << ' ' << us.phone << ' ';
	os << us.email << ' ' << us.login << ' ' << us.password << endl;
	return os;
}

bool read(const char* path, vector<user>& arr) {
	ifstream file;
	file.open(path);

	if (!file.is_open())
		return false;
	while (!file.eof()) //пока не достигнут конец файла
	{
		//считываемые строки:
		vector<string> str(7);

		//считываем 7 срок дл€ одного пользовател€
		for (int i = 0; i < 7; i++)
			file >> str[i];

		//объ€вл€ем объект класса ѕќЋ№«ќ¬ј“≈Ћ№ дл€ записи в него информации
		user u;
		u.last = str[0];
		u.name = str[1];
		u.middle = str[2];
		u.phone = str[3];
		u.email = str[4];
		u.login = str[5];
		u.password = str[6];

		//помещаем "пользовател€" в массив пользователей
		arr.push_back(u);
	}
	file.close();

	return true;
}

void print(const vector<user>& arr) {
	cout << "List of users: " << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i];
}

int search_login(const vector<user>& arr, string str) {
	int index = -1;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i].login == str)
			index = i;

	return index;
}

int search_FIO(const vector<user>& arr, string str1, string str2) {
	int ind = -1;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i].last == str1 && arr[i].name == str2)
			ind = i;

	return ind;
}

int search_phone(vector<user>& arr, string str) {
	int index = -1;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i].phone == str)
			index = i;

	return index;
}

string readLastname() {
	string str;
	cout << "Enter lastname:" << endl;
	cin >> str;
	while (!isCorrectName(str)) {
		cout << "Uncorrect lastname!" << endl;
		cout << "Enter lastname:" << endl;
		cin >> str;
	}
	return str;
}

string readName()
{
	string str;
	cout << "Enter name:" << endl;
	cin >> str;
	while (!isCorrectName(str)) {
		cout << "Uncorrect name!" << endl;
		cout << "Enter name:" << endl;
		cin >> str;
	}
	return str;
}

string readMiddlename()
{
	string str;
	cout << "Enter middle name:" << endl;
	cin >> str;
	while (!isCorrectName(str)) {
		cout << "Uncorrect middle name!" << endl;
		cout << "Enter middle name:" << endl;
		cin >> str;
	}
	return str;
}

string readPhone()
{
	string str;
	cout << "Enter phone number:" << endl;
	cin >> str;
	while (!isCorrectPhone(str)) {
		cout << "Uncorrect phone number!" << endl;
		cout << "Enter phone number:" << endl;
		cin >> str;
	}

	return convertPhone(str);
}

string readEmail()
{
	string str;
	cout << "Enter email:" << endl;
	cin >> str;
	while (!isCorrectEmail(str)) {
		cout << "Uncorrect email!" << endl;
		cout << "Enter email:" << endl;
		cin >> str;
	}
	return str;
}

string readLogin()
{
	string str;
	cout << "Enter login:" << endl;
	cin >> str;
	while (!isCorrectLogin(str)) {
		cout << "Uncorrect login!" << endl;
		cout << "Enter login:" << endl;
		cin >> str;
	}
	return str;
}

string readPassword() {
	string str;
	cout << "Enter password:" << endl;
	cin >> str;
	while (!isCorrectParol(str)) {
		cout << "Uncorrect parol" << endl;
		cout << "Enter parol:" << endl;
		cin >> str;
	}

	return md5(str);
}


void add_user(vector<user>& arr) {
	user new_user;
	string str;

	new_user.last = readLastname();

	new_user.name = readName();

	new_user.middle = readMiddlename();

	new_user.phone = readPhone();

	new_user.email = readEmail();

	new_user.login = readLogin();

	new_user.password = readPassword();

	arr.push_back(new_user);
}

void delete_by_FIO(vector<user>& arr) {
	string str1, str2;
	str1 = readLastname();
	str2 = readName();

	int ind = search_FIO(arr, str1, str2);

	if (ind >= 0)
		delete_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

void delete_by_login(vector<user>& arr) {
	string str;
	str = readLogin();
	int ind = search_login(arr, str);

	if (ind >= 0)
		delete_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

void delete_by_phone(vector<user>& arr) {
	string str;
	str = readPhone();
	int ind = search_phone(arr, str);

	if (ind >= 0)
		delete_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

bool isCorrectName(string str) {
	regex rg("[A-Z][a-z]+");

	return regex_match(str.begin(), str.end(), rg);
}

bool isCorrectEmail(string str) {
	regex rg("[a-z0-9]+[a-z0-9_\\-.]*[a-z0-9]+@[a-z]{2,}\\.[a-z]{2,6}");
	return regex_match(str.begin(), str.end(), rg);
}

bool isCorrectPhone(string str) {
	regex rg("(8|\\+7|7)[ (-]{0,2}[0-9]{3}[ )-]{0,2}[0-9]{3}[- ]?[0-9]{2}[- ]?[0-9]{2}");
	
	return regex_match(str.begin(), str.end(), rg);
}

string convertPhone(string str) {
	regex rg("\\+7-\\([0-9]{3}\\)-[0-9]{3}-[0-9]{2}-[0-9]{2}");
	if (!regex_match(str.begin(), str.end(), rg)) {
		string str_new("+7-(999)-555-44-22");
		string digits;
		for (int i = 0; i < str.size(); i++)
			if (str[i] >= '0' && str[i] <= '9')
				digits.push_back(str[i]);

		for (int i = 0; i < 3; i++)
			str_new[i+4] = digits[1 + i];

		for (int i = 0; i < 3; i++)
			str_new[i + 9] = digits[4 + i];

		for (int i = 0; i < 2; i++)
			str_new[i + 13] = digits[7 + i];

		for (int i = 0; i < 2; i++)
			str_new[i + 16] = digits[9 + i];

		return str_new;
	}
	return str;
}

bool isCorrectLogin(string str) {
	regex rg("[A-Za-z0-9]+[A-Za-z0-9_\\-.]*[A-Za-z0-9]+");
	return regex_match(str.begin(), str.end(), rg);
}

bool isCorrectParol(string str) {
	regex rg("(?=.*[0-9])(?=.*[!@#$%^&*])(?=.*[a-z])(?=.*[A-Z])[0-9a-zA-Z!@#$%^&*]{8,}");
	return regex_match(str.begin(), str.end(), rg);
}


void change_by_FIO(vector<user>& arr) {
	string str1, str2;
	str1 = readLastname();
	str2 = readName();

	int ind = search_FIO(arr, str1, str2);

	if (ind >= 0)
		change_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

void change_by_login(vector<user>& arr) {
	string str;
	str = readLogin();

	int ind = search_login(arr, str);

	if (ind >= 0)
		change_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

void change_by_phone(vector<user>& arr) {
	string str;
	str = readPhone();

	int ind = search_phone(arr, str);

	if (ind >= 0)
		change_user(arr, ind);
	else
		cout << "User not founded!" << endl;
}

void checkPassword(vector<user>& arr, int ind) {
	string str = readPassword();
	while (str != arr[ind].password) {
		cout << "Wrong password. Try again!";
		str = readPassword();
	}
}

void change_user(vector<user>& arr, int ind) {
	checkPassword(arr, ind);

	char c = 'a';
	string str;
	while (c != 'e') {
		cout << "-----------------" << endl;
		cout << "Change:" << endl;
		cout << "f - lastname" << endl;
		cout << "i - name" << endl;
		cout << "o - middle" << endl;
		cout << "m - email" << endl;
		cout << "l - login" << endl;
		cout << "p - password" << endl;
		cout << "n - phone" << endl;
		cout << "e - exit" << endl;
		cout << "-----------------" << endl;
		cout << "Enter symbol of command:" << endl;
		cin >> c;
		switch (c) {
		case 'f':
			arr[ind].last = readLastname();
			break;
		case 'i':
			arr[ind].name = readName();
			break;
		case 'o':
			arr[ind].middle = readMiddlename();
			break;
		case 'm':
			arr[ind].email = readEmail();
			break;
		case 'l':
			arr[ind].login = readLogin();
			break;
		case 'p':
			arr[ind].password = readPassword();
			break;
		case'n':
			arr[ind].phone = readPhone();
			break;
		default:
			if (c != 'e')
				cout << "Wrong command!" << endl;
		}
	}
}

void delete_user(vector<user>& arr, int ind) {
	arr.erase(arr.begin() + ind);
	cout << "User deleted!" << endl;
}

void write(const char* path, const vector<user>& arr) {
	ofstream file;
	file.open(path);

	for (int i = 0; i < arr.size(); i++)
		file << arr[i];

	file.close();
}

void delete_user_global(vector<user>& arr) {
	cout << "Delete: " << endl;
	cout << "f - by lastname and name" << endl;
	cout << "l - by login" << endl;
	cout << "p - by phone" << endl;
	char c;
	cin >> c;
	while (c != 'f' && c != 'l' && c != 'p') {
		cout << "Wrong command, try again.";
		cin >> c;
	}
	switch (c) {
	case 'f':
		delete_by_FIO(arr);
		break;
	case 'l':
		delete_by_login(arr);
		break;
	case 'p':
		delete_by_phone(arr);
		break;
	}
}

void change_user_global(vector<user>& arr) {
	cout << "Change: " << endl;
	cout << "f - by lastname and name" << endl;
	cout << "l - by login" << endl;
	cout << "p - by phone" << endl;
	char c;
	cin >> c;
	while (c != 'f' && c != 'l' && c != 'p') {
		cout << "Wrong command, try again.";
		cin >> c;
	}
	switch (c) {
	case 'f':
		change_by_FIO(arr);
		break;
	case 'l':
		change_by_login(arr);
		break;
	case 'p':
		change_by_phone(arr);
		break;
	}
}

void sort_database(vector<user>& arr) {
	cout << "Sort by:" << endl;
	cout << "f - lastname" << endl;
	cout << "i - name" << endl;
	cout << "o - middle" << endl;
	cout << "m - email" << endl;
	cout << "l - login" << endl;
	cout << "p - password" << endl;
	cout << "n - phone" << endl;

	char c;
	cin >> c;

	while (c != 'f' && c != 'i' && c != 'o' && c != 'm' && c != 'l' && c != 'p' && c != 'n') {
		cout << "Wrong command, try again.";
		cin >> c;
	}

	switch (c) {
	case 'f':
		quicksort(arr, 0, arr.size() - 1, isLessLastname);
		break;
	case 'i':
		quicksort(arr, 0, arr.size() - 1, isLessName);
		break;
	case 'o':
		quicksort(arr, 0, arr.size() - 1, isLessMiddlename);
		break;
	case 'm':
		quicksort(arr, 0, arr.size() - 1, isLessEmail);
		break;
	case 'l':
		quicksort(arr, 0, arr.size() - 1, isLessLogin);
		break;
	case 'p':
		quicksort(arr, 0, arr.size() - 1, isLessPassword);
		break;
	case'n':
		quicksort(arr, 0, arr.size() - 1, isLessPhone);
	}
}

bool isLessLastname(user u1, user u2) {
	if (u1.last < u2.last)
		return true;
	else
		return false;
}

bool isLessName(user u1, user u2) {
	if (u1.name < u2.name)
		return true;
	else
		return false;
}

bool isLessMiddlename(user u1, user u2) {
	if (u1.middle < u2.middle)
		return true;
	else
		return false;
}

bool isLessPhone(user u1, user u2) {
	if (u1.phone < u2.phone)
		return true;
	else
		return false;
}

bool isLessEmail(user u1, user u2) {
	if (u1.email < u2.email)
		return true;
	else
		return false;
}

bool isLessLogin(user u1, user u2) {
	if (u1.login < u2.login)
		return true;
	else
		return false;
}

bool isLessPassword(user u1, user u2) {
	if (u1.password < u2.password)
		return true;
	else
		return false;
}

void quicksort(vector<user>& mas, int first, int last, bool (*isLess) (user, user))
{
	int f = first, l = last;
	user mid = mas[(f + l) / 2]; //вычисление опорного элемента
	do
	{
		while (isLess(mas[f], mid)) f++;
		while (isLess(mid, mas[l])) l--;
		if (f <= l) //перестановка элементов
		{
			user temp = mas[f];
			mas[f] = mas[l];
			mas[l] = temp;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) quicksort(mas, first, l, isLess);
	if (f < last) quicksort(mas, f, last, isLess);
}