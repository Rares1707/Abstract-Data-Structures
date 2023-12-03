#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    root = nullptr;
    relation = r;
    currentNumberOfElements = 0;
}
//Theta(1)

int SortedIndexedList::size() const {
    return currentNumberOfElements;
}
//Theta(1)

bool SortedIndexedList::isEmpty() const {
    return currentNumberOfElements == 0;
}
//Theta(1)

TComp SortedIndexedList::getElement(int i) const{
    if (i < 0 || i >= currentNumberOfElements)
    {
        throw exception();
    }
	PointerToNode currentNode = root;
    int currentPosition = 0;
    while (true)
    {
        if (currentNode->numberOfElementsToTheLeft + currentPosition == i)
        {
            return currentNode->element;
        }
        if (currentNode->numberOfElementsToTheLeft + currentPosition > i)
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentPosition += currentNode->numberOfElementsToTheLeft + 1;
            currentNode = currentNode->right;
        }
    }
}
//O(log height) which is O(n)

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= currentNumberOfElements)
    {
        throw exception();
    }
    PointerToNode currentNode = root;
    currentNumberOfElements--;
    PointerToNode parent = nullptr;
    bool lastTurnWasLeft = false;
    int currentPosition = 0;
    while (currentNode != nullptr)
    {
        if (currentNode->numberOfElementsToTheLeft + currentPosition == i)
        {
            int valueOfNode = currentNode->element;
            if (currentNode->right == nullptr && currentNode->left == nullptr) //the node has no descendants
            {
                if (currentNode == root)
                {
                    delete currentNode;
                    root = nullptr;
                    return valueOfNode;
                }

                if (lastTurnWasLeft && parent != nullptr)
                {
                    parent->left = nullptr;
                }
                else if (!lastTurnWasLeft && parent != nullptr)
                {
                    parent->right = nullptr;
                }
                delete currentNode;
            }
            else if (currentNode->right != nullptr && currentNode->left == nullptr) //the node has one descendant to the right
            {
                if (currentNode == root)
                {
                    PointerToNode oldRoot = root;
                    root = root->right;
                    delete oldRoot;
                    return valueOfNode;
                }

                if (lastTurnWasLeft)
                {
                    parent->left = currentNode->right;
                }
                else if (!lastTurnWasLeft)
                {
                    parent->right = currentNode->right;
                }
                delete currentNode;
            }
            else if (currentNode->right == nullptr && currentNode->left != nullptr) //the node has one descendant to the left
            {
                if (currentNode == root)
                {
                    PointerToNode oldRoot = root;
                    root = root->left;
                    delete oldRoot;
                    return valueOfNode;
                }

                if (lastTurnWasLeft)
                {
                    parent->left = currentNode->left;
                }
                else if (!lastTurnWasLeft)
                {
                    parent->right = currentNode->left;
                }
                delete currentNode;
            }
            else //the node has 2 descendants
            {
                //We will find the minimum of the right subtree, move the value to the
                //node to be deleted, and delete the found node (minimum)
                PointerToNode minimumNodeOfRightSubtree = currentNode->right;
                if (minimumNodeOfRightSubtree->left == nullptr)
                {
                    currentNode->element = minimumNodeOfRightSubtree->element;
                    currentNode->right = minimumNodeOfRightSubtree->right;
                    delete minimumNodeOfRightSubtree;
                }
                else
                {
                    PointerToNode parentOfMinimumNode = currentNode;
                    while (minimumNodeOfRightSubtree->left != nullptr)
                    {
                        parentOfMinimumNode = minimumNodeOfRightSubtree;
                        minimumNodeOfRightSubtree = minimumNodeOfRightSubtree->left;
                        parentOfMinimumNode->numberOfElementsToTheLeft--;
                    }
                    currentNode->element = minimumNodeOfRightSubtree->element;
                    parentOfMinimumNode->left = minimumNodeOfRightSubtree->right;
                    delete minimumNodeOfRightSubtree;
                }
            }
            return valueOfNode;
        }
        else if (currentNode->numberOfElementsToTheLeft + currentPosition > i)
        {
            parent = currentNode;
            lastTurnWasLeft = true;
            currentNode->numberOfElementsToTheLeft--;
            currentNode = currentNode->left;
        }
        else
        {
            parent = currentNode;
            lastTurnWasLeft = false;
            currentPosition += currentNode->numberOfElementsToTheLeft + 1;
            currentNode = currentNode->right;
        }
    }
}
//O(log height) which is O(n)

int SortedIndexedList::search(TComp e) const {
    PointerToNode currentNode = root;
    int currentPosition = 0;
    while (currentNode != nullptr)
    {
        if (currentNode->element == e)
        {
            //INORDER TRAVERSAL starting from the first (the highest) node which has the desired value
            //why? because we want to find the node which has the same value and is as low as possible in the tree

            std::stack<PointerToNode> auxiliaryStack;
            while (currentNode != nullptr)
            {
                auxiliaryStack.push(currentNode);
                currentNode = currentNode->left;
            }
            int positionInSubtree = -1;
            while (!auxiliaryStack.empty())
            {
                positionInSubtree++;
                currentNode = auxiliaryStack.top();
                auxiliaryStack.pop();
                if (currentNode->element == e)
                {
                    return currentPosition + positionInSubtree;
                }
                currentNode = currentNode->right;
                while (currentNode != nullptr)
                {
                    auxiliaryStack.push(currentNode);
                    currentNode = currentNode->left;
                }
            }
            cout << "YOU'VE GOT A BIG PROBLEM IF THIS IS PRINTED\n";
            cout << "What problem? the inorder search from above is not working properly, it is not finding an element which for sure exits\n";
        }
        else if (relation(e, currentNode->element))
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentPosition += currentNode->numberOfElementsToTheLeft + 1;
            currentNode = currentNode->right;
        }
    }
	return -1;
}
//O(n) because of the inorder traversal (the worst case is when we find the element in the root and to the right of the root's left child)


PointerToNode SortedIndexedList::insert(PointerToNode currentNode, TComp e)
{
    if (currentNode == nullptr)
    {
        currentNode = new BSTNode(e, nullptr, nullptr, 0);
    }
    else if (relation(e, currentNode->element))
    {
        currentNode->left = insert(currentNode->left, e);
        currentNode->numberOfElementsToTheLeft++;
    }
    else
    {
        currentNode->right = insert(currentNode->right, e);
    }
    return currentNode;
}

void SortedIndexedList::add(TComp e) {
    root = insert(root, e);
    currentNumberOfElements++;
}
//O(log height) which is O(n)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

void destroyNode(PointerToNode node)
{
    if (node == nullptr)
        return;
    if (node->right != nullptr)
        destroyNode(node->right);
    if (node->left != nullptr)
        destroyNode(node->left);
    delete node;
}
//Theta(n)


//destructor
SortedIndexedList::~SortedIndexedList() {
    destroyNode(root);
}

void SortedIndexedList::filter(Condition cond) {
    int steps = this->size();
    for (int i = 0; i < steps; i++)
    {
        if (!cond(getElement(i)))
        {
            remove(i);
            i--;
            steps--;
        }
    }
}
//O(log height) which is O(n) for getElement()
//O(log height) which is O(n) for remove()
//for filter: total complexity O(n * log(height) which is O(n^2)
