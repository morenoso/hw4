#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int pathHeight(Node* currNode, int currHeight);

bool equalPaths(Node * root)
{
    // Add your code below
    //its either empty or is the leaf
    if(root == nullptr ) {
        return true;
    }
    //check if the heights of the paths are the same
    //or if there is only one leaf node
    if(pathHeight(root->left, 0) == pathHeight(root->right, 0) || (pathHeight(root->left,0) == 0 && pathHeight(root->right,0)==1)
        || (pathHeight(root->left, 0) == 1 && pathHeight(root->right,0) == 0)) {
        return true;
    }
    return false;

}

int pathHeight(Node* currNode, int currHeight) {
    if(currNode == nullptr) {
        return currHeight;
    }
    int lHeight = pathHeight(currNode->left, currHeight+1);
    int rHeight = pathHeight(currNode->right, currHeight +1);

    if(lHeight > rHeight) {
        return lHeight;
    }else {
        return rHeight;
    }
}
