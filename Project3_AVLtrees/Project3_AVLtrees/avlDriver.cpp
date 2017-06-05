#include <iostream>
#include <cstdlib>
#include "avl.h"
using namespace std;

//--------------------------------------------------------------------
// Test Driver for avl class
// Compiled under MS Visual C++. 2015, Windows 10
// by Hiromi Cota
// Contains code from bstDriver.cpp by Paul Bladek
// 4 JUN 2017
//--------------------------------------------------------------------

int main()
{
	using PB_BST::avl;
	using PB_BST::node;
	try
	{
		avl<char> tree;
		node<char>* marker = nullptr;
		char c;
		cout << "Enter characters, followed by <Enter>.\n";
		do
		{
			cin.get(c);
			if (c == '\n')
				break;
				tree.insert(c);
		} while (true);

		tree.printXlevel(cout);

	}
	catch (invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch (bad_alloc e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch (exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << "press \"Enter\" to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
}