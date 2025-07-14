#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <conio.h>
#include <ctime>
#include<assert.h>
using namespace std;

class BookRecord
{
private:
	int ISSN;
	string Title;
	string  AuthorName;
	int  ref_books;
	int Issuable_books;

public:
	BookRecord()
	{
		ISSN = 0;
		Title = "xxx";
		AuthorName = "xxx";
		ref_books = 0;
		Issuable_books = 0;
	}

	int getISSN()    //getter for issn
	{
		return ISSN;
	}

	BookRecord(int _Id = 0, string _title = 0, string A_N = 0, int R_b = 0, int Ib = 0)
	{
		ISSN = _Id;
		Title = _title;
		AuthorName = A_N;
		ref_books = R_b;
		Issuable_books = Ib;
	}

	void Update_List(string _title = 0, string A_N = 0, int R_b = 0, int Ib = 0)
	{                              //this function can update all the content of BookRecord except issn
		Update_Title(_title);
		Update_Author(A_N);            
		Update_RefBooks(R_b);
		Update_IssuBooks(Ib);
	}

	void Update_Title(string _title)
	{
		this->Title = _title;
	}

	void Update_Author(string A_N)
	{
		this->AuthorName = A_N;
	}

	void Update_RefBooks(int R_b)
	{
		this->ref_books = R_b;
	}
	void Update_IssuBooks( int Ib)
	{
		this->Issuable_books = Ib;
	}

	friend ostream& operator<<(ostream& out, BookRecord& n)
	{
		out << "-----------------------------------------------------------" << endl;
		out << "Book Id : " << n.ISSN << endl;;
		out << "Book Name : " << n.Title << endl;
		out << "Author Name : " << n.AuthorName << endl;
		out << "Reference Books : " << n.ref_books << endl;
		out << "Issuable Books : " << n.Issuable_books << endl;
		out << "-----------------------------------------------------------" << endl;

		return out;
	}
};

class HashMap
{
	friend class BookRecord;

private:
	list<BookRecord> chain;
	vector<list<BookRecord> > HashTable;
	int capacity;


public:

	HashMap(int _capacity=20)
	{                           //constructor in which the size is set by user and by default with 20;
		capacity = _capacity;

		for (int i = 0; i < capacity; i++)
		{
			HashTable.push_back(chain);
		}
	}

	int UniverSal_HashFun(int ISSN)   // this function is universal hash function with using random number
	{                                 //generatero to avoid maximum collision
		srand(ISSN);
		int key = 0;
		key = rand() % capacity;
		return key;
	}

	void insert(int _Id = 0, string _title = 0, string A_N = 0, int R_b = 0, int Ib = 0)
	{                            //insert the BookRecord of book using hash funtion which can avoid collision          
		int key = UniverSal_HashFun(_Id);
		HashTable[key].push_back(BookRecord(_Id, _title, A_N, R_b, Ib));
	}

	void remove(int ISSN)
	{
		int key = UniverSal_HashFun(ISSN);

		list<BookRecord> ::iterator iter;
		iter = HashTable[key].begin();

		while (iter != HashTable[key].end())
		{
			if ((*iter).getISSN() == ISSN)
			{
				HashTable[key].erase(iter);
			}

		}
	}

