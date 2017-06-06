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
//			T popNode(node<T>* &cur) -- returns element in node deleted
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
		avl<T>& operator+(const T d)
		{avl<T> temp = *this; temp.insert(d); return temp;}
		bool insert(T d) { return insert(d, root);}
		bool insert(T d, node<T>* &cur);
		bool isempty() { return bst<T>::isempty(); }
		bool isempty() const { return bst<T>::isempty(); }
		T popNode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);				
		node<T>* getRoot() const { return bst<T>::root; }
		node<T>* getRoot() { return bst<T>::root; }
		void deltree() { bst<T>::delTree(); }
		~avl() {deltree();}
		
	protected:
		node<T>* rotateRight(node<T> *nodeN);	
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);		
		int getHeightDifference(const node<T> *const nodeN)const;		
		void addTree(const node<T>* np);
	};
	//--------------------------------------------------------------------
	// overloaded =
	// throws bad_alloc
	// Returns reference to *this
	//--------------------------------------------------------------------
	template<class T>
	avl<T>& avl<T>::operator=(const avl<T>& t)
	{			
		if(this != &t)
		{
			if (!isempty())
				deltree();
			if(!t.isempty())
			{
				bst<T>::root = new node<T>(*(t.getRoot()));
			}
		}
		return *this;
	}
	//--------------------------------------------------------------------
	// overloaded +=
	// throws bad_alloc
	// Returns reference of *this
	//--------------------------------------------------------------------
	template<class T>
	avl<T>& avl<T>::operator+=(const avl<T>& t)
	{			
		node<T>* temp = t.getRoot();
		addTree(temp);		
		return (*this);
	}
	//--------------------------------------------------------------------
	// recursively adds in the contents of a second tree
	//--------------------------------------------------------------------
	template <class T>
	void avl<T>::addTree(const node<T>* np)
	{
		if (np != nullptr)
		{
			addTree(np->left);
			addTree(np->right);
			insert(np->value());
		}
	}
	//--------------------------------------------------------------------
	// Insert new node - triggers rebalance()
	// Returns true if insert successful.
	// Returns false if node already present in tree
	//--------------------------------------------------------------------
	template<class T>
	bool avl<T>::insert(T d, node<T>* &cur)
	{
		if (bst<T>::insert(d, cur) == true)
		{
			rebalance(cur);
			if (bst<T>::root == nullptr)
				bst<T>::root = cur;
			bst<T>::root->setHeight();
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------
	// Pops and returns target node.
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::popNode(node<T>* &cur)
	{
		T contents = bst<T>::popNode(cur);
		if (cur != nullptr)
			rebalance(cur);
		bst<T>::root->setHeight();
		return contents;
	}
	//--------------------------------------------------------------------
	// Pops and returns lowest node in tree
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::poplow(node<T>* &cur)
	{	
		T contents = bst<T>::popLow(&cur);
		if (cur != nullptr)
			rebalance(cur);
		bst<T>::root->setHeight();
		return contents;
	}
	//--------------------------------------------------------------------
	// Pops and returns first node that matches arg T& d
	//--------------------------------------------------------------------
	template<class T>
	T avl<T>::popfirst(const T& d, node<T>* np)
	{
		T contents = bst<T>::popFirstOf(d, np);
		rebalance(bst<T>::parentptr);
		bst<T>::root->setHeight();
		return contents;
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree right
	// Returns pointer to new tree root (was left child)
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{		
		node<T> *child = nodeN->left;
		node<T> *orphan = nullptr;
		T value = nodeN->value();

		if (nodeN->left->right != nullptr)
			orphan = nodeN->left->right;
		
		nodeN->setdata(child->value());	//N has correct data and child
		if (child->left != nullptr)
			nodeN->left = child->left;
		else
			nodeN->left = nullptr;

		nodeN->right = child;
		child->setdata(value);	//N->r right now has correct data
		child->left = nullptr;	//Node already re-parented
		child->right = orphan;	//Orphan now re-parented.
				
		nodeN->setHeight();
		return nodeN;
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree left
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T> *child = nodeN->right;
		node<T> *orphan = nullptr;
		T value = nodeN->value();

		if (nodeN->right->left != nullptr)
			orphan = nodeN->right->left;

		nodeN->setdata(child->value());	//N has correct data and child
		if (child->right != nullptr)
			nodeN->right = child->right;
		else
			nodeN->right = nullptr;

		nodeN->left = child;
		child->setdata(value);	//N->r right now has correct data
		child->right = nullptr;	//Node already re-parented
		child->left = orphan;	//Orphan now re-parented.

		nodeN->setHeight();
		return nodeN;
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree Right, then Left
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
	{
		nodeN->right = rotateRight(nodeN->right);
		return rotateLeft(nodeN);
	}
	//--------------------------------------------------------------------
	// Rotates (sub)tree Left, then Right
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		nodeN->left = rotateLeft(nodeN->left);
		return rotateRight(nodeN);
	}
	//--------------------------------------------------------------------
	// Determines what sort of imbalance is present, then calls appropriate algorithm
	//--------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{		
		int diff = getHeightDifference(nodeN);	//Cache difference
		if (diff == 2)	//Right imbalance block
		{
			if (getHeightDifference(nodeN->right) < 0)
				return rotateRightLeft(nodeN);	//Left-Right				
			else
				return rotateLeft(nodeN);		//Right
		}//end Right Imbalances
		else if (diff == -2)	//Left imbalance
		{
			if (getHeightDifference(nodeN->left) > 0)
				return rotateLeftRight(nodeN);	//Right-Left
			else
				return rotateRight(nodeN);		//Left
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
		if (nodeN->right != nullptr)
			if (nodeN->left != nullptr)
				return (nodeN->right->getHeight() - nodeN->left->getHeight());
			else
				return (nodeN->right->getHeight());
		else if (nodeN->left != nullptr)
			return (-(nodeN->left->getHeight()));
		else
			return 0;
	}
}
#endif
