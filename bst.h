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
    int Heightcount (Node<Key, Value>* root, bool& b) const; // added by Huizhen to count the Height
   // bool HeightBalanced (Node<Key, Value>* root) const; // added by HUizhen to check if it is balanced 
    void HelptoClear (Node<Key, Value>* current); // helper functioin for clear function 
    void removeHelp(Node<Key,Value>* current);
    bool isleftchild(Node<Key,Value>* curr);
    bool isrightchild(Node<Key,Value>* curr);
    int numofchild(Node<Key,Value>* curr);
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
    current_ = nullptr;
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
    return current_==rhs.current_;
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
    return current_!=rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //current_ == the one next to it, which is the successor 
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
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
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
    //if it is an empty tree, when set the insert node as the root, b(n)=0, done!
    Node<Key,Value> *now = root_;
    Node<Key,Value> *newnode = new Node<Key,Value>(keyValuePair.first,keyValuePair.second,nullptr);
    bool b = true;
    if(empty()){
      root_ = newnode; 
    }
    //enter a while loop first
    else{
      while(b){
      //check if b is bigger or smaller than the root, remember we are comparing key not the value 
      //now->getKey() = key of the root; KeyvaluePair.first = the key value of the newnode 
      //meaning that it needs to be added on the left side of the tree 
      //case 1: when the newnode is smaller than the rootnode 
        if(now->getKey() > keyValuePair.first){
        //case 1: if there is no left sub tree, then the newnode become the left child of the root node
        //and don't forget to set the parent of the new node as the root 
          if(now->getLeft()==nullptr){
            now->setLeft(newnode);
            newnode->setParent(now);
            b = false;
          }
          //let the root be the left child of the root, keep looping, keep comparing until there is no left node anymore
          else{
            now = now->getLeft();
          }
        }
        //case 2: the new node is bigger than the root 
        //check if it goes to the right side, same logic but different comparison 
        else if(now->getKey() < keyValuePair.first){
          //if there is no right sub tree, then we set the newnode as the right node and vise. versa 
          if(now->getRight()==nullptr){
            now->setRight(newnode);
            newnode->setParent(now);
            //when loop stop
            b = false;
          }
          else{
            now = now->getRight();
          }
        }
        //case 3: when this key already exist
        else{
          now->setValue(keyValuePair.second);
          delete newnode;
          b = false;
        }
     }
  }
}

template<class Key, class Value>
bool BinarySearchTree<Key,Value>::isleftchild(Node<Key,Value>* curr)
{
  if(curr->getParent()!=nullptr){
    return curr==curr->getParent()->getLeft();
  }
  else{
    return false;
  }
}

template<class Key, class Value>
bool BinarySearchTree<Key,Value>::isrightchild(Node<Key,Value>* curr)
{
  if(curr->getParent()!=nullptr){
    return curr==curr->getParent()->getLeft();
  }
  else{
    return false;
  }
}

