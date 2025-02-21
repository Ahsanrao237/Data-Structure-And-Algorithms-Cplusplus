#include<iostream>
#include <fstream>
#include<string>
#include<ctime>
#include<Windows.h>
using namespace std;
void add_book(string b_name);
void add_student(string name, string reg);
void book_issue(string name, string b_name, string reg);
void return_book(string name, string reg, string b_name);
bool ser_book(string b_name);
bool ser_student(string reg);
bool ser_record(string reg);
int search_Pos(string reg, string b_name);
void delete_book(string b_name);
void display_books();
void current_time();
void Fine_charge(int pos);
int issue_siz();
int book_siz();

int main() {                          //////////main()
	char c;
	string b_name, name, reg;
	int ch;

	do {
		cout << "\n\n============================" << endl;
		cout << "  LIBRARY MANAGEMENT SYSTEM   " << endl;
		cout << "============================" << endl;

		cout << "\n1-    ADD BOOK        " << endl;
		cout << "2-    ADD STUDENT       " << endl;
		cout << "3-    SEARCH BOOK       " << endl;
		cout << "4-    ISSUE BOOK         " << endl;
		cout << "5-    Return Book         " << endl;
		cout << "6-    BOOKS DETAILS" << endl;
		cout << "choose any one from the above options: ";
		cin >> ch;
		if (ch == 1) {
			cout << "\n\n================== " << endl;
			cout << "      ADD BOOK         " << endl;
			cout << "==================" << endl;
			cout << "\n Enter Book Name: ";
			cin >> b_name;

			add_book(b_name);
		}
		else if (ch == 2) {
			cout << "\n\n================== " << endl;
			cout << "      ADD Student         " << endl;
			cout << "==================" << endl;
			cout << "\nEnter your your name to be able to issue the book:";
			cin >> name;
			cout << "Enter your Registration Number:";
			cin >> reg;

			add_student(name, reg);
		}
		else if (ch == 3) {
			cout << "\n\n======================" << endl;
			cout << "      SEARCH BOOK         " << endl;
			cout << "======================" << endl;
			cout << "Enter Book That You Want to Search: ";
			cin >> b_name;
			ser_book(b_name);
		}

		else if (ch == 4) {
			cout << "\n\n======================" << endl;
			cout << "        ISSUE BOOK        " << endl;
			cout << "======================" << endl;
			cout << "Name the BOOK which you want to Issue: ";
			cin >> b_name;
			cout << "Enter Your Name : ";
			cin >> name;
			cout << "Enter Reg Num : ";
			cin >> reg;

			book_issue(name, b_name, reg);
		}
		else if (ch == 5) {
			cout << "\t==============================" << endl;
			cout << "\t         RETURN BOOK                " << endl;
			cout << "\t==============================" << endl;

			cout << "Enter your Name: ";
			cin >> name;
			cout << "Enter your registration number: ";
			cin >> reg;
			cout << "Enter book name which you issued: ";
			cin >> b_name;

			return_book(name, reg, b_name);
		}

		else if (ch == 6) {
			cout << "\n\n================== " << endl;
			cout << "   BOOK DETAILS         " << endl;
			cout << "==================" << endl;
			display_books();
		}
		cout << "\nPress 'y' to continue and 'n' to exit:";
		cin >> c;
	} while (c == 'Y' || c == 'y');
	system("pause");
	return 0;
}

struct book {
	string b_name;
	book *next;

}; book *book_head = NULL;

struct student {
	string name;
	string reg;
	student *next;

}; student *stu_head = NULL;

struct issue_book {
	string b_name;
	string name;
	string reg;
	int due_d, due_m, due_y;
	issue_book *next;
}; issue_book *issue_head = NULL;

void add_student(string name, string reg) {                    /////ADD STUDENT METHOD
															   //Add student in file:
	ofstream f_out("Student.txt", ios::out | ios::app);

	if (f_out.fail()) {
		cerr << "Error Opening File:" << endl;
		exit(1);
	}
	else {
		f_out << name << endl;
		f_out << reg << "\n" << endl;
		f_out.close();
	}

	//Add student in link list:
	student *stu1 = new student;
	stu1->name = name;
	stu1->reg = reg;
	stu1->next = NULL;
	student *temp;

	if (stu_head == NULL) {
		stu_head = stu1;
	}
	else {
		temp = stu_head;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = stu1;
	}
	cout << "\n-----------x-----------x-----------x-----------x-----------" << endl;
	cout << "Student named " << name << " Registered succesfully: " << endl;
	cout << "Now he/she can Issue any book from Library for particular time:" << endl;
	cout << "-----------x-----------x-----------x-----------x-----------\n" << endl;
}

