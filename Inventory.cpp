#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// Used to get unbuffered key input
#include <conio.h>

//Used for editing command line text styling
//#include <cwchar>
//#include <windows.h>

using namespace std;

//course of action enum for the program to handle program execution
enum courseofaction {
	cont,
	retry,
	_end
} coa;

struct item {
	string item_num;
	int quantity;
	courseofaction coa;

	void setItem_Num() {
		cout << "Please scan the Barcode!" << endl;
		cin >> item_num;
	}

	void setQuantity() {
		cout << "How many are included in the shipment:" << endl;
		cin >> quantity;
	}

	courseofaction review() {
		//show input to the user 
		cout << "Item number: " << item_num << endl;
		cout << "Quantity Included: " << quantity << endl;

		//prompt to go on or retry data entry
		char ch;
		cout << "[C]ontinue, [R]etry or [E]nd?" << endl;
		if ((ch = _getch()) != EOF && ch == 'c') {
			//the information is correct
			return coa = cont;
		}
		else if (ch == 'r') {
			//the information is wrong and needs re-entered
			return coa = retry;
		}
		else if (ch == 'e') {
			//Finish and print results
			return coa = _end;
		}
	}
};

//ostream &operator<<(ostream &os, vector<string> &v)
//{
//	for (auto &i : v)
//		os << v << endl;
//
//	return os;
//}

int main()
{
	string ponum, date;
	vector<item> itemlist;

	cout << "Please enter a purchase order number: " << endl;
	cin >> ponum; 

	cout << "Please enter a date for this purchase order (MMDDYY): " << endl;
	cin >> date;

	bool morelinenumbers = true;
	item po_item;

	while (morelinenumbers) {
		po_item.setItem_Num();
		po_item.setQuantity();
		courseofaction path = po_item.review();

		//review info, if good, put in list otherwise reprompt for information
		if (path == cont) {
			itemlist.push_back(po_item);
			cout << "You have entered in " << itemlist.size() << " items" << endl;
		}
		else if (path == _end) {
			itemlist.push_back(po_item);

			ofstream outfile;
			outfile.open(ponum + "-" + date + ".csv");
			outfile << "Item Number, Quantity" << endl;

			//add them to csv file
			for (auto i : itemlist) {
				outfile << i.item_num << ',' << i.quantity << endl;
			}
			outfile.close();
			morelinenumbers = false;
		}
	}

	//system("pause");

	return 0;
}

