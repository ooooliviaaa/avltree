#ifndef RBBST_H
#define RBBST_H

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
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
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
    virtual void insertFix(AVLNode<Key,Value>* node1, AVLNode<Key,Value>* node2); //added by Huizhen TODO
    virtual void removeFix(AVLNode<Key, Value>* node, int change); //added by Huizhen TODO
    virtual void rightRotate(AVLNode<Key,Value>* node);//added by Huizhen TODO
    virtual void leftRotate(AVLNode<Key,Value>* node);//added by Huizhen TODO
    virtual bool isleftChild(AVLNode<Key,Value>* node);
    //zig zig and zig zag case 
    bool isZigzig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n); 
    bool isZigzag(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
};

//if it is the left child helper function 
template<class Key, class Value>
bool AVLTree<Key,Value>::isleftChild(AVLNode<Key,Value>* node){
  if(node->getParent()!=nullptr){
    return node == node->getParent()->getLeft();
  }
  else{
    return false;
  }
}

//helper function1 : right rotate 
template<class Key, class Value>
void AVLTree<Key,Value>::rightRotate(AVLNode<Key,Value>* x)
{
    //only need to delare three because those are the only three that will change in a rotation 
    AVLNode<Key,Value>* a = x->getLeft();
    AVLNode<Key,Value>* c = a->getRight();
    //when node is not the root
    if(x == this->root_){
      this->root_ = a;
      a->setParent(nullptr);
      x->setParent(a);
      a->setRight(x);
      x->setLeft(c);
      if(c!=nullptr){
        c->setParent(x);
      }
    }
    //when it is the root of the entire tree, just rotate 
    else{
      AVLNode<Key,Value>* p = x->getParent();
      //when the rotating node is the left sub tree of the parent 
      a->setParent(p);
      a->setRight(x);
      if(p->getRight()==x){
          p->setRight(a);
      }
      //if it is the right sub tree of the parent 
      else{
          p->setLeft(a);
      }
      x->setParent(a);
      if(c!=nullptr){
        c->setParent(x);
      }
      x->setLeft(c);
    }
}



//helper function:2 leftrotate 
template<class Key, class Value>
void AVLTree<Key,Value>::leftRotate(AVLNode<Key,Value>* x)
{
  //only need three node because those are the three that are actually changing 
  AVLNode<Key,Value>* y = x->getRight();
  AVLNode<Key,Value>* b = y->getLeft();
  //when the node, which is the one that needs to be rotated is not the root of the 
  if(x==this->root_){
    this->root_ = y;
    y->setParent(nullptr);
    x->setParent(y);
    y->setLeft(x);
    x->setRight(b);
    if(b!=nullptr){
      b->setParent(x);
    }
  }
  //when it is the root of the tree, then it is easier, simply just rotate 
  else{
    AVLNode<Key,Value>* p = x->getParent();
    //depends on the node x is a right subtree or a left one 
    //set parent for y as left or right child 
    y->setParent(p);
    y->setLeft(x);
    if(p->getRight()==x){
      p->setRight(y);
    }
    //when it is right side
    else{
      p->setLeft(y);
    }
    //when done putting y in the position, set x, and b in the right position 
    x->setParent(y);
    //check if b is a nullptr because sometimes b doesn't exist 
    if(b!=nullptr){
      x->setRight(b);
    }
  }
}
//zig zig case 
template<class Key, class Value>
bool AVLTree<Key, Value>::isZigzig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n){
    return this->isleftChild(p) == this->isleftChild(n);
}
//zig zag case
template<class Key, class Value>
bool AVLTree<Key, Value>::isZigzag(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n){
    return this->isleftChild(p) != this->isleftChild(n);
}

