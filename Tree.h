#pragma once
#include <iostream>

using namespace std;

template<class TKey, class TVal>
class BTreeNode
{
public:
	TKey key;
	TVal value;

	BTreeNode* left = nullptr;
	BTreeNode* right = nullptr;

	BTreeNode(TKey key, TVal val) :key(key), value(val) {}

	void print()
	{
		if (left != nullptr) left->print();
		cout << value;
		if (right != nullptr) right->print();
	}

	void printD(const TKey& key, const TKey& key1)
	{
		if (left != nullptr) left->printD(key, key1);

		if (this->key >= key1 && this->key <= key) 
			cout << value;

		if (right != nullptr) right->printD(key, key1);
	}

	void del()
	{
		if (left != nullptr) left->del();
		if (right != nullptr) right->del();
		delete this;
	}

	TVal* getInfo(const TKey& key)
	{
		if (key == this->key) return &value;
		if (key < this->key && left != nullptr) return left->getInfo(key);
		if (key > this->key && right != nullptr) return right->getInfo(key);
		return nullptr;
	}
};

template<class TKey, class TVal>
class BTree
{
public:
	static BTreeNode<TKey, TVal>* root;
	~BTree()
	{
		clear();
	}
	bool isEmpty()
	{
		return root;
	}

	void clear()
	{
		if (root)
			root->del();
		root = nullptr;
		cout << "Tree deleted" << endl;
	}

	void print()
	{
		if (root)
			root->print();
		else
			cout << "Tree empty";
		cout << endl;
	}

	void printD(TKey key, TKey key2)
	{
		if (root)
			root->printD(key, key2);
		else
			cout << "Tree empty";
		cout << endl;
	}

	TVal* get(const TKey& key)
	{
		if (root)
			return root->getInfo(key);
		return nullptr;
	}

	BTreeNode<TKey, TVal>* push_r(TKey key, TVal val, BTreeNode<TKey, TVal>*& node = root)
	{
		if (!node)
		{
			node = new BTreeNode<TKey, TVal>(key, val);
			return node;
		}
		if (key < node->key) node->left = push_r(key, val, node->left);
		else if (key > node->key) node->right = push_r(key, val, node->right);
		return node;
	}
};

template<class TKey, class TVal>
BTreeNode<TKey, TVal>* BTree<TKey, TVal>::root = nullptr;