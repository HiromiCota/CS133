#ifndef AVL_H
#define AVL_H
//--------------------------------------------------------------------
// An AVL tree class
// Compiled under MS Visual C++.Net 2005
// by Paul Bladek
// May, 2008
//--------------------------------------------------------------------

#include "bst.h"
using namespace std;


namespace PB_BST
{
//--------------------------------------------------------------------
// AVL Tree
//   Class: avl<T>: public bst<T>
//   REQUIRES Type T be able convert from int & have < & == defined
//
//   File: avl.h
//   Title: avl template Class -- inherits from bst<T>
//   Description: This file contains the class definition for avl
//
//   Programmer:  Paul Bladek
// 
//   Date:  May 2008
//   Version: 1.0
// 
//   Environment: Hardware: IBM Pentium 
//   Software: Windows XP or .Net Framework for execution;
//
//   Compiles under Microsoft Visual C++.Net 2005
// 
//   class avl<T>:
//
//
//     Methods:
// 
//       inline: 
//			avl() -- default constructor
//			avl(const avl<T>& t) -- copy constructor (deep copy)
//			avl<T>& operator+=(const T d) -- adds an element to the tree
//			avl<T> operator+(const T d) -- adds an element to the tree
//			void insert(T d) -- adds an element to the tree
//			~avl() -- destructor	
//
//       non-inline:
//			avl<T>& operator=(const avl<T>& t) -- deep copy
//			avl<T>& operator+=(const avl<T>& t) -- adds an element to the tree
//			void insert(T d, node<T>* &cur) -- adds an element to the tree
//			T popnode(node<T>* &cur) -- returns element in node deleted
//			T poplow(node<T>* &cur) -- returns element in leftmost node (deleted)
//			T popfirst(const T& d, node<T>* np)
//				-- returns element in first node matching d (deleted)
//		protected:
//			node<T>* rotateRight(node<T> *nodeN) -- balances tree	
//			node<T>* rotateLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateRightLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateLeftRight(node<T> *nodeN) -- balances tree
//			node<T>* rebalance(node<T> *&nodeN) -- balances tree
//			int getHeightDifference(const node<T> *const nodeN)const
//				-- returns the height difference between the left & right subtrees 
//
//
//   History Log: 
//     May 20, 2008, PB  completed version 1.0 
//------------------------------------------------------------------- 
	template<class T>
	class avl: public bst<T>
	{    
	public:
		avl() : bst(){}
		avl(const avl<T>& t) : bst(t){}
		avl<T>& operator=(const avl<T>& t);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d){insert(d); return *this;}
		avl<T> operator+(const T d)
		{avl<T> temp = *this; temp.insert(d); return temp;}
		bool insert(T d) { return insert(d, root);}
		bool insert(T d, node<T>* &cur);
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		~avl() {deltree();}
	protected:
		node<T>* rotateRight(node<T> *nodeN);	
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		int getHeightDifference(const node<T> *const nodeN)const;
	};
	//--------------------------------------------------------------------
	// overloaded =
	// throws bad_alloc
	// Returns reference to *this
	//--------------------------------------------------------------------
	template<class T>
	avl<T>& avl<T>::operator=(const avl<T>& t)
	{
	}
	//--------------------------------------------------------------------
	// overloaded +=
	// throws bad_alloc
	// Returns reference of *this
	//--------------------------------------------------------------------
	template<class T>
	avl<T>& avl<T>::operator+=(const avl<T>& t)
	{
	}
	//--------------------------------------------------------------------
	// Insert new node - triggers rebalance()
	// Returns true if insert successful.
	// Returns false if node already present in tree
	//--------------------------------------------------------------------
	template<class T>
	bool avl<T>::insert(T d, node<T>* &cur)
	{
		
	}
	//--------------------------------------------------------------------
	// Pops and returns target node.
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::popnode(node<T>* &cur)
	{
		
	}
	//--------------------------------------------------------------------
	// Pops and returns lowest node in tree
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::poplow(node<T>* &cur)
	{
		
	}
	//--------------------------------------------------------------------
	// Pops and returns first node that matches arg T& d
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::popfirst(const T& d, node<T>* np)
	{
		
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree right
	// Returns pointer to new tree root (was left child)
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{
		node<T> *nodeO = nodeN->left;
		nodeN->left = nodeO->right;
		nodeO->right = nodeN;
		nodeN->setHeight();
		nodeO->setHeight();
		return *nodeO;
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree left
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T> *nodeO = nodeN->right;
		nodeN->right = nodeO->left ;
		nodeO->left = nodeN;
		nodeN->setHeight();
		nodeO->setHeight();
		return *nodeO;		
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree Right, then Left
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
	{
		nodeN->right = rotateRight(nodeN);
		return rotateLeft(nodeN);
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree Left, then Right
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		nodeN->left = rotateLeft(nodeN);
		return rotateRight(nodeN);
	}//--------------------------------------------------------------------
	// Determines what sort of imbalance is present, then calls appropriate algorithm
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{
		nodeN->setHeight();	//Make sure height data is correct before proceding
		if (getHeightDifference(nodeN) == 2)	//Right imbalance block
		{
			if (getHeightDifference(nodeN->right) < 0)
				return rotateRightLeft(nodeN);	//Right-Left
			else
				return rotateRight(nodeN);		//Right
		}//end Right Imbalances
		else if (getHeightDifference(nodeN) == -2)	//Left imbalance
		{
			if (getHeightDifference(nodeN->left) > 0)
				return rotateLeftRight(nodeN);	//Left-Right
			else
				return rotateLeft(nodeN);		//Left
		}//end Left Imbalances
		else
			return nodeN;						//Balance not required
	}
	//--------------------------------------------------------------------
	// Determines if imbalance is present
	//--------------------------------------------------------------------
	template<class T>
	int avl<T>::getHeightDifference(const node<T> *const nodeN)const
	{
		return (nodeN->right->getHeight() - nodeN->left->getHeight());
	}
}
#endif