//helper function3: insert-fix 
template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
  //according to the pdf, if p = nullptr, simply return 
  if(this->empty()){
    return;
  }
  //set g as the parent of p 
  if(p==nullptr || p->getParent()==nullptr){
    return;
  }
  AVLNode<Key, Value>* g = static_cast<AVLNode<Key,Value>*>(p->getParent()); 
  //assume p is. left child of g 
  if(p == g->getLeft())
  {
    //update g's balance as -1 for now
    g->setBalance(g->getBalance() -1);
    //case 1: b(g) == 0, just return 
    if(g->getBalance()==0){
      return;
    }
    //case2: b(g) == -1, insertFix(g, p) // recurse
    else if(g->getBalance()==-1){
      insertFix(g, p);
    }
    //case 3: Case 3: b(g) == -2
    else if(g->getBalance() == -2){
      //If zig-zig then rotateRight(g); b(p) = b(g) = 0
      //subcase1: zig zig basically mean same direction rotation, basically either two left or two right 
      if(isZigzig(g,p,n)){
        rightRotate(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      //subcase2: If zig-zag then rotateLeft(p); rotateRight(g); 
      else{
        leftRotate(p);
        rightRotate(g);
        //enter special cases, three in total 
        //1. Case 3a: b(n) == -1 then b(p) = 0; b(g) = +1; b(n) = 0;
        if(n->getBalance()==-1){
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        //Case 3b: b(n) == 0 then b(p) = 0; b(g) = 0; b(n) = 0;
        else if(n->getBalance()==0){
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        //Case 3c: b(n) == +1 then b(p)= -1; b(g) = 0; b(n) = 0
        else if(n->getBalance()==1){
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }
  }
  //now big case2: if p is the right child
  else if(p == g->getRight())
  {
    //update g's balance as -1 for now
    g->setBalance(g->getBalance()+1);
    //case 1: b(g) == 0, just return 
    if(g->getBalance()==0){
      return;
    }
    //case2: b(g) == -1, insertFix(g, p) // recurse
    else if(g->getBalance()==1){
      insertFix(g, p);
    }
    //case 3: Case 3: b(g) == 2
    else if(g->getBalance()==2){
      //If zig-zig then rotateRight(g); b(p) = b(g) = 0
      //subcase1: zig zig basically mean same direction rotation, basically either two left or two right 
      if(isZigzig(g,p,n)){
        leftRotate(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      //subcase2: If zig-zag then rotateLeft(p); rotateRight(g); 
      else if(isZigzag(g,p,n)){
        rightRotate(p);
        leftRotate(g);
        //enter special cases, three in total 
        //1. Case 3a: b(n) == -1 then b(p) = 0; b(g) = +1; b(n) = 0;
        if(n->getBalance()==1){
          p->setBalance(0);
          g->setBalance(-1);
          n->setBalance(0);
        }
        //Case 3b: b(n) == 0 then b(p) = 0; b(g) = 0; b(n) = 0;
        else if(n->getBalance()==0){
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        //Case 3c: b(n) == +1 then b(p)= -1; b(g) = 0; b(n) = 0
        else if(n->getBalance()==-1){
          p->setBalance(1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }
  }
}


//helper function 4: REMOVEFIX
template<class Key, class Value>
void AVLTree<Key,Value>::removeFix (AVLNode<Key, Value>* n, int diff)
{
  if(n==nullptr){
    return;
  }
  int ndiff = -1;
  //p = parent(n) and if p is not NULL let ndiff (nextdiff) = +1 if n is a left child and -1 otherwise
  AVLNode<Key,Value>* p = n->getParent();
  if(p!=nullptr){
    if(p->getLeft()==n){
      ndiff = 1;
    }
    else{
      ndiff = -1;
    }
  }
  //assume diff = -1;
  if(diff == -1){
    //case 1: b(n) + diff = -2, perform the mirroring 
    if(n->getBalance()+diff == -2){
      //Let c = left(n), the taller of the children
      AVLNode<Key,Value>* c = n->getLeft();
      //case 1a: Case 1a: b(c) == -1 -> rotateRight(n), b(n) = b(c) = 0, removeFix(p, ndiff)
      if(c->getBalance()==-1){
        rightRotate(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      //case 1b: Case 1b: b(c) == 0 // zig-zig case -> rotateRight(n), b(n) = -1, b(c) = +1 // Done!
      else if(c->getBalance()==0){
        rightRotate(n);
        n->setBalance(-1);
        c->setBalance(1);
      }
      //case 1c: Case 1c: b(c) == +1
      //Let g = right(c) rotateLeft(c) then rotateRight(n)
      else if(c->getBalance()==1){
        AVLNode<Key,Value>*g = c->getRight();
        c->setRight(g);
        g->setParent(c);
        leftRotate(c);
        rightRotate(n);
        //If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
        if(g->getBalance()==1){
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if(g->getBalance()==0){
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if(g->getBalance()==-1){
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    //case 2: b(n)+diff = -1; then b(n) = -1, done!
    else if(n->getBalance()+diff == -1){
      n->setBalance(-1);
    }
    //case 3 : when it's 0 
    else if(n->getBalance()+diff == 0){
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
  //big case 2: when diff = 1 insetad of -1, change the sign and left->right ,vise versa 
  else if(diff == 1){
    if(n->getBalance()+diff == 2){
      //Let c = left(n), the taller of the children
      AVLNode<Key,Value>* c = n->getRight();
      //case 1a: Case 1a: b(c) == -1 -> rotateRight(n), b(n) = b(c) = 0, removeFix(p, ndiff)
      if(c->getBalance()==1){
        leftRotate(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      //case 1b: Case 1b: b(c) == 0 // zig-zig case -> rotateRight(n), b(n) = -1, b(c) = +1 // Done!
      else if(c->getBalance()==0){
        leftRotate(n);
        n->setBalance(1);
        c->setBalance(-1);
      }
      //case 1c: Case 1c: b(c) == +1
      //Let g = right(c) rotateLeft(c) then rotateRight(n)
      else if(c->getBalance()==-1){
        AVLNode<Key,Value>*g = c->getLeft();
        c->setLeft(g);
        g->setParent(c);
        rightRotate(c);
        leftRotate(n);
        //If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
        if(g->getBalance()==-1){
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if(g->getBalance()==0){
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if(g->getBalance()==-1){
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    //case 2: b(n)+diff = -1; then b(n) = -1, done!
    else if(n->getBalance()+diff == 1){
      n->setBalance(1);
    }
    //case 3 : when it's 0 
    else if(n->getBalance()+diff == 0){
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
// 
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //if it is an empty tree, when set the insert node as the root, b(n)=0, done!
    AVLNode<Key,Value> *newnode = new AVLNode<Key,Value>(new_item.first,new_item.second,nullptr);
    AVLNode<Key,Value> *current = static_cast<AVLNode<Key,Value>*>(this->root_);
    bool b = true;
    if(this->empty()){
      this->root_ = newnode;
      newnode->setBalance(0);
      return;
    }
    else{
    //walk the tree and check balance 
      while(b){
        if(current->getKey() > new_item.first){
        //case 1: if there is no left sub tree, then the newnode become the left child of the root node
        //and don't forget to set the parent of the new node as the root 
          if(current->getLeft()==nullptr){
            current->setLeft(newnode);
            newnode->setParent(current);
            b = false;
            newnode->setBalance(0);
            AVLNode<Key,Value>* p = newnode->getParent();
            if(p!=nullptr){
              if(p->getBalance()==-1 || p->getBalance()==1){
                p->setBalance(0);
              }
              else if(p->getBalance()==0){
                p->setBalance(-1);
                insertFix(p,newnode);
              }
            }
          }
          //let the root be the left child of the root, keep looping, keep comparing until there is no left node anymore
          else{
            current = current->getLeft();
          }
        }
        else if(current->getKey() < new_item.first){
          if(current->getRight()==nullptr){
            current->setRight(newnode);
            newnode->setParent(current);
            //when loop stop
            b = false;
            newnode->setBalance(0);
            AVLNode<Key,Value>* p = newnode->getParent();
            if(p!=nullptr){
              if(p->getBalance()==-1 || p->getBalance()==1){
                p->setBalance(0);
              }
              else if(p->getBalance()==0){
                p->setBalance(1);
                insertFix(p,newnode);
              }
            }
          } 
          else{
            current = current->getRight();
          }
        }
        if(current->getKey() == new_item.first){
          current->setValue(new_item.second);
          delete newnode;
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
void AVLTree<Key, Value>:: remove(const Key& key)
{
  //step 1: find node n, to remove by walking the tree, similar to bst 
  AVLNode<Key, Value>* n = static_cast<AVLNode<Key,Value>*>(this->find(key).current_);
  AVLNode<Key,Value>* p = n->getParent();
  int diff = 0;
  //bool b = true;
  if(n == nullptr){
    return;
  }
  //when n is not a nullptr
  else{
    diff = 0;
    if(this->isleftChild(n)){
      diff = 1;
    }
    else{
      diff = -1;
    }
  }
  //declare a successor for the future use: 
  //step 2:if n has two children, if so swap position with 
  //in order successor and perform the next step 
  //2 children case 
  if(n->getLeft()!=nullptr && n->getRight()!=nullptr){
    AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(n));
    nodeSwap(n,pred);
    //n->setParent(p);
    p = n->getParent();
    if(p!=nullptr){
      diff = 0;
      if(isleftChild(n)){
        diff = 1;
      }
      else{
        diff = -1;
      }
    }
    //if n has a left child 
    if(n->getLeft()!=nullptr){
      if(isleftChild(n)){
        p->setLeft(n->getLeft());
      }
      else{
        p->setRight(n->getLeft());
      }
      n->getLeft()->setParent(p);
      //delete n and update pointer 
      delete n;
      //call removefix to patch the tree 
      removeFix(p, diff);
      return;
    }
    //when n->getLeft is a nullptr, so no left child, this case we can just delete and call removefix 
    else{
      //same logic 
      if(isleftChild(n)){
        p->setLeft(nullptr);
        delete n;
        removeFix(p, diff);
        return;
      }
      else{
        p->setRight(nullptr);
        delete n; 
        removeFix(p, diff);
        return;
      }
    }
  }
  //if it has one left child 
  else if(n->getRight()==nullptr){
    p = n->getParent();
    if(n->getParent()!=nullptr){
      //check if it is left or right child and then change the child by promoting right child 
      if(isleftChild(n)){
        n->getParent()->setLeft(n->getLeft());
        diff = 1;
      }
      else{
        n->getParent()->setRighgt(n->getLeft());
        diff = -1;
      }
      //update parent 
      n->getLeft()->setParent(n->getParent());
      //delete node 
      delete n;
      //call removefix 
      removeFix(p,diff);
      return;
    }
    //if n is the root
    else{
      if(n->getParent()!=nullptr){
        n->getParent()->setLeft(n->getRight());
      }
      else{
        n->getParent()->setParent(n->getParent());
      }
      n->getRight()->setParent(n->getParent());
      delete n; 
      removeFix(p, diff);
      return;
    }
  }
  else if(n->getLeft()==nullptr){
    if(n->getParent()!=nullptr){
      n->getParent()->setLeft(nullptr);
      delete n;
      removeFix(p, diff);
    }
    else{
      n->getParent()->setRight(nullptr);
      delete n; 
      removeFix(p, diff);
    }
  }
  //case when it has no left child or right child 
  else{
    this->root_ = nullptr; 
    delete n; 
    return;
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
