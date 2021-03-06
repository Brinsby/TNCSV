#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
// For text table spacing
#include <iomanip>
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
	edit,
	_end
} coa;

struct item 
{
	string item_num;
	int quantity;
	courseofaction coa;

	void setItem_Num() 
	{
	B1:
		cout << "Please scan the Barcode!" << endl;
		cin >> item_num;
		if (!(int)item_num.length() <= 13 && !(int)item_num.length() >= 5)
		{
			cout << "Please enter a number that is 13 digits long" << endl;
			cin.clear();
			cout.clear();
			goto B1;
		}
		for (int j = 0; j < item_num.length() ; j++)
		{
			if (isdigit(item_num[j]))
				continue;
			else
			{
				cout << "Please enter a number without characters/letters" << endl;
				cin.clear();
				goto B1;
			}
		}
	}

	void setQuantity() {
		cout << "How many are included in the shipment:" << endl;
		cin >> quantity;
	}

	courseofaction review(vector<item> list)
	{
		//prompt to go on or retry data entry
		char ch;
		cout << "[C]ontinue, [E]dit or [Q]uit?" << endl;
		if ((ch = _getch()) != EOF && ch == 'c')
		{
			//the information is correct
			return coa = cont;
		}
		else if (ch == 'e') 
		{
			//lets user edit previous entries
			return coa = edit;
		}
		else if (ch == 'q') 
		{
			//Finish and print results
			return coa = _end;
		}
	}
};


void DrawTable(vector<item> list) {
	int v = 0, c = 1;
	system("CLS");

	cout << "__________________________________________" << endl;
	cout << "|" << "Line #" << setw(3) << '|' << "   Item Number" << setw(4) << '|' << setw(8) << "   Quantity" << setw(4) << "|" << endl;
	cout << "__________________________________________" << endl;
	do
	{
		if (!list.empty()) {
			//show input to the user 
			cout << "|" << c << ")" << setw(7) << '|' << "  " << list[v].item_num << setw(3) << '|' << setw(8) << list[v].quantity << setw(7) << "|" << endl;
			cout << "__________________________________________" << endl;
			v++;
			c++;
		}
	} while (v < list.size());
}

int main()
{
	string date, ponum;
	int ponumlen = 11;
	vector<item> itemlist;

S1:		// Type checks and length checks the purchase order
	cout << "Please enter a purchase order number: " << endl;
	cin >> ponum; 
		if ((int)ponum.length() != 12) 
		{
			cout << "Please enter a number that is 12 digits long" << endl;
			cin.clear();
			cout.clear();
			goto S1;
		}
		for (int i = 0; i < ponumlen+1; i++)
		{
			if (isdigit(ponum[i]))
				continue;
			else
			{
				cout << "Please enter a number without characters/letters" << endl;
				cin.clear();
				goto S1;
			}
		}

		// enter the date of purchase order
	cout << "Please enter a date for this purchase order (MMDDYY): " << endl;
	cin >> date;

	bool morelinenumbers = true;
	item po_item;

	system("CLS");
	DrawTable(itemlist);

	while (morelinenumbers) 
	{
		// Draws table and pushes item num and quantity into table
		DrawTable(itemlist);
		po_item.setItem_Num();
		po_item.setQuantity();
		itemlist.push_back(po_item);
		DrawTable(itemlist);
		courseofaction path = po_item.review(itemlist);
		

		//review info, if good, put in list otherwise reprompt for information
		
		if (path == edit) {
			itemlist.push_back(po_item);
			int temp = 0;
			cout << "Number to edit" << endl;
			cin >> temp;

			cout << itemlist[temp-1].item_num << endl;
			cout << "enter new item number" << endl;
			cin >> itemlist[temp-1].item_num;


		}
		else if (path == _end) {
			itemlist.push_back(po_item);

			ofstream outfile;
			outfile.open(ponum + "-" + date + ".csv");

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

