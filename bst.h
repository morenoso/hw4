#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    int isBalancedHelper(Node<Key,Value>* current) const;
    void clearHelper(Node<Key, Value> * curr);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //maybe check value/key instead of pointer idk
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //wip 
    current_ = successor(current_);

    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //check if internalFind comes out NULL or not, because if the key is found, we update the value and are done
    //for now i will write, but remember that i haven't implemented it yet
    if(root_==nullptr) {
        //for first insertion we set root to what we're insertin
        root_ = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }

    if(internalFind(keyValuePair.first)!= NULL) {
        internalFind(keyValuePair.first)->setValue(keyValuePair.second);
        return;
    }
    
    Node<Key,Value> *temp = root_;
    Node<Key,Value> * tempParent = nullptr;
    //nvm do this later when parent is known, params are key, value, parent;
    //Node<Key,Value> *temp = new Node();

    //bst searching while within the tree
    while(temp != nullptr) {
        //iterate left or right
        //if key of current node is less than the param, we shoudl go right
        if(temp->getKey() < keyValuePair.first) {
            tempParent = temp;
            temp = temp->getRight();
        }else{
            //don't have to worry about same key, bcs of case 1
            tempParent = temp;
            temp = temp->getLeft();
        }
        //if we reached a null node that means that 
        //we found were to insert our child
        //this is why we need to track the parent
    }
    Node<Key,Value> * insertion = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, tempParent);
    if(keyValuePair.first < tempParent->getKey()) {
        tempParent->setLeft(insertion);
    } else {
        tempParent ->setRight(insertion);
    }
    //in theory should work, but remember that there is 0 testing and i'm tired/sleepy
//i write messages to myself to remember im not done, because it just looks like text
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key,Value> *temp = internalFind(key);

    if(temp == nullptr){
        //key not found
        return;
    }

    if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
        if(temp == root_){
            root_ = nullptr;
        }else{
            //adjust linking status of parent
            if(temp->getParent()->getLeft() == temp){
                temp->getParent()->setLeft(nullptr);
            }else{
                temp->getParent()->setRight(nullptr);
            }
        }
        delete temp;
        
    }else if(temp->getLeft() == nullptr || temp->getRight() == nullptr) {
        //one child
        //nodeSwap();
        //newRoot = left_, or newRoot = right_
        //newRoot = temp->right_;

        //figure out if we have a left or right child
        //doesn't really matter which side it is, we just want to make sure we're getting the child and not nullptr
        Node<Key, Value> * child = nullptr;
        if(temp->getLeft()!= nullptr){
            child = temp->getLeft();
        }else{
            child = temp->getRight();
        }

        //make the child the root if we're getting rid of the root
        if(temp == root_) {
            root_ = child;
            root_->setParent(nullptr);
        }else{
                //temp is a left child
            if(temp->getParent()->getLeft() == temp){
                temp->getParent()->setLeft(child);
            }else{
                //temp is a right child
                temp->getParent()->setRight(child);
            }
            child->setParent(temp->getParent());

        }
       
        delete temp;

    }else{
        //we must also account for if predecessor has a left child
        //must reattach leftChild to predecessor's parent
        
   
        nodeSwap(temp, predecessor(temp));
        //predecessor(temp)->left_!= nullptr
        if(temp == root_) {
            root_ = predecessor(temp);
        }

        //btw this code may change if testing shows my understanding of nodeSwap implementation is wrogn
        if(temp->getParent()->getLeft() == temp){
            temp->getParent()->setLeft(temp->getLeft());
        }else{
            temp->getParent()->setRight(temp->getLeft());
        }

        if(temp->getLeft()!= nullptr){
            
            temp->getLeft()->setParent(temp->getParent());
            
        } 

        delete temp;
        
    }
  
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if(current == nullptr){
        return nullptr;
    }
    Node<Key, Value> *temp;
    Node<Key, Value> *rChild;
    if(current->getLeft() != nullptr) {
        temp = current->getLeft();
        while(temp->getRight() != nullptr) {
            temp = temp->getRight();
        }
        return temp;
    } else {
        temp = current->getParent();
        rChild = current;
        while(temp != nullptr && temp->getRight() != rChild){
            rChild = temp;
            temp = temp->getParent();
        }
        return temp;
    }
}

template <class Key, class Value>
Node<Key, Value>* 
BinarySearchTree<Key,Value>::successor(Node<Key, Value>* current) {
    //TODO
    //mapping it all out
    //if right child exists, go as far left as you can in right child subtree(this could be the child itself)
    //if it doesn't exist, walk up the tree until you find out you're a left child, the parent is the successor
    //(the first node can ALSO be the left child, so it could just be your parent)
    //if we reach the root without finding a successor, we're done

    //maybe a helper called successor search?
    //would return successor node
    if(current == nullptr){
        return nullptr;
    }
    Node<Key,Value> *temp;
    Node<Key, Value> *lChild;
    if(current->getRight() != nullptr){
        temp = current->getRight();
        while(temp->getLeft() != nullptr) {
            temp = temp->getLeft();
        }
        return temp;
    }else{
        temp = current->getParent();
        lChild = current;
        //nullchecking is for once we reach parent
        while(temp != nullptr && temp->getLeft() != lChild) {
            lChild = temp;
            temp = temp->getParent();
        }
        return temp;
    }
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //pseudocode
    //while loop for node that isn't null
    //remove getSmallest Node, or remove root acutally
    //done?
    clearHelper(root_);
    root_ = nullptr;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key,Value>* curr){
    if(curr == nullptr){
        return;
    }

    clearHelper(curr->getLeft());
    clearHelper(curr->getRight());
    delete curr;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //pseudocode
    //keep going left until you can't?
    if(root_ == nullptr){
        return nullptr;
    }
    Node<Key, Value> *temp = root_;
    while(temp->getLeft() != nullptr) {
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    //pseudocode
    //basic tree iteration
    //while somethign
    //if key < node.key go right, if > go right, if = return
    //if we reach end without returning sne dnull
    Node<Key, Value>  *temp = root_;
    while(temp != nullptr) {
        if(key < temp->getKey()) {
            temp = temp->getLeft();
        }else if(key > temp->getKey()){
            temp = temp->getRight();
        }else{
            return temp;
        }
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    //i think i implemented a function for this in lab, will just take it
    //nvm, work on the isBalancedHelper() func tommorow
    if( isBalancedHelper(root_)>=0){
        return true;
    }
    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::isBalancedHelper(Node<Key,Value>* current) const{
    //idea:
    //calculate height of left and right subtrees
    //work our way down before going up
    //starting from leaf nodes left to right check if balanced(obviously leaf is balanced)
    //once we find an imbalance, if there is any, return -1
    //otherwise, keep finding height
    //at each node, we are checking if we're balanced
    if(current == nullptr){
        return 0;
    }
    int leftHeight = isBalancedHelper(current->getLeft());
    int rightHeight = isBalancedHelper(current->getRight());
    if(std::abs(leftHeight-rightHeight) > 1 || leftHeight == -1 || rightHeight == -1){
        return -1;
    }
    return std::max(leftHeight, rightHeight) + 1;


}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
