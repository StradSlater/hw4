#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool findDepth(Node* root, int depth, int &length){


    if (root == NULL){
        return true;
    }

    if (root->left == NULL && root->right == NULL){
        if (length == -1){
            length = depth;
        }
        return (length == depth);
    }

    else {
        bool left = findDepth(root->left, depth+1, length);
        bool right = findDepth(root->right, depth+1, length);

        return (left && right);
    }


}



bool equalPaths(Node * root)
{
    int length = -1;
    return findDepth(root, 0, length);
}

