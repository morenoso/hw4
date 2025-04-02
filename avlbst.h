#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key,Value>* pivot);
    void rotateLeft(AVLNode<Key, Value>* pivot);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    void removeFix(AVLNode<Key, Value>* node, int diff);
    void insertHelp(const std::pair<const Key, Value> &new_item);
    
};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* pivot) {
    //pivot is the node that becomes its left child's right child
    if(pivot == BinarySearchTree<Key, Value>::root_) {
        BinarySearchTree<Key,Value>::root_ = pivot->getLeft();
    }
    AVLNode<Key,Value>* parent = pivot->getParent();
    AVLNode<Key, Value>* lChild = pivot->getLeft();
    AVLNode<Key, Value>* newLChild = lChild->getRight();

    if(parent != nullptr){
        //actually wait, this may be wrong
        //this only works if we want to do a right rotation, and the pivot is a right child
        //waht if we want to do a right rotation, and the pivot is a left child
        
        //keeping for memories, this is the fix here
        if(parent->getLeft()== pivot){
            parent->setLeft(lChild);
        }else{
            parent->setRight(lChild);
        }
    }
    lChild->setParent(parent);
    pivot->setParent(lChild);
    lChild->setRight(pivot);    
    pivot->setLeft(newLChild);
    if(newLChild != nullptr){
        newLChild->setParent(pivot);
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* pivot){
    //pivot is the node that becomes its right child's left child
    if(pivot == BinarySearchTree<Key,Value>::root_){
        BinarySearchTree<Key,Value>::root_ = pivot->getRight();
    }
    AVLNode<Key,Value> * parent = pivot->getParent();
    AVLNode<Key,Value>* rChild = pivot->getRight();
    AVLNode<Key,Value>* newRChild = rChild->getLeft();

    if(parent != nullptr){
        //this is the issue, since it may become parent's right child
        if(parent->getLeft()==pivot){
            parent->setLeft(rChild);
        }else{
            parent->setRight(rChild);
        }
    }
    rChild->setParent(parent);
    pivot->setParent(rChild);
    rChild->setLeft(pivot);
    pivot->setRight(newRChild);
    if(newRChild != nullptr){
        newRChild->setParent(pivot);
    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::insertHelp(const std::pair<const Key, Value> &new_item)
{
    if(BinarySearchTree<Key,Value>::root_==nullptr) {
        //for first insertion we set root to what we're insertin
        AVLNode<Key,Value>* avlRoot = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
        BinarySearchTree<Key,Value>::root_ = avlRoot;
        return;
    }

    if(BinarySearchTree<Key,Value>::internalFind(new_item.first)!= NULL) {
        BinarySearchTree<Key,Value>::internalFind(new_item.first)->setValue(new_item.second);
        return;
    }
    
    AVLNode<Key,Value> *temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::root_);
    AVLNode<Key,Value> * tempParent = nullptr;
    //nvm do this later when parent is known, params are key, value, parent;
    //Node<Key,Value> *temp = new Node();

    //bst searching while within the tree
    while(temp != nullptr) {
        //iterate left or right
        //if key of current node is less than the param, we shoudl go right
        if(temp->getKey() < new_item.first) {
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
    AVLNode<Key,Value> * insertion = new AVLNode<Key,Value>(new_item.first, new_item.second, tempParent);
    //std::cout << insertion->getBalance() << std::endl;
    //std::cout << static_cast<int>(insertion->getBalance()) << std::endl;
    if(new_item.first < tempParent->getKey()) {
        tempParent->setLeft(insertion);
    } else {
        tempParent ->setRight(insertion);
    }


}
/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //bst insert rewritten to accomodate avl nodes
    insertHelp(new_item);

    //static_cast may not be needed, but it works so i'm not getting rid of it
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(new_item.first));
    
    if(temp != BinarySearchTree<Key,Value>::root_){
        AVLNode<Key, Value>* tempParent = temp->getParent();
        if(tempParent->getBalance()==-1 ||tempParent->getBalance()==1){
            tempParent->setBalance(0);
        }else{
            if(tempParent->getLeft()== temp){
                tempParent->setBalance(-1);
            }else{
                tempParent->setBalance(1);
            }
            insertFix(tempParent,temp);
        }
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
    if(parent == nullptr || parent->getParent()== nullptr){
        return;
    }
    AVLNode<Key, Value>* grandparent = parent->getParent();

    if(grandparent->getLeft() == parent){
        grandparent->updateBalance(-1);
        if(grandparent->getBalance()==0){
            return;
        }else if(grandparent->getBalance()==-1){
            //going up the tree to find imbalance
            insertFix(grandparent,parent);
        }else if(grandparent->getBalance()==-2){
            if(parent->getBalance() == -1){
                //zig-zig
                rotateRight(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
                return;
            }else{
                //zig-zag(balance 0 shoudn't happen, this is for balance 1)
                rotateLeft(parent);
                rotateRight(grandparent);
                if(node->getBalance()==-1){
                    parent->setBalance(0);
                    grandparent->setBalance(1);
                    node->setBalance(0);
                }else if(node->getBalance()==0){
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    //node->setBalance(0);
                }else{
                    parent->setBalance(-1);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
                return;
            }
        }
      
        
    }else{
        grandparent->updateBalance(1);
        if(grandparent->getBalance()==0){
            return;
        }else if(grandparent->getBalance()==1){
            //going up the tree to find imbalance
            insertFix(grandparent,parent);
        }else if(grandparent->getBalance()==2){
            if(parent->getBalance() == 1){
                //zig-zig
                rotateLeft(grandparent);
                //test
                //this->print();
                parent->setBalance(0);
                grandparent->setBalance(0);
                return;
            }else{
                //zig-zag(balance 0 shoudn't happen, this is for balance 1)
                rotateRight(parent);
                //test
                //this->print();
                rotateLeft(grandparent);
                //this->print();
                if(node->getBalance()==1){
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                    node->setBalance(0);
                }else if(node->getBalance()==0){
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    //node->setBalance(0);
                }else{
                    parent->setBalance(1);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
                return;
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO

    //find node to remove by walking tree
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    //do nothing if it doesn't exist
    if(temp == nullptr){
        return;
    }

    //if n has 2 children, swap positions with predecessor 
    bool hasTwoChildren = false;
    AVLNode<Key, Value>* pred = nullptr;
    if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
        //if a node has two children, it has a predecessor

        pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::predecessor(temp));
        //keep track of root, since we won't use the regular remove
        
        //swap nodes with in order predecessor
        nodeSwap(temp, pred);

        if(BinarySearchTree<Key,Value>::root_ == temp){
            BinarySearchTree<Key,Value>::root_ = pred;
        }
        
        hasTwoChildren = true;
    }
    
    int diff;
    AVLNode<Key, Value>* tempParent = temp->getParent();
    if(tempParent != nullptr){
        if(tempParent->getLeft()== temp){
            diff = 1;
        }else{
            diff = -1;
        }
    }

    //implement this in the avlbst instead, since bst doesn't handle avlnodes
    if(hasTwoChildren){
        //must handle delete ourselves, since bst remove can't find the swapped node
        if(tempParent != nullptr && diff == 1){
            tempParent->setLeft(temp->getLeft());
        }
        if(tempParent != nullptr && diff == -1){
            tempParent->setRight(temp->getLeft());
        }
        if(temp->getLeft()!= nullptr){
            temp->getLeft()->setParent(tempParent);
        }
        delete temp;
    }else{
        BinarySearchTree<Key,Value>::remove(key);
    }
    removeFix(tempParent, diff);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff){
    if(node == nullptr){
        return;
    }
    //idk how to explain this, this is literally just the pseudocode from the slides
    //but written out in c++
    AVLNode<Key,Value>* parent = node->getParent();
    int nDiff = -1;
    if(parent != nullptr){
        if(parent->getLeft()== node){
            nDiff = 1;
        }
    }
    if(diff == -1){
        if(node->getBalance() + diff == -2){
            AVLNode<Key, Value>* child = node->getLeft();
            if(child->getBalance() == -1){
                rotateRight(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nDiff);
            }else if(child->getBalance() == 0){
                rotateRight(node);
                node->setBalance(-1);
                child->setBalance(1);
            }else{
                AVLNode<Key, Value>* grandchild = child->getRight();
                rotateLeft(child);
                rotateRight(node);
                if(grandchild->getBalance() == 1){
                    node->setBalance(0);
                    child->setBalance(-1);
                    grandchild->setBalance(0);
                }else if(grandchild->getBalance()== 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }else{
                    node->setBalance(1);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }
                removeFix(parent, nDiff);
            }
        }else if(node->getBalance()+ diff == -1){
            node->setBalance(-1);
        }else{
           // std::cout <<std::endl;
           node->setBalance(0);
           removeFix(parent,nDiff); 
        }

    }else{
        if(node->getBalance() + diff == 2){
            AVLNode<Key, Value>* child = node->getRight();
            if(child->getBalance() == 1){
                rotateLeft(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nDiff);
            }else if(child->getBalance() == 0){
                rotateLeft(node);
                node->setBalance(1);
                child->setBalance(-1);
            }else{
                AVLNode<Key, Value>* grandchild = child->getLeft();
                rotateRight(child);
                rotateLeft(node);
                if(grandchild->getBalance() == -1){
                    node->setBalance(0);
                    child->setBalance(1);
                    grandchild->setBalance(0);
                }else if(grandchild->getBalance()== 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }else{
                    node->setBalance(-1);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }
                removeFix(parent, nDiff);
            }
        }else if(node->getBalance()+ diff == 1){
            node->setBalance(1);
        }else{
           node->setBalance(0);
           removeFix(parent,nDiff); 
        }
    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