	void update(int ISSN)
	{
		int key = UniverSal_HashFun(ISSN);

		int selection, refbooks, Issbooks;
		string name, AuthorName;

		list<BookRecord> ::iterator iter;
		iter = HashTable[key].begin();

		cout << "\nEnter 1  to change All data.";
		cout << "\nEnter 2 to change title of book.";
		cout << "\nEnter 3 to change  Authors name.";
		cout << "\nEnter 4 to change no of reference books.";
		cout << "\nEnter 5 to change no of issuable books." << endl << endl;
		cin >> selection;

		if (selection == 1)
		{
			cout << "Update book title : ";
			cin >> name;

			cout << "Update name of author : ";
			cin >> AuthorName;

			cout << "Update no of refernece books : ";
			cin >> refbooks;

			cout << "Update no of issuable books : ";
			cin >> Issbooks;

			while (iter != HashTable[key].end())
			{
				if ((*iter).getISSN() == ISSN)
				{
					(*iter).Update_List(name, AuthorName, refbooks, Issbooks);
				}

				iter++;
			}
		}

		if (selection == 2)
		{
			cout << "Enter the book title  : ";
			cin >> name;

			while (iter != HashTable[key].end())
			{
				if ((*iter).getISSN() == ISSN)
				{
					(*iter).Update_Title(name);
				}

				iter++;
			}
		}
		if (selection == 3)
		{
			cout << "Enter the name of author  : ";
			cin >> AuthorName;

			while (iter != HashTable[key].end())
			{
				if ((*iter).getISSN() == ISSN)
				{
					(*iter).Update_Author(AuthorName);
				}

				iter++;
			}
		}
		if (selection == 4)
		{
			cout << "Update no of issuable books : ";
			cin >> refbooks;

			while (iter != HashTable[key].end())
			{
				if ((*iter).getISSN() == ISSN)
				{
					(*iter).Update_RefBooks(refbooks);
				}

				iter++;
			}
		}
		if (selection == 5)
		{
			cout << "Update no of issuable books : ";
			cin >> Issbooks;

			while (iter != HashTable[key].end())
			{
				if ((*iter).getISSN() == ISSN)
				{
					(*iter).Update_IssuBooks(Issbooks);
				}

				iter++;
			}
		}
	}
	// function to display BookRecords by using BookRecord operator to cout iterater
	void Book_Records()
	{
		list<BookRecord> ::iterator iter;

		for (int i = 0; i < capacity; i++)
		{
			iter = HashTable[i].begin();

			while (iter != HashTable[i].end())
			{
				cout << *iter;

				iter++;
			}
		}
	}
};

int main()
{
	char c;

	cout << "\n\t\t\t........................LIBRARY MANAGEMENT SYSTEM..........................." << endl << endl;

	cout << "\n\n\t\tSystem Has following functionality.........." << endl << endl;
	cout << "1.In sytem there is Ram which store book records" << endl;
	cout << "2.there is unique ISSN that  assign to book" << endl;
	cout << "3.In library there has records of total books copies to be issued" << endl;
	cout << "4.In library there has records of reference book " << endl;
	cout << "5. we used universal hash function to implement the library" << endl;
	cout << "press enter key to continue" << endl;
	c = _getch();


	system("cls");


	HashMap hm(17);

	int totalBooks, i = 0;
	int issn = 0, ref_books = 0, Issuable_books = 0;
	string book_name, AuthorName;

	char ch;

	cout << "\n\t\tPress C to create a book record"
		<< "\n\t\tPress R to review a book record"
		<< "\n\t\tPress U to update a book record"
		<< "\n\t\tPress D to delete a book record  "
		<< "\n\t\tPress Q to Quit  ";

	ch = _getch();

	system("cls");

	while (true)
	{
		if (ch == 'C' || ch == 'c')
		{
			cout << "Enter number of books you want to insert : ";
			cin >> totalBooks;

			while (i < totalBooks)
			{
				cout << "\n\nEnter book id : ";
				cin >> issn;

				cout << "Enter book Title : ";
				cin >> book_name;

				cout << "Enter name of author : ";
				cin >> AuthorName;

				cout << "Enter no of refernece books : ";
				cin >> ref_books;

				cout << "Enter no of issuable books : ";
				cin >> Issuable_books;

				hm.insert(issn, book_name, AuthorName, ref_books, Issuable_books);

				i++;
			}
		}

		else if (ch == 'R' || ch == 'r')
		{
			hm.Book_Records();
		}
	

		else if (ch == 'U' || ch == 'u')
		{
			cout << "Enter ISSN of record you want to update : ";
			cin >> issn;

			hm.update(issn);
		}

		else if (ch == 'D' || ch == 'd')
		{
			int id;
			cout << "Enter id of record you want to delete : ";
			cin >> id;

			hm.remove(id);
		}

		else if (ch == 'Q' || ch == 'q')
		{
			break;
		}

		else
		{
			cout << "\nInvalid Input.";
		}

		cout << "\n\t\tPress C to create a book record"
			<< "\n\t\tPress R to review a book record"
			<< "\n\t\tPress U to update a book record"
			<< "\n\t\tPress D to delete a book record  "
			<< "\n\t\tPress Q to Quit  ";

		ch = _getch();

		system("cls");
	}
	return 0;
}