void add_book(string b_name) {              /////ADD BOOK METHOD

											//Add book in file:
	ofstream f_out("Books.txt", ios::out | ios::app);
	if (f_out.fail()) {
		cerr << "Error in Add Book File:" << endl;
		exit(1);
	}
	else {
		f_out << b_name << endl;
		f_out.close();
	}

	//Add book in link list:
	book *b1 = new book;
	b1->b_name = b_name;
	b1->next = NULL;
	book *temp;
	if (book_head == NULL) {
		book_head = b1;
	}
	else {
		temp = book_head;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = b1;
	}
	cout << "\n-----------x-----------x-----------x-----------x" << endl;
	cout << b_name << " book successfully added in Library:" << endl;
	cout << "Now this book can be Issued by registered students:" << endl;
	cout << "-----------x-----------x-----------x-----------x--\n" << endl;
}

void book_issue(string name, string b_name, string reg) {          //////////ISSUE BOOK METHOD:

	if (ser_record(reg) == true) {
		cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
		cout << "                     Sorry we can't Issue book" << endl;
		cout << "First Return the last book which you issued then issue a new one:  \n" << endl;
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" << endl;
	}
	else if (ser_book(b_name) == true && ser_student(reg) == true && ser_record(reg) == false) {
		//Add Record in File:
		ofstream f_out("Record.txt", ios::out | ios::app);
		if (f_out.fail()) {
			cerr << "Error in Adding Record in File:" << endl;
			exit(1);
		}
		else {
			f_out << name << endl;
			f_out << reg << endl;
			f_out << b_name << endl;
			f_out.close();
		}

		//take current date from OS and after modification save it in record as issue date:
		SYSTEMTIME a;
		GetLocalTime(&a);
		int day = a.wDay+10, month = a.wMonth, year = a.wYear;
		if (day > 30) {
			month++;
			day = day - 30;
		}
		if (month > 12)
			year++;

		//Add record in link list
		issue_book *issue1 = new issue_book;
		issue1->name = name;
		issue1->b_name = b_name;
		issue1->reg = reg;
		issue1->due_d = day;
		issue1->due_m = month;
		issue1->due_y = year;
		issue1->next = NULL;
		issue_book *temp;

		if (issue_head == NULL) {
			issue_head = issue1;
		}
		else {
			temp = issue_head;
			while (temp->next != NULL)
				temp = temp->next;

			temp->next = issue1;
		}
		delete_book(b_name);
		cout << "\n-----------x-----------x-----------x-----------x---" << endl;
		cout << b_name << " book Issued successfully to " << name << endl;
		cout << "Now you have to return this book in 10 days" << endl;
		cout << "Otherwise you have to charge fine of 10$ perday:" << endl;
		current_time();
		cout << "-----------x-----------x-----------x-----------x---\n" << endl;
	}
}

void return_book(string name, string reg, string b_name)      //////////RETURN BOOK:
{
	if (ser_record(reg) == true) {

		//Delete record from file:
		ifstream f_in;
		f_in.open("Record.txt");
		if (f_in.fail()) {
			cerr << "Error in returning book:" << endl;
			exit(1);
		}
		else {
			string line;
			ofstream f_out;
			f_out.open("temp.txt");

			while (getline(f_in, line)) {
				if (line != name && line != reg && line != b_name)
					f_out << line << endl;
			}
			f_in.close();
			f_out.close();
			remove("Record.txt");
			rename("temp.txt", "Record.txt");
		}

		//delete record from link list:
		issue_book *temp = issue_head;
		issue_book *temp1=NULL;
		int pos = search_Pos(reg, "NULL");
		Fine_charge(pos);
		if (pos == 1) {
			//if pos==1 delete node from front:
			issue_head = issue_head->next;
			delete(temp);
		}

		else if (pos == issue_siz()) {
			////if pos==(complete size of list) apply delete node from end:
			while (temp->next != NULL) {
				temp1 = temp;
				temp = temp->next;
			}
			temp1->next = NULL;
			delete(temp);
		}
		else {
			for (int i = 1; i<pos; i++) {
				temp1 = temp;
				temp = temp->next;
			}
			temp1->next = temp->next;
			delete(temp);
		}

		cout << "\n-----------x-----------x-----------x---------" << endl;
		cout << b_name << " Book Return Successfully" << endl;
		cout << "Now you Can issue another Book from Library" << endl;
		cout << "-----------x-----------x-----------x---------\n" << endl;
		add_book(b_name);
	}
	else
		cout << "\nYour Registration number is not in library Record file:\n" << endl;
}

