#include <iostream>
#include <cstdlib>
#include "bst.h"
#include "avl.h"
using namespace std;

//--------------------------------------------------------------------
// Test Driver for bst and node classes
// Compiled under MS Visual C++.Net 20013, Windows 7
// by Paul Bladek
// December, 2000
// revised April, 2005
// revised June, 2015
//--------------------------------------------------------------------
int main(void)
{
	using PB_BST::bst;
	using PB_BST::node;
	using PB_BST::avl;
	try
	{
//		bst<char> tree;
//		node<char>* marker = nullptr;
//		char c;
//		cout << "enter some characters, followed by <enter>.\n" ;
//		do
//		{ 
//			cin.get(c);
//			if(c == '\n')
//				break;
//			tree.insert(c); 
//		}
//		while(true);
//		//
//		tree.printXlevel(cout);
//		tree.popFirstOf('D', tree.getroot());
//
//		tree.printXlevel(cout);
//		//
//		bst<char> tree2 = tree; // test overloaded =
//		tree2 += tree; // test overloaded +
//		cout << "tree 1:" << endl;		
//		cout << tree << " : " << tree.getNumberOfNodes()
//			<< "nodes" << endl;  // test overloaded << and print()
//		tree.printXlevel(cout);
//		cout  << endl << "tree 2:" << tree2 
//			<< tree.getNumberOfNodes() << "nodes" << endl;
//		tree2.printXlevel(cout);
//		cout << endl << endl << "Enter character to match: ";
//		cin >> c;
//		tree.findFirstOf(c, tree.getroot(), marker);
// 
//		// set marker to first match of c
//		if(marker != nullptr)
//			cout << marker->value();
//		else
//			cout << "not found";
//		cout << "\n Enter character to delete: ";
//		cin >> c;
//		cin.ignore(FILENAME_MAX, '\n');
//		c = tree.popFirstOf(c);
//  
//		// test popFirstOf(), popnode(), poplow()	
//		cout << "<" << c << ">  " << tree << endl;
//		tree.delTree();  // delete first tree
//		tree2 += 'Z';     // add in another element , test +=
////		tree2 = (tree + 'Y');  // test +		
//		cout << tree2 << endl;
//		cout << "tree 1:" << endl;		
//		cout << tree << " : " << tree.getNumberOfNodes()
//			<< "nodes" << endl;  // test overloaded << and print()
//		tree.printXlevel(cout);
//		cout  << endl << "tree 2:" << tree2 
//			<< tree.getNumberOfNodes() << "nodes" << endl;
//		tree2.printXlevel(cout);
//		cout << endl;
//		tree.delTree();  // delete second tree

		avl<char> treeA, treeB;
		node<char>* markerA = nullptr;
		cout << "Enter characters, followed by <Enter>.\n";
		char tests[5][4] = {
		"cba",	//Will cause left imbalance
		"def",	//Will cause right imbalance
		"igh",	//Will cause LR imbalance
		"klj",	//Will cause RL imbalance
		"nmo"	//Will not cause an imbalance
		};
		for (int i = 0; i < 5; i++)
		{
			treeA.deltree();
			for (int j = 0; j < 3; j++)
			{
				treeA.insert(tests[i][j]);
			}
			treeB += treeA;
			cout  << endl << "AVL tree:" << treeA 
					<< treeA.getNumberOfNodes() << "nodes" << endl;
			treeA.printXlevel(cout);	
			cout << endl << "AVL tree B:" << treeB
				<< treeB.getNumberOfNodes() << "nodes" << endl;
			treeB.printXlevel(cout);
		}
		cout << endl << "AVL tree B:" << treeB
			<< treeB.getNumberOfNodes() << "nodes" << endl;
		treeB.printXlevel(cout);
	
	}
	catch(invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(bad_alloc e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(exception e)
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

