#include "stdafx.h"

#include <iostream>

#include <assert.h>

class RBTree

{

private:

	struct treeNode

	{

		int data;

		bool red;

		treeNode * left;

		treeNode * right;

		treeNode * parent;

		treeNode() :left(NULL), right(NULL), parent(NULL), data(NULL), red(false)

		{

		}

	};

	treeNode * nil;

	treeNode * treeRoot = nil;

public:

	RBTree()

	{

		nil = new treeNode;

		nil->parent = nil->left = nil->right = NULL;

		nil->data = NULL;

		nil->red = false;

		treeRoot = new treeNode;

		treeRoot = nil;

	}



	treeNode * root(void) { return treeRoot; }



private:

	treeNode * treeInsert(int data)

	{

		treeNode * newLeaf = new treeNode;

		newLeaf->data = data;

		treeNode * insertIndex = treeRoot;

		treeNode * parentIndex = treeRoot;

		while (parentIndex != nil && data != parentIndex->data)

		{

			insertIndex = parentIndex;

			if (newLeaf->data < parentIndex->data)

			{

				parentIndex = parentIndex->left;

			}

			else

			{

				parentIndex = parentIndex->right;

			}

		}

		newLeaf->parent = insertIndex;

		if (insertIndex == nil)

		{

			treeRoot = newLeaf;

		}

		else if (newLeaf->data < insertIndex->data)

		{

			insertIndex->left = newLeaf;

		}

		else if (newLeaf->data == insertIndex->data)

		{

			delete newLeaf;

		}

		else

		{

			insertIndex->right = newLeaf;

		}

		newLeaf->right = newLeaf->left = nil;

		return newLeaf;



	}

public:

	treeNode * treeSearch(int data)

	{

		treeNode * node = treeRoot;

		while (node != nil && data != node->data)

		{

			if (data > node->data)

			{

				node = node->right;

			}

			else

			{

				node = node->left;

			}

		}

		return node;

	}

	int getBlackHeight(int data) //calling with 0 will search for nil node to get black height of tree?

	{

		treeNode * node = treeSearch(data);

		int blackHeight = 0;

		while (node->parent != nil)

		{

			if (!node->red)

			{

				blackHeight++;

			}

			node = node->parent;

		}

		return blackHeight;

	}

private:

	treeNode * treeMinimum(treeNode * index)

	{

		treeNode * root = index;

		while (root->left != nil)

		{

			root = root->left;

		}

		return root;

	}

	treeNode * treeMaximum(treeNode * index)

	{

		treeNode * root = index;

		while (root->right != nil)

		{

			root = root->right;

		}

		return root;

	}

	treeNode * treeSuccessor(int data)

	{

		treeNode * index = treeSearch(data);

		if (index->right != nil)

		{

			return treeMinimum(index->right);

		}

		else

		{

			treeNode * successor = index->parent;

			while (successor != nil && index == successor->right)

			{

				index = successor;

				successor = successor->parent;

			}

			return successor;

		}

	}

	void treeDelete(int data)

	{

		treeNode * index = treeSearch(data);

		treeNode * splice;

		treeNode * child;

		if (index != nil)

		{

			if (index->left == nil || index->right == nil)

			{

				splice = index;

			}

			else { splice = treeSuccessor(data); }

			if (splice->left != nil)

			{

				child = splice->left;

			}

			else { child = splice->right; }

			if (child != nil)

			{

				child->parent = splice->parent;

			}

			if (splice->parent == nil)

			{

				treeRoot = child;

			}

			else if (splice == splice->parent->left)

			{

				splice->parent->left = child;

			}

			else { splice->parent->right = child; }

			if (splice != index)

			{

				index->data = splice->data;

			}

			delete splice;

		}

	}

public:

	void assertTreeValid()

	{

		assertSubTreeValid(treeRoot);

	}

private:

	void assertSubTreeValid(treeNode * nodePtr)

	{



		assertNodeValid(nodePtr);

		if (nodePtr->right != nil)

		{

			assertSubTreeValid(nodePtr->right);

		}

		if (nodePtr->left != nil)

		{

			assertSubTreeValid(nodePtr->left);

		}

	}

	void assertNodeValid(treeNode * nodePtr)

	{

		while (nodePtr->parent != nil)

		{

			if (nodePtr->parent->left->data == nodePtr->data)

			{

				assert(nodePtr->data < nodePtr->parent->data);

			}

			else { assert(nodePtr->data > nodePtr->parent->data); }

			nodePtr = nodePtr->parent;

		}

	}

	void leftRotate(treeNode * pivot)

	{

		treeNode * rightOfPivot = pivot->right;

		pivot->right = rightOfPivot->left;

		if (rightOfPivot->left != nil)

		{

			rightOfPivot->left->parent = pivot;

		}

		rightOfPivot->parent = pivot->parent;

		if (pivot->parent == nil)

		{

			treeRoot = rightOfPivot;

		}

		else if (pivot == pivot->parent->left)

		{

			pivot->parent->left = rightOfPivot;

		}

		else { pivot->parent->right = rightOfPivot; }

		rightOfPivot->left = pivot;

		pivot->parent = rightOfPivot;

	}

	void rightRotate(treeNode * pivot)

	{

		treeNode * leftOfPivot = pivot->left;

		pivot->left = leftOfPivot->right;

		if (leftOfPivot->right != nil)

		{

			leftOfPivot->right->parent = pivot;

		}

		leftOfPivot->parent = pivot->parent;

		if (pivot->parent == nil)

		{

			treeRoot = leftOfPivot;

		}

		else if (pivot == pivot->parent->left)

		{

			pivot->parent->left = leftOfPivot;

		}

		else { pivot->parent->right = leftOfPivot; }

		leftOfPivot->right = pivot;

		pivot->parent = leftOfPivot;

	}

public:

