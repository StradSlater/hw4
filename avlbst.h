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
    AVLTree(const std::pair<const Key, Value>& keyValuePair) {
        this->root_ = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    }
    AVLTree();

    ~AVLTree();

    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO

    
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void simpleInsert(const std::pair<const Key, Value> &keyValuePair);
    void editBals(AVLNode<Key,Value>* ptr);
    AVLNode<Key, Value>* rotate(AVLNode<Key,Value>* ptr);
    AVLNode<Key, Value>* rightRotate(AVLNode<Key,Value>* ptr);
    AVLNode<Key, Value>* leftRotate(AVLNode<Key,Value>* ptr);
    static AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current);
    static AVLNode<Key, Value>* successor(AVLNode<Key, Value>* current);
};

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree()
{
  this->root_ = NULL;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree()
{
  ;
}


template<class Key, class Value>
void AVLTree<Key, Value>::simpleInsert(const std::pair<const Key, Value> &keyValuePair)
{
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
    if (curr == NULL){
      this->root_ = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
      static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0);
    }
    else{
      while ((curr != NULL) && (curr->getItem() != keyValuePair)){
            

          if (curr->getKey() == keyValuePair.first){
            curr->setValue(keyValuePair.second);
            curr = NULL;
          }
          else if (keyValuePair < curr->getItem()){
            if (curr->getLeft() == NULL){
              AVLNode<Key, Value>* insertion = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
              curr->setLeft(insertion);
              insertion->setBalance(0);
              curr = NULL; 
            }
            else{
              curr = curr->getLeft();
            }
          }
          else{
            if (curr->getRight() == NULL){
              AVLNode<Key, Value>* insertion = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
              curr->setRight(insertion);
              insertion->setBalance(0);
              curr = NULL; 
            }
            else{
              curr = curr->getRight();
            }
          }
      }
    }    
}