template<class Key, class Value>
int BinarySearchTree<Key,Value>::numofchild(Node<Key,Value>* curr)
{
  if(curr==nullptr){
    return -100;
  }
  else if(curr->getLeft()==nullptr){
    return 1;
  }
  else if(curr->getRight()==nullptr){
    return 1;
  }
  else{
    return 2;
  }
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
/*
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
  bool b = true;
  Node<Key,Value> *now = root_;
  Node<Key,Value> *last = nullptr;
  if(now == nullptr){
    //i used to do return nullptr but this is void function so i need to
    //change all of them to return;
    return;
  }
  //1. step one: find the value of the actual key first, walking the tree 
  //condition: as long as we didn't find the matching value, which is such root != key 
  while(now->getKey()!=key&&now!=nullptr){
    //when the node to remove is smaller than the root, basically on the left sub tree 
    if(key<now->getKey()){
      if(now->getLeft() == nullptr){
        return;
      }
      last = now;
      now = now->getLeft();
    }
    //when the node n is on the right side of the tree
    else if(key>now->getKey()){
      if(now->getRight()==nullptr){
        return;
      }
      last = now;
      now = now->getRight();
    }
  }

  //step 2: now we walked the tree and found the node, what we gonna do is do the right proccesure 
  //case 1: according to ppt, the first scenario is when there is 2 children 
  if(now->getRight()!=nullptr && now->getLeft()!=nullptr){
    //swap with the predecessor 
    Node<Key,Value>* predofnow = predecessor(now);
    nodeSwap(now,predofnow);
    last = now->getParent();
  }
  if(now->getParent()!=nullptr && now!=nullptr && now->getParent()->getLeft()!= now){
    b = false;
  }
  else{
    b = true;
  }


  //case 2: when there is only right leaf 
  if(now->getLeft()==nullptr){
    //if it is the root
    if(now == root_){
      root_ = now->getRight();
      now->getRight()->parent_ = nullptr;
    }
    //if it is not the root
    else{
      Node<Key,Value>*therightchild = now->getRight();
      if(b){
        last->setLeft(therightchild);
      }
      else{
        last->setRight(therightchild);
      }
      therightchild->setParent(last);
    }
    delete now;
  }
  //case 2: when there is only the left leaf 
  else if(now->getRight()==nullptr){
    //if the it is the root then we simply set the left node as the new root and root has no parent
    if(now== root_){
      root_ = now->getLeft();
      root_->setParent(nullptr);
    }
    //in other case if it is a node in the tree, then we need to promote the child and then delete the node 
    else{
      Node<Key,Value>*theleftchild = now->getLeft();
      if(b){
        last->setLeft(theleftchild);
      }
      else{
        last->setRight(theleftchild);
      }
      theleftchild->setParent(last);
    }
    delete now;
  }

  //case 3: when it has no child, simply just delete and change pointers 
  else if((now->getLeft()==nullptr) && (now->getRight()==nullptr)){
    if(b==true){
      if(now==root_){
        root_ = nullptr;
      }
      else{
        last->setLeft(nullptr);
      }
      delete now;
    }
    else{
      if(now==root_){
        root_= nullptr;
      }
      else{
        last->setRight(nullptr);
      }
      delete now;
    }
  }
}*/

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::remove(const Key& key){
  if(empty()){
    return;
  }
  Node<Key,Value>* cur = find(key).current_;
  removeHelp(cur);
}

//remove rewrite 
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelp(Node<Key,Value>* current)
{
  //when there is no children for the removing node 
  if(numofchild(current)==0){
    if(current->getParent()!=nullptr){
      if(isleftchild(current)){
        current->getParent()->setLeft(nullptr);
      }
      else{
        current->getParent()->setRight(nullptr);
      }
    }
    else{
      root_ = nullptr;
    }
    delete current;
  }

  //when it has two children 
  else if(numofchild(current)==2){
    //find predecessor, and then swap
    Node<Key,Value>* pred = predecessor(current);
    nodeSwap(current,pred);
    //after that check the children again 
    //if it has no child
    if(numofchild(current)==0){
      if(current->getParent()!=nullptr){
        if(isleftchild(current)){
          current->getParent()->setLeft(nullptr);
        }
        else{
          current->getParent()->setRight(nullptr);
        }
      }
      else{
        root_ = nullptr;
      }
      delete current;
    }
    //when there is 1 child 
    else if(numofchild(current)==1){
      if(current->getLeft()!=nullptr){
        if(current->getParent()!=nullptr){
          if(isleftchild(current)){
            current->getParent()->setLeft(current->getLeft());
          }
          else{
            current->getParent()->setRight(current->getLeft());
          }
          current->getLeft()->setParent(current->getParent());
        }
        //if it is the root
        else{
          root_ = current->getLeft();
          current->getLeft()->setParent(nullptr);
        }
      }
      //when there is a right child
      else{
        if(current->getParent()!=nullptr){
          if(isleftchild(current)){
            current->getParent()->setLeft(current->getRight());
          }
          else{
            current->getParent()->setRight(current->getRight());
          }
          if(current->getRight()!=nullptr){
          current->getRight()->setParent(current->getParent());
          }
        }
        //if it is the root
        else{
          root_ = current->getRight();
          current->getRight()->setParent(nullptr);
        }
      }
      delete current;
    }
    //when there are two children 
    else if(numofchild(current)==2){
      if(current->getLeft()!=nullptr){
        if(current->getParent()!=nullptr){
          if(isleftchild(current)){
            current->getParent()->setLeft(current->getLeft());
          }
          else{
            current->getParent()->setRight(current->getLeft());
          }
          current->getLeft()->setParent(current->getParent());
        }
        else{
          root_ = current->getLeft();
          current->getLeft()->setParent(nullptr);
        }
      }
      //right child 
      else{
        if(current->getParent()!=nullptr){
          if(isleftchild(current)){
            current->getParent()->setLeft(current->getRight());
          }
          else{
            current->getParent()->setRight(current->getRight());
          }
          current->getRight()->setParent(current->getParent());
        }
        else{
          root_ = current->getRight();
          current->getRight()->setParent(nullptr);
        }
      }
      delete current;
    }
  }
}


//predecessor 
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    //when it is an empty tree
    if(current == nullptr){
      return nullptr;
    }
    //check if the left child exist, if so predecessor is the right most node of the left subtree
    if(current->getLeft()!=nullptr){
      current = current->getLeft();
      while(current->getRight()!=nullptr){
        current = current->getRight();
      }
      return current;
    }
    //if the left child doesn't exist Else walk up the ancestor is the predecessor
    else{
      //when it is not the right child of the parent, keep going up 
      while(current!=current->getParent()->getRight()){
      current = current->getParent();
      if(current==nullptr){
        return nullptr;
      }
      if(current->getParent()==nullptr){
        return nullptr;
      }
    }
    return current;
  }
}

