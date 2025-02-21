/*
#include <iostream>
using namespace std;
void insert_end(int id);
void delete_end();
void display();

struct node {
	int id;
	node *next;
}; node *head = NULL;

void insert_end(int id)
{
	node *new1 = new node;
	new1->id = id;
	new1->next = NULL;
	node *temp;

	if (head == NULL)
	{
		head = new1;
		new1->next = head;
		cout << "\nNode becomes the head of insert at end function:\n\n" << endl;
	}

	else {
		temp = head;

		while (temp->next != head)
			temp = temp->next;

		temp->next = new1;
		new1->next = head;
		cout << "Node is inserted at end:\n\n" << endl;
	}
}

void delete_end() {
	node *temp = head;
	node *temp1=NULL;

	if (temp->next == temp) {
		delete(temp);
		head = NULL;
	}
	else {
		while (temp->next != head)
		{
			temp1 = temp;
			temp = temp->next;
		}
		temp1->next = head;
		delete(temp);
	}
	cout << "\nNode has been deleted from end:\n\n" << endl;
}

void display() {
	node *temp = head;
	cout << "ID: " << temp->id << endl;
	while (temp->next != head) {
		temp = temp->next;
		cout << "ID: " << temp->id << endl;
	}
}

int main()
{
	char c;
	int choice, value;

	do {
		cout << "\n\n=================================" << endl;
		cout << "   CIRCULAR LINK LIST IMPLEMENTATION  " << endl;
		cout << "=================================" << endl;

		cout << "\n1-    Insert an element at end       " << endl;
		cout << "2-    Delete an element at end      " << endl;
		cout << "3-    Display list        \n " << endl;
		cout << "choose any one from the above options: ";
		cin >> choice;
		
		if (choice == 1) {

			cout << "Enter an element for insertion: ";
			cin >> value;

			insert_end(value);
		}
		else if (choice == 2) {

			delete_end();
		}

		else if (choice == 3) {
			cout << "\n*************\n DISPLAY\nLink List\n*************" << endl;
			display();
		}

		else if (choice == 6) {

			exit(0);
		}

		cout << "\nPress 'y' to continue and ''n' to exit" << endl;
		cin >> c;
	} while (c == 'Y' || c == 'y');
	return 0;
}
*/