bool ser_book(string b_name)                             ////////Search book method
{
	bool flag = false;
	string line;
	//Search Book from file:
	ifstream f_in;
	f_in.open("Books.txt", ios::in);

	if (f_in.fail()) {
		cerr << "Error in Searching Books File:" << endl;
		exit(1);
	}
	else {
		while (!f_in.eof()) {
			getline(f_in, line);
			if (line == b_name) {
				flag = true;
				f_in.close();
			}
		}
	}
	//Search BOOK from link list:
	book *temp = book_head;

	if (temp == NULL) {
		cout << "" << endl;
	}
	else {
		//Find position of record:
		for (int i = 0; i<book_siz(); i++) {
			if (temp->b_name == b_name) {
				flag = true;
				break;
			}
			else
				temp = temp->next;
		}
	}
	if (flag == true) {
		cout << "\nYour desired book is available in our library\n " << endl;
		return true;
	}
	else {
		cout << "\nYour desired book is not available in our library\n " << endl;
		return false;
	}
}

bool ser_student(string reg)                             ////////Search Student method
{
	bool flag = false;
	string line;
	//Search student from file:
	ifstream f_in;
	f_in.open("Student.txt", ios::in);

	if (f_in.fail()) {
		cerr << "Error in Searching Student File:" << endl;
		exit(1);
	}
	else {
		while (!f_in.eof()) {
			getline(f_in, line);

			if (line == reg) {
				flag = true;
				f_in.close();
			}
		}
	}
	//Search Student From link list:
	student *temp = stu_head;
	student *siz_temp = stu_head;
	int siz = 1;

	if (temp == NULL) {
		cout << "" << endl;
	}

	else {
		//Find size of link list:
		while (siz_temp->next != NULL) {
			siz_temp = siz_temp->next;
			siz++;
		}
		//Find position of record:
		for (int i = 0; i<siz; i++) {
			if (temp->reg == reg) {
				flag = true;
				break;
			}
			else
				temp = temp->next;
		}
	}
	if (flag == true) {
		cout << "\nStudent is Registered in Library:" << endl;
		return true;
	}
	else {
		cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
		cout << "Student is not Registered in Library:" << endl;
		cout << "First registered yourself then Issue a book" << endl;
		cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
		return false;
	}
}

bool ser_record(string reg)                       /////////Search RECORD method
{
	bool flag = false;
	string line;
	//Search Record from file:
	ifstream f_in;
	f_in.open("Record.txt", ios::in);

	if (f_in.fail()) {
		cerr << "Error in Searching Record File:" << endl;
		exit(1);
	}
	else {
		while (!f_in.eof()) {
			getline(f_in, line);
			if (line == reg) {
				flag = true;
				f_in.close();
			}
		}
	}
	//Search Record from link list:
	issue_book *temp = issue_head;

	if (temp == NULL) {
		cout << "" << endl;
	}
	else {
		//Find position of record:
		for (int i = 0; i<issue_siz(); i++) {
			if (temp->reg == reg) {
				flag = true;
				break;
			}
			else
				temp = temp->next;
		}
	}
	if (flag == true)
		return true;

	else
		return false;
}

void display_books() {                         //////DISPLAY BOOKS LIST
											   //Display Books from file:
	string line;
	ifstream f_in;
	f_in.open("Books.txt", ios::in);

	if (f_in.fail()) {
		cerr << "Error in Displaying Books Details from File:" << endl;
		exit(1);
	}
	else {
		while (!f_in.eof()) {
			getline(f_in, line);
			cout << line << endl;
		}
		f_in.close();
	}
	//Display books from link list:
	book *temp = book_head;
	while (temp->next != NULL) {
		temp = temp->next;
		//cout<<temp->b_name<<endl;
	}
}

