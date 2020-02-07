/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
template <class K, class V>
int AVLTree<K, V>::getHeight(Node* subRoot) const
{
    if (subRoot == NULL)
        return -1;

    if (subRoot->left == NULL && subRoot->right == NULL)
        return 0;

    return 1 + std::max(getHeight(subRoot->left), getHeight(subRoot->right));
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* subRoot)
{
    if (subRoot == NULL)
        return;

    subRoot->height = getHeight(subRoot);
}

template <class K, class V>
int AVLTree<K, V>::getBalance(Node* subRoot) const
{
    if (subRoot == NULL)
        return 0;

    return heightOrNeg1(subRoot->right) - heightOrNeg1(subRoot->left);
}

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name
    Node* temp = t;
    temp = temp->right->left;
    t->right->left = t;
    t = t->right;
    t->left->right = temp;
    updateHeight(t);
    updateHeight(t->left);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name
    Node* temp = t;
    temp = temp->left->right;
    t->left->right = t;
    t = t->left;
    t->right->left = temp;
    updateHeight(t);
    updateHeight(t->right);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == NULL)
        return;

    int fb = getBalance(subtree);
    if (fb >= -1 && fb <= 1)
        return;

    int sb;
    if (fb == 2) {
        sb = getBalance(subtree->right);
            if (sb == 1)
                rotateLeft(subtree);
            if (sb == -1)
                rotateRightLeft(subtree);
    }
    if (fb == -2) {
        sb = getBalance(subtree->left);
            if (sb == -1)
                rotateRight(subtree);
            if (sb == 1)
                rotateLeftRight(subtree);
    }
    // subtree->height = getHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // base case
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    // subtree not null from here
    if (key > subtree->key)
        insert(subtree->right, key, value);

    else if (key < subtree->key)
        insert(subtree->left, key, value);

    else { // if the key exist, update the value
        subtree->value = value;
        return;
    }

    updateHeight(subtree);
    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        // when key == subtree->key, execute removal
        // 0-child scenario
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = NULL;
        // 2-child
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node* iop = subtree->left;
            // if this node have right child, then update iop
            while (iop->right != NULL)
                iop = iop->right;
            swap(iop, subtree);
            remove(subtree->left, key); // swapping compromises the structure, does this work?
        } else {
            // 1-child scenario
            if (subtree->left != NULL) {
                Node* temp = subtree;
                subtree = subtree->left;
                delete temp;
            }else{
                Node* temp = subtree;
                subtree = subtree->right;
                delete temp;
            }
        }
    }
    updateHeight(subtree);
    rebalance(subtree);
}
