/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

// mirror recursive helper funtion
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    // base case
    if (subRoot == NULL)
        return;
    // recursive Definition
    // subRoot is not NULL
    Node* temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    if (root == NULL)
        return true;
    // what is traversal exactly?
    InorderTraversal<T> trav(root);
    typename InorderTraversal<T>::Iterator it = trav.begin();
    int prev = (*it)->elem;

    for (it = trav.begin(); it != trav.end(); ++it) {
        if ((*it)->elem < prev) {
            // the first time of the loop is =
            // false when bigger in front of smaller
            return false;
        }else{
            prev = (*it)->elem;
        }
    }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */

template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}

 //isOrdered() function recursive helper
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{
    // base case
    if (subRoot == NULL)
        return true;
    // recursive definition
    if (subRoot->elem < findMax(subRoot->left) && subRoot->left != NULL)
        return false;
    if (subRoot->elem > findMin(subRoot->right) && subRoot->right != NULL)
        return false;
    if (!isOrderedRecursive(subRoot->left) || !isOrderedRecursive(subRoot->right))
        return false;

    return true;
}

template <typename T>
int BinaryTree<T>::findMax(Node* subRoot) const
{
    // base case
    if (subRoot == NULL)
        return -1;
    // recursive definition

    int max = subRoot->elem;
    if (subRoot->left != NULL)
        max = std::max(max, findMax(subRoot->left));
    if (subRoot->right != NULL)
        max = std::max(max, findMax(subRoot->right));
    return max;
}

template <typename T>
int BinaryTree<T>::findMin(Node* subRoot) const
{
    // base case
    if (subRoot == NULL)
        return -1;
    // recursive definition
    int min = subRoot->elem;
    if (subRoot->left != NULL)
        min = std::min(min, findMin(subRoot->left));
    if (subRoot->right != NULL)
        min = std::min(min, findMin(subRoot->right));
    return min;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    T arr[500];
    int index = 0;
    path(root, paths, arr, index);
}

template <typename T>
void BinaryTree<T>::path(Node* subRoot, std::vector<std::vector<T>>& paths, T arr[], int index) const
{
    if (subRoot == NULL)
        return;

    arr[index] = subRoot->elem;
    ++index;

    if (subRoot->left == NULL && subRoot->right == NULL) {
        std::vector<T> temp;
        for(int i = 0; i < index; ++i) {
        temp.push_back(arr[i]);
        }
        paths.push_back(temp);
    }
    else {
        path(subRoot->left, paths, arr, index);
        path(subRoot->right, paths, arr, index);
    }
    --index;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    if(root == NULL)
        return -1;

    return sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* subRoot, int dist) const {
    if (subRoot->left == NULL && subRoot->right == NULL)
        return dist;

    int sum = 0;
    sum += dist;
    if(subRoot->left != NULL)
        sum += sumDistances(subRoot->left, dist + 1);

    if(subRoot->right != NULL)
        sum += sumDistances(subRoot->right, dist + 1);

    return sum;
}