template<class Key, class Value>
void AVLTree<Key, Value>::editBals(AVLNode<Key,Value>* ptr)
{
  
  if (ptr == NULL){
    return;
  }
  
  else{
    AVLNode<Key,Value>* left = ptr->getLeft();
    AVLNode<Key,Value>* right = ptr->getRight();
    
    int leftHeight = this->findMaxDepth(left);
    int rightHeight = this->findMaxDepth(right);
    ptr->setBalance(leftHeight-rightHeight);
  

    editBals(left);
    editBals(right);
  }
  
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotate(AVLNode<Key,Value>* ptr)
{
    if (ptr == NULL){
      return NULL;
    }
  
    AVLNode<Key, Value>* newRoot = ptr;


    if (ptr->getBalance() > 1 && ptr->getLeft()->getBalance() >= 0)
    {
      newRoot = rightRotate(ptr);
    }

    else if (ptr->getBalance() > 1 && ptr->getLeft()->getBalance() < 0)
    {
      ptr->setLeft(leftRotate(ptr->getLeft()));
      newRoot = rightRotate(ptr);
    }

    else if (ptr->getBalance() < -1 && ptr->getRight()->getBalance() <= 0)
    {
      newRoot = leftRotate(ptr);
    }

    else if (ptr->getBalance() < -1 && ptr->getRight()->getBalance() > 0)
    {
      ptr->setRight(rightRotate(ptr->getRight()));
      newRoot = leftRotate(ptr);
    }

    editBals(newRoot);


    ptr->setRight(rotate(ptr->getRight()));
    ptr->setLeft(rotate(ptr->getLeft()));


    return newRoot;

}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rightRotate(AVLNode<Key,Value>* ptr)
{
  
  AVLNode<Key, Value> *a = ptr->getLeft();
  AVLNode<Key, Value> *temp = a->getRight();

  a->setRight(ptr);
  ptr->setLeft(temp);

  if (temp != NULL){
    temp->setParent(ptr);
  }

  a->setParent(ptr->getParent());
  if (ptr->getParent() != NULL) {
        if (ptr->getParent()->getLeft() == ptr) {
            ptr->getParent()->setLeft(a);
        } else {
            ptr->getParent()->setRight(a);
        }
    } 
  ptr->setParent(a);
  
  
  return a;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::leftRotate(AVLNode<Key,Value>* ptr)
{
  AVLNode<Key, Value> *a = ptr->getRight();
  AVLNode<Key, Value> *temp = a->getLeft();

  a->setLeft(ptr);
  ptr->setRight(temp);

  if (temp != NULL){
    temp->setParent(ptr);
  }

  a->setParent(ptr->getParent());
  if (ptr->getParent() != NULL) {
        if (ptr->getParent()->getLeft() == ptr) {
            ptr->getParent()->setLeft(a);
        } else {
            ptr->getParent()->setRight(a);
        }
    } 
  ptr->setParent(a);
  

  return a; 
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
      simpleInsert(new_item);
      editBals(static_cast<AVLNode<Key, Value>*>(this->root_));
      while (!(this->isBalanced())){
        this->root_ = rotate(static_cast<AVLNode<Key, Value>*>(this->root_));
        editBals(static_cast<AVLNode<Key, Value>*>(this->root_));
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
    AVLNode<Key, Value>* removed = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (removed == NULL){
      ;
    }
  
    else if ((removed->getLeft() == NULL) && (removed->getRight() == NULL)){
      AVLNode<Key, Value>* p = removed->getParent();
      if (p == NULL){
        delete removed;
        this->root_ = NULL;
      }
      else{
        if ((p->getLeft() != NULL) && (p->getLeft() == removed)){
          p->setLeft(NULL);
        }
        else if ((p->getRight() != NULL) && (p->getRight() == removed)){
          p->setRight(NULL);
        }
        delete removed;
      }
    }

    else if (removed->getLeft() == NULL){
      AVLNode<Key, Value>* p = removed->getParent();
      AVLNode<Key, Value>* rc = removed->getRight();
      

      if (p == NULL){
        delete removed;
        rc->setParent(NULL);
        this->root_ = rc;
      }
      
      else{
        
        rc->setParent(p);
        if ((p->getLeft() != NULL) && (p->getLeft() == removed)){
          p->setLeft(rc);
        }
        else if ((p->getRight() != NULL) && (p->getRight() == removed)){
          p->setRight(rc);
        }
        delete removed;

        
        }
        
      }
    

    else if (removed->getRight() == NULL){
      AVLNode<Key, Value>* p = removed->getParent();
      AVLNode<Key, Value>* lc = removed->getLeft();
      lc->setParent(p);
  
      if (p == NULL){
        delete removed;
        lc->setParent(NULL);
        this->root_ = lc;
      }

      else {
        lc->setParent(p);
        if ((p->getLeft() != NULL) && (p->getLeft() == removed)){
          p->setLeft(lc);
        }
        else if ((p->getRight() != NULL) && (p->getRight() == removed)){
          p->setRight(lc);
        }
        /*
        if (p->getParent() == NULL){
          this->root_ = successor(static_cast<AVLNode<Key, Value>*>(p));
          this->root_->setParent(NULL);
          AVLNode<Key, Value>* root_lc = static_cast<AVLNode<Key, Value>*>(this->root_)->getLeft();
          this->root_->setLeft(p);
          p->setParent(this->root_);
          p->setRight(root_lc);
        }
        */
        
        delete removed;
        
      }
    }

    else{
      AVLNode<Key, Value>* next = predecessor(removed);
      nodeSwap(removed, next);
      while (!((removed->getLeft() == NULL) && (removed->getRight() == NULL))){
        next = predecessor(removed);
        nodeSwap(removed, next);
      }
      AVLNode<Key, Value>* p = removed->getParent();
      if (p == NULL){
        delete removed;
        this->root_ = NULL;
      }

      else{
        if ((p->getLeft() != NULL) && (p->getLeft() == removed)){
          p->setLeft(NULL);
        }
        else if ((p->getRight() != NULL) && (p->getRight() == removed)){
          p->setRight(NULL);
        }
        delete removed;
      }
 
    }

    editBals(static_cast<AVLNode<Key, Value>*>(this->root_));
    
    while (!(this->isBalanced())){
      this->root_ = rotate(static_cast<AVLNode<Key, Value>*>(this->root_));
      editBals(static_cast<AVLNode<Key, Value>*>(this->root_));
    }
}

template<class Key, class Value>
AVLNode<Key, Value>*
AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
    // TODO
    if (current == NULL){
      return NULL;
    }

    if (current->getLeft() != NULL){
      AVLNode<Key, Value>* l = current->getLeft();

      if (l->getRight() == NULL){
        return l;
      }

      else{
        AVLNode<Key, Value>* curr = l->getRight();
        while (curr->getRight() != NULL){
          curr = curr->getRight();
        }
        return curr;
      }
    }

    if (current->getParent() == NULL){
      return NULL;
    }

    AVLNode<Key, Value>* parent = current->getParent();

    if (current->getLeft() == NULL && parent->getLeft() == current){
        AVLNode<Key, Value>* nextParent = parent->getParent();
        if (nextParent == NULL){
          return NULL;
        }
        while (nextParent->getRight() != parent){
          nextParent = nextParent->getParent();
        }
        return nextParent;
    }

    if (current->getLeft() == NULL){
      return current->getParent();
    }
}



template<class Key, class Value>
AVLNode<Key, Value>*
AVLTree<Key, Value>::successor(AVLNode<Key, Value>* current)
{
    // TODO
    if (current == NULL){
      return NULL;
    }

    if (current->getRight() != NULL){
      AVLNode<Key, Value>* r = current->getRight();

      if (r->getLeft() == NULL){
        return r;
      }

      else{
        AVLNode<Key, Value>* curr = r->getLeft();
        while (curr->getLeft() != NULL){
          curr = curr->getLeft();
        }
        return curr;
      }
    }

    if (current->getParent() == NULL){
      return NULL;
    }

    AVLNode<Key, Value>* parent = current->getParent();

    if (current->getRight() == NULL && parent->getRight() == current){
        AVLNode<Key, Value>* nextParent = parent->getParent();
        if (nextParent == NULL){
          return NULL;
        }
        while ((nextParent != NULL) && (nextParent->getLeft() != parent)){
          nextParent = nextParent->getParent();
        }
        return nextParent;
    }

    if (current->getRight() == NULL){
      return current->getParent();
    }

    return NULL;

}
    

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
