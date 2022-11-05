#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "User.h"
#include "md5.h"
using namespace std;

bool read(const char* path, vector<user>& arr);
void print(const vector<user>& arr);
int search_login(const vector<user>& arr, string str);
int search_FIO(const vector<user>& arr, string str1, string str2);
int search_phone(vector<user>& arr, string str);
string readLastname();
string readName();
string readMiddlename();
string readPhone();
string readEmail();
string readLogin();
string readPassword();
void add_user(vector<user>& arr);
void delete_by_FIO(vector<user>& arr);
void delete_by_login(vector<user>& arr);
void delete_by_phone(vector<user>& arr);
bool isCorrectName(string str);
bool isCorrectEmail(string str);
bool isCorrectPhone(string str);
string convertPhone(string str);
bool isCorrectLogin(string str);
bool isCorrectParol(string str);
void change_by_FIO(vector<user>& arr);
void change_by_login(vector<user>& arr);
void change_by_phone(vector<user>& arr);
void checkPassword(vector<user>& arr, int ind);
void change_user(vector<user>& arr, int ind);
void delete_user(vector<user>& arr, int ind);
void write(const char* path, const vector<user>& arr);
ostream& operator<<(ostream& os, const user& us);
void delete_user_global(vector<user>& arr);
void change_user_global(vector<user>& arr);
void sort_database(vector<user>& arr);
bool isLessLastname(user u1, user u2);
bool isLessName(user u1, user u2);
bool isLessMiddlename(user u1, user u2);
bool isLessPhone(user u1, user u2);
bool isLessEmail(user u1, user u2);
bool isLessLogin(user u1, user u2);
bool isLessPassword(user u1, user u2);
void quicksort(vector<user>& mas, int first, int last, bool (*isLess) (user, user));