void Fine_charge(int pos) {
     bool flag = false;
     do
     {
     	//charge fine by taking current date from OS and comparing it with due date of book issue:
      	SYSTEMTIME a;
        GetLocalTime(&a);
        int day = a.wDay, month = a.wMonth, year = a.wYear;

        int due_date, due_mon, due_year;
        cout << "\nEnter correct Due date of Book which you Issued :" << endl;
        cout << "Date:";
        cin >> due_date;
        cout << "Month: ";
        cin >> due_mon;
        cout << "Year: ";
        cin >> due_year;
        cout << "\nDUE DATE: " << due_date << "-" << due_mon << "-" << due_year << endl;

        //Search Due Date record from link list:
        issue_book *temp = issue_head;

        if (temp == NULL)
            cout << "" << endl;

        else {
            //take node to the desired record location:
            for (int i = 1; i < pos; i++)
            temp = temp->next;
        }

        if (temp->due_d == due_date && temp->due_m == due_mon && temp->due_y == due_year)
        {
            flag = true;

            if (day > temp->due_d || month > temp->due_m || year > temp->due_y)
                cout << "\nDue date is crossed so pay Fine of 10$ " << endl;

            else
                cout << "\nThank you for Returning book on time:" << endl;
        }

        else
            cout << "\nPlease Enter correct Due Date:\nPlease Reenter Due Date:" << endl;

      } while (flag == false);
}

void delete_book(string b_name) {                    ////////////DELETE BOOK
													 //Delete book from file:
	ifstream f_in;
	f_in.open("Books.txt");
	if (f_in.fail()) {
		cerr << "Error Opening File:" << endl;
		exit(1);
	}
	else {
		string line;
		ofstream f_out;
		f_out.open("temp.txt");

		while (getline(f_in, line)) {
			if (line != b_name)
				f_out << line << endl;
		}

		f_in.close();
		f_out.close();
		remove("Books.txt");
		rename("temp.txt", "Books.txt");
	}

	//delete book from link list:
	book *temp = book_head;
	book *temp1=NULL;
	int pos = search_Pos("NULL", b_name);

	if (pos == 1) {
		//if pos==1 delete node from front:
		book_head = book_head->next;
		delete(temp);
	}
	else if (pos != 1 && pos != book_siz()) {
		for (int i = 1; i<pos; i++) {
			temp1 = temp;
			temp = temp->next;
		}
		temp1->next = temp->next;
		delete(temp);
	}
	else if (pos == book_siz()) {
		////if pos==(complete size of list) apply delete node from end:
		while (temp->next != NULL) {
			temp1 = temp;
			temp = temp->next;
		}
		temp1->next = NULL;
		delete(temp);
	}
	else
		cout << "Enter correct position:" << endl;
}

int search_Pos(string reg, string b_name)                          /////Search Record Position:
{   //for searching book position:
	if (reg != "NULL") {
		issue_book *temp = issue_head;
		int count = 1, pos = -1;
		bool flag = false;

		if (temp == NULL)
			flag = false;

		else {
			for (int i = 0; i<issue_siz(); i++) {
				if (temp->reg == reg) {
					flag = true;
					break;
				}
				else
					temp = temp->next;

				count++;
			}
		}
		if (flag == true)
			return count;

		else if (flag = false)
			return pos;
	}

	//for searching book position:
	else if (b_name != "NULL") {
		book *temp = book_head;
		int count = 1, pos = -1;
		bool flag = false;

		if (temp == NULL)
			flag = false;

		else {
			for (int i = 0; i<book_siz(); i++) {
				if (temp->b_name == b_name) {
					flag = true;
					break;
				}
				else
					temp = temp->next;

				count++;
			}
		}

		if (flag == true)
			return count;

		else if (flag = false)
			return pos;
	}
}

int issue_siz() {                         /////////////////SIZE OF ISSUED_BOOKS RECORD
	issue_book *temp = issue_head;
	int count = 1;
	//Find size of link list:
	while (temp->next != NULL) {
		temp = temp->next;
		count++;
	}
	return count;
}
int book_siz() {                         ///////////////////BOOK SIZE
	book *temp = book_head;
	int count = 1;
	//Find size of link list:
	while (temp->next != NULL) {
		temp = temp->next;
		count++;
	}
	return count;
}

void current_time() {                            ///////////current time
	ofstream f_out("Record.txt", ios::out | ios::app);
	if (f_out.fail()) {
		cerr << "Error in Inserting time in File:" << endl;
		exit(1);
	}
	else {
		SYSTEMTIME a;
		GetLocalTime(&a);
		int day = a.wDay;
		int month = a.wMonth;
		int year = a.wYear;
		int duedate = day + 10;

		if (duedate > 30) {
			month++;
			duedate = duedate - 30;
		}
		if (month > 12)
			year++;

		f_out << "DUE DATE:\n" << duedate << "\n" << month << "\n" << year << "\n" << endl;
		f_out.close();

		cout << "Current DATE: " << day << "/" << month << "/" << year << endl;
		cout << "Due DATE: " << duedate << "/" << month << "/" << year << endl;
	}
}
