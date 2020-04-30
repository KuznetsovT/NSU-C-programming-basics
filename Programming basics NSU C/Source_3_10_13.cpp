
#define _CRT_SECURE_NO_WARNINGS

#include "Header_3_10_13.h"
#include <string.h>
#include <iostream>
using namespace std;

struct Cpeople {
	char name[32];
	char surname[32];
	char phone[32];
	char data[32];


	friend ostream & operator<<(ostream &out, const Cpeople & cp) {
		return out << "[ name: " << cp.name << " , surname: " << cp.surname << " , phone: " << cp.phone << " , data: " << cp.data << " ] ";
	}

	friend int operator<(const Cpeople o, const Cpeople t);
};

typedef DoubleLinkedList<Cpeople> database;
int compare_name(DoubleLinkedList<Cpeople>::iterator first, DoubleLinkedList<Cpeople>::iterator second);

int main() {

	database* list = new database();
	cout << "AWFUL USER INTERFACE'S GREATING YOU... print \"help\" if you need\n\n";
	for (;;) {
		char order[128];
		int status = scanf("%s", order);


		if (status == 0 || status == EOF) {
			cout << "Something's bad";

			continue;
		}
		if (!strcmp(order, "pushback")) {
			Cpeople cp;
			scanf("%s%s%s%s", cp.name, cp.surname, cp.phone, cp.data);
			list->push_back(cp);
			cout << "pushed\n";

			continue;
		}
		if (!strcmp(order, "pushfront")) {
			Cpeople cp;
			scanf("%s%s%s%s", cp.name, cp.surname, cp.phone, cp.data);
			list->push_front(cp);
			cout << "pushed\n";

			continue;
		}
		if (!strcmp(order, "peekback")) {
			if (!list->is_empty())
				cout << list->peek_back() << endl;
			else
				cout << "list is empty!\n";

			continue;
		}
		if (!strcmp(order, "peekfront")) {
			if (!list->is_empty())
				cout << list->peek_front() << endl;
			else
				cout << "list is empty!\n";

			continue;
		}
		if (!strcmp(order, "popback")) {
			if (!list->is_empty())
				cout << list->pop_back() << endl;
			else
				cout << "list is empty!\n";

			continue;
		}
		if (!strcmp(order, "popfront")) {
			if (!list->is_empty())
				cout << list->pop_front() << endl;
			else
				cout << "list is empty!\n";

			continue;
		}
		if (!strcmp(order, "size")) {
			
			cout << "size: " << list->length() << endl;
			continue;
		}

		if (!strcmp(order, "list")) {
			
			cout << *list << endl;
			continue;
		}

		if (!strcmp(order, "sort")) {
			list->sort();
			cout << *list << endl;
			continue;
		}

		if (!strcmp(order, "sortbyname")) {
			list->sort(compare_name);
			cout << *list << endl;
			continue;
		}

		if (!strcmp(order, "clear")) {
			delete list;
			list = new database();

			cout << "list'empty\n";
			continue;
		}
		if (!strcmp(order, "exit")) {
			
			delete list;
			return 0;
		}
		if (!strcmp(order, "help")) {
			cout <<
				"Menu:\n"
				<<"help: prints commands\n"
				<<"exit: exits\n"
				<<"pushback: push in the end of list. Then write name surname phone data\n"
				<<"pushfront:...at the begining\n"
				<<"peekfront:watch first element\n"
				<<"peekback:...last element\n"
				<<"popfront, popback:delete front, back elements\n"
				<<"size: returns list's size\n"
				<<"clear:clears list\n"
				<<"list:prints list\n"
				<<"sort: sorts and prints sorted list\n"
				<<"sortbyname: sorts only by name and surname\n";

			continue;
		}

		//default

		cout << "Wrong input!\n";
	}

	delete list;
	return 0;
}







int operator<(const Cpeople o, const Cpeople t)
{
	if (strcmp(o.name, t.name) == 0) {
		if (strcmp(o.surname, t.surname) == 0) {
			if (strcmp(o.phone, t.phone) == 0) return strcmp(o.data, t.data) < 0;
			else return strcmp(o.phone, t.phone) < 0;
		}
		else return strcmp(o.surname, t.surname) < 0;
	}
	else return strcmp(o.name, t.name) < 0;
}

int compare_name(DoubleLinkedList<Cpeople>::iterator first, DoubleLinkedList<Cpeople>::iterator second) {
	return strcmp((*first).name, (*second).name);
}