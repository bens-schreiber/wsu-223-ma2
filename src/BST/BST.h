#pragma once

#include <iostream>
#include <limits>
#include <queue>
using namespace std;

/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node
{
public:
	T value;
	Node *left;
	Node *right;

	Node(T val)
	{
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST
{

protected:
	Node<T> *_root; // Root of the tree nodes

	// This algorithm works by using a depth first search.
	inline static bool _find(Node<T> *root, T value)
	{
		if (!root)
		{
			return false;
		}
		if (root->value == value)
		{
			return true;
		}
		if (root->value > value)
		{
			return _find(root->left, value);
		}
		return _find(root->right, value);
	}

	// This algorithm works by using a depth first search.
	// Everytime the root is not null, add 1 to the count.
	// Then recursively call the function on the left and right children.
	// Return the max of the left and right children, which will be the maximum path / depth.
	static unsigned int _findMaxDepth(Node<T> *root)
	{
		if (!root)
		{
			return 0;
		}
		return 1 + max(_findMaxDepth(root->left), _findMaxDepth(root->right));
	}

	/* Add new T val to the tree */
	inline void addHelper(Node<T> *root, T val)
	{
		if (root->value > val)
		{
			if (!root->left)
			{
				root->left = new Node<T>(val);
			}
			else
			{
				addHelper(root->left, val);
			}
		}
		else
		{
			if (!root->right)
			{
				root->right = new Node<T>(val);
			}
			else
			{
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	inline void printInOrderHelper(Node<T> *root)
	{
		if (!root)
			return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	inline int nodesCountHelper(Node<T> *root)
	{
		if (!root)
		{
			return 0;
		}
		else
		{
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	inline int heightHelper(Node<T> *root)
	{
		if (!root)
		{
			return -1;
		}
		else
		{
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	inline bool deleteValueHelper(Node<T> *parent, Node<T> *current, T value)
	{
		if (!current)
			return false;
		if (current->value == value)
		{
			if (current->left == nullptr || current->right == nullptr)
			{
				Node<T> *temp = current->left;
				if (current->right)
					temp = current->right;
				if (parent)
				{
					if (parent->left == current)
					{
						parent->left = temp;
					}
					else
					{
						parent->right = temp;
					}
				}
				else
				{
					this->_root = temp;
				}
			}
			else
			{
				Node<T> *validSubs = current->right;
				while (validSubs->left)
				{
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			   deleteValueHelper(current, current->right, value);
	}

	/********************************* PUBLIC API *****************************/
public:
	BST() : _root(nullptr) {} // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 */
	~BST()
	{
		deleteValueHelper(nullptr, this->_root, this->_root->value);
	}

	/* Public API */

	inline void add(T val)
	{
		if (this->_root)
		{
			this->addHelper(this->_root, val);
		}
		else
		{
			this->_root = new Node<T>(val);
		}
	}

	inline void print()
	{
		printInOrderHelper(this->_root);
	}

	inline int nodesCount()
	{
		return nodesCountHelper(this->_root);
	}

	inline int height()
	{
		return heightHelper(this->_root);
	}

	inline bool deleteValue(T value)
	{
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	// This algorithm works by using the std::queue.
	// We start by adding the root node to the queue.
	// Then we enter a while loop that runs until the queue is empty.
	// With each iteration, we pop the front of the queue, then append its left and right children to the queue.
	// We print the value of the node that we popped.
	// We continue this process until the queue is empty.
	void printLevelOrder()
	{
		std::queue<Node<T> *> q;
		q.push(this->_root);
		while (!q.empty())
		{
			Node<T> *temp = q.front();
			q.pop();
			if (temp)
			{
				cout << temp->value << " ";
				q.push(temp->left);
				q.push(temp->right);
			}
		}
	}

	void printMaxPath()
	{
		auto depth = _findMaxDepth(this->_root);
		std::cout << depth;
	}

	bool contains(T value)
	{
		return _find(this->_root, value);
	}
};