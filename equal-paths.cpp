#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int calculateHeight(Node* root){
    if(root == nullptr)
        return 0;
    int lDepth = calculateHeight(root->left);
    int rDepth = calculateHeight(root->right);
    if(lDepth > rDepth)
      return (lDepth + 1);
    else
      return (rDepth + 1);
}

bool equalPaths(Node * root)
{   
    if(root == nullptr){
      return true; 
    }
    int hleft = calculateHeight(root->left);
    int hright = calculateHeight(root->right);
    //if both left child and right child exist
    if(((root->right)!=nullptr) && ((root->left)!=nullptr)){
      //if max of the left and right side are the same, then check if it's equal paths
      if(hleft == hright){
        if(equalPaths(root->left)&&equalPaths(root->right)){
            return true;
        }
        else{
            return false;
        }
      }
      //if the max height of left and right child are not the same then it's def a false
      else{
        return false;
      }
    }
    //if it only has left child
    else if((root->right)== nullptr){
        if(equalPaths(root->left)){
            return true;
        }
        else{
            return false;
        }
    }

    //if it only has right child 
    else if((root->left) == nullptr){
        if(equalPaths(root->right)){
            return true;
        }
        else{
            return false;
        }
    }
}