	void RBInsert(int data)

	{

		treeNode * node = treeInsert(data);

		node->red = true;

		treeNode * uncle;

		while (node != treeRoot && node->parent->red == true)

		{

			if (node->parent == node->parent->parent->left)

			{

				uncle = node->parent->parent->right;

				//case 1

				if (uncle->red == true)

				{

					node->parent->red = false;

					uncle->red = false;

					node->parent->parent->red = true;

					node = node->parent->parent;

				}

				else

				{

					//case 2

					if (node == node->parent->right)

					{

						node = node->parent;

						leftRotate(node);

					}

					//case 3

					node->parent->red = false;

					node->parent->parent->red = true;

					rightRotate(node->parent->parent);

				}

			}

			else

			{

				uncle = node->parent->parent->left;

				if (uncle->red == true)

				{

					node->parent->red = false;

					uncle->red = false;

					node->parent->parent->red = true;

					node = node->parent->parent;

				}

				else

				{

					if (node == node->parent->left)

					{

						node = node->parent;

						rightRotate(node);

					}

					node->parent->red = false;

					node->parent->parent->red = true;

					leftRotate(node->parent->parent);

				}

			}

		}

		treeRoot->red = false;

	}

	void rbDeleteFixUp(treeNode * node)
	{
		treeNode * sibling;
		while (node != treeRoot && node->red == false)
		{
			if (node == node->parent->left)
			{
				sibling = node->parent->right;
				if (sibling->red == true)
				{
					sibling->red = false;
					node->parent->red = true;
					leftRotate(node->parent);
					sibling = node->parent->right;
				}
				if (sibling->right->red == false && sibling->left->red == false)
				{
					sibling->red = true;
					node = node->parent;
				}
				else
				{
					if (sibling->right->red == false)
					{
						sibling->left->red = false;
						sibling->red = true;
						rightRotate(sibling);
						sibling = node->parent->right;
					}			
					sibling->red = node->parent->red;
					node->parent->red = false;
					sibling->right->red = false;
					leftRotate(node->parent);
					node = treeRoot;					
				}
			}
			else
			{
				sibling = node->parent->left;
				if (sibling->red == true)
				{
					sibling->red = false;
					node->parent->red = true;
					rightRotate(node->parent);
					sibling = node->parent->left;
				}
				if (sibling->right->red == false && sibling->left->red == false)
				{
					sibling->red = true;
					node = node->parent;
				}
				else
				{
					if (sibling->left->red == false)
					{
						sibling->right->red = false;
						sibling->red = true;
						leftRotate(sibling);//
						sibling = node->parent->left;
					}

					prettyPrint(treeRoot);
					sibling->red = node->parent->red;
					node->parent->red = false;
					sibling->left->red = false;
					prettyPrint(treeRoot);
					rightRotate(node->parent);//
					prettyPrint(treeRoot);
					node = treeRoot;	
				}
			}
		}
		node->red = false;
	}

	void RBDelete(int data)

	{

		treeNode * node = treeSearch(data);

		if (node != nil)

		{

			treeNode * replace;

			treeNode * c;

			if (node->left == nil || node->right == nil)

			{

				replace = node;

			}

			else

			{

				replace = treeSuccessor(data);

			}

			if (replace->left != nil)

			{

				c = replace->left;//

			}

			else

			{

				c = replace->right;//

			}

			c->parent = replace->parent;

			if (replace->parent == nil)

			{

				c = treeRoot;

			}

			else if (replace == replace->parent->left)

				{

					replace->parent->left = c;//

				}

				else

				{

					replace->parent->right = c;//

				}

			if (replace != node)

			{

				node->data = replace->data;

			}



			std::cout << "Deleting " << data << " - before fixup" << std::endl;

			prettyPrint(root());

			std::cout << std::endl << std::endl;



			if (replace->red == false)

			{

				rbDeleteFixUp(c);

			}

			delete replace;

		}

	}



	void prettyPrint(treeNode * node, int depth = 0)

	{

		if (node == nil) return;

		if (node->right != nil) prettyPrint(node->right, depth + 1);

		for (int i = 0; i < depth; ++i) std::cout << "       ";

		std::cout << node->data << ((node->red) ? "(R)" : "(B)") << std::endl;

		if (node->left != nil) prettyPrint(node->left, depth + 1);

	}

};

int main()

{

	RBTree treeOne;
	for (int data = 1; data <= 15; data++)
	{
		treeOne.RBInsert(data);
		treeOne.getBlackHeight(data);
		treeOne.assertTreeValid();
		std::cout << "Inserted " << data << std::endl;
		treeOne.prettyPrint(treeOne.root());
		std::cout << std::endl << std::endl;
	}

	assert(treeOne.treeSearch(4)->data == 4);
	treeOne.RBDelete(12);
	std::cout << "Deleted 12" << std::endl;
	treeOne.prettyPrint(treeOne.root());
	std::cout << std::endl << std::endl;

	treeOne.assertTreeValid();
	treeOne.RBDelete(4);
	std::cout << "Deleted 4" << std::endl;
	treeOne.prettyPrint(treeOne.root());
	std::cout << std::endl << std::endl;

	treeOne.assertTreeValid();
	treeOne.RBDelete(8);
	std::cout << "Deleted 8" << std::endl;
	treeOne.prettyPrint(treeOne.root());
	std::cout << std::endl << std::endl;

	treeOne.assertTreeValid();
	treeOne.RBDelete(2);
	treeOne.assertTreeValid();

	assert(treeOne.treeSearch(12)->data == 0);
	treeOne.RBDelete(12);
	return 0;
}