//Helper function written by Huizhen to find the successor of any node 
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //if current = nullptr, meaning tree is empty, return nullptr
    if(current==nullptr){
        return nullptr;
    }
    //if right child exists, then the sucessor is the left most child of the right subtree 
    if(current->getRight()!=nullptr){
        current = current->getRight();
        while(current->getLeft()!=nullptr){
            current = current->getLeft();
        }
        return current;
    }
    else{
        //Else walk up the ancestor chain until you traverse the first left child pointer 
        //(find the first node who is a left child of his parent
        //case 1: the node is the root, has no successor 
        if(current->getParent()==nullptr){
            return nullptr;
        }

        //when the current node is not the left child of the parent 
        while(current->getParent()->getLeft()!=current){
          //first find the parent
          current = current->getParent();
          if(current == nullptr){
            return nullptr;
          }
          if(current->getParent()==nullptr){
            return nullptr;
          }
        }
        return current->getParent();
       /* while(current->getParent()!=nullptr){
          if(current->getParent()->getLeft()==current){
            b = true;
            break;
          }
          current = current->getParent();

        }*/
    }
}




/**
* Helper function for clear function 
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::HelptoClear (Node<Key, Value>* current)
{
  if(current == nullptr){
    //again this is a void function
    return;
  }
  HelptoClear(current->getLeft());
  HelptoClear(current->getRight());
  delete current;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
  HelptoClear(root_);
  //resetting to empty tree
  root_ = nullptr; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // if it is an empty tree, return a nullptr 
    if(empty()){
        return nullptr; 
    }
    //the smallest node of the avl tree is the left most node of all 
    Node<Key, Value>* now = root_;
    //if there is no left subtree then the root node itself is the smallest node
    while(now->getLeft() != nullptr){
        now = now->getLeft();
    }
    return now; 
}   

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists Returns a pointer to the node with the specified key. 
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
  Node<Key,Value>* now = root_;
  if(empty()){
      return nullptr; 
  }
  //check the key and the value, if the key is smaller than the key given, then 
  //loop through the tree and check each key and return the value of it 
  while(now != nullptr){
      if(now->getKey() > key){
          now = now->getLeft();
      }
      else if(now->getKey() < key){
          now = now->getRight();
      }
      else if(now->getKey() == key){
          return now; 
      } 
   }
   return nullptr;
}

/**
 * Helper function from Huizhen that help to calculate the height 
 */
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>:: Heightcount (Node<Key, Value>* root, bool& balanced) const
{
  if(root==nullptr){
    return 0;
  }
  if(!balanced){
    return -1;
  }
  int lleft = Heightcount(root->getLeft(),balanced);
  int lright = Heightcount(root->getRight(),balanced);
  if(abs(lleft - lright)>1){
    balanced = false;
  }
  int max_num = std::max(lleft,lright)+1;
  return max_num;
}

/**
 * Helper function from Huizhen that help to check if balanced 
 */
 /*
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>:: HeightBalanced (Node<Key, Value>* root) const
{
  if(root_ == nullptr){
    return true;
  }
  else{
    int dif = Heightcount(root->getRight()) - Heightcount(root->getLeft());
    if(dif <=1 && dif >= -1){
      return HeightBalanced(root->getRight()) && HeightBalanced(root->getLeft());
    }
  }
  return false; 
}*/


 
/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
  if(empty()){
    return true;
  }
  bool balance = true;
  Node<Key,Value>* current = root_;
  Heightcount(current, balance);
  if(!balance){
    return false;
  }
  else{
  return true;
  }
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
