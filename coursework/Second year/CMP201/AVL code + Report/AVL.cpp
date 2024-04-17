#include "AVL.h"
#include <algorithm>
#include <chrono> /* timing */
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h> /* srand, rand */
#include <string>
#include <time.h> /* time */


//preOrder [1]
void AVL::preOrder(AVL* r) { //root > left > right 
    if (r != NULL) {
        std::cout << r->data << " ";
        preOrder(r->left);
        preOrder(r->right);
    }
}

//inOrder[1]
void AVL::inOrder(AVL* r) { // left > root > right
    if (r != NULL) {
        inOrder(r->left);
        std::cout << r->data << " ";
        inOrder(r->right);
    }
};

// Max helper function 
int AVL::max(int a, int b) { // this is just a function version of the standard built in std::max
    return (a < b) ? b : a;
};

//getHeight
int AVL::getHeight(AVL* r) {
    if (!r) {
        return 0;
    }
    return r->height;
};

//getBalance
int AVL::getBalance(AVL* r) {
    if (!r) {
        return 0;
    }
    return getHeight(r->left) - getHeight(r->right);
};

//leftRotate [2]
AVL* AVL::leftRotate(AVL* r) { //just the inverse of rightrotate
    AVL* newRoot = r->right;
    if (r->right == NULL) {
        return 0;
    }
    AVL* subtreeToTransplant = newRoot->left;

    newRoot->left = r;
    r->right = subtreeToTransplant;

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
};

//rightRotate [2]
AVL* AVL::rightRotate(AVL* r) { // Given this in 8c, just need to add height calcs.
    AVL* newRoot = r->left;
    if (r->left == NULL) {
        return 0;
    }
    AVL* subtreeToTransplant = newRoot->right;

    newRoot->right = r;
    r->left = subtreeToTransplant;

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
};

//insertNode [4]
AVL* AVL::insertNode(AVL* r, int key) {

    if (!r) { // if there's nothing there, make a new node.
        r = new AVL(key);
        return r;
    }

    if (key < r->data) { // If new data is less than existing, new left node
        r->left = insertNode(r->left, key);
    }
    else if (key > r->data) { // if new data is more than existing, new right node
        r->right = insertNode(r->right, key);
    }
    else {
        return r; // in no other cases return r, ie key is already in tree
    }

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1; // get the height of the node so we can reference it later
    int balance = getBalance(r); // get the balance so we can change it if it's unbalanced

    if (balance > 1 && key < r->left->data) {
        return rightRotate(r);
    }
    if (balance < -1 && key > r->right->data) {
        return leftRotate(r);
    }
    if (balance > 1 && key > r->left->data) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    if (balance < -1 && key < r->right->data) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
};

//deleteNode [5]
AVL* AVL::deleteNode(AVL* r, int key) { //Given this in 8b

    //This logic is just copied from Insert 

    if (!r) {
        return r; // if not root return
    }
    if (key < r->data) { // if our value to delete is less than our data traverse
        // the left branch
        r->left = deleteNode(r->left, key);
    }
    else if (key > r->data) { // if our value to delete is more than our data
        // traverse the right branch
        r->right = deleteNode(r->right, key);
    }
    
    // Keep on traversing the stucture until we can no longer traverse, at which point begin considering cases 
    // Strongly advised to work recursively

    else { // "Do the actual work" 
        if (!r->left || !r->right ) { // In the case we're missing AT LEAST one child, so we can at MOST have one, and at least have none.
            AVL* successor = r->left ? r->left : r->right; //use a ternary operator. 

            if (!successor) { //Removal from leaf
                successor = r;
                r = NULL;
            }
            else { // Removal from node with single child
                r = successor;
            }
        }
        else { // Removal fromm node with two children
            // To quote the lectures
            // find successor node (smallest node that is bigger than the node we're removing) insert that value into space where node we're removing was
            // continue down
            AVL* successor = r->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            r->data = successor->data;
            r->right = deleteNode(r->right, successor->data); //works recursively.  

        }
    }

    if (!r) {
        return r;
    }

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
    int balance = getBalance(r);

    // Check the balance and balance accordingly if we have to
    if (balance > 1 && getBalance(r->left) >= 0) {
        return rightRotate(r); // left left
    }
    if (balance < -1 && getBalance(r->right) <= 0) {
        return leftRotate(r); // right right
    }
    if (balance > 1 && getBalance(r->left) < 0) {
        r->left = leftRotate(r->left); // left right
        return rightRotate(r);
    }
    if (balance < -1 && getBalance(r->right) > 0) {
        r->right = rightRotate(r->right); // right left
        return leftRotate(r);
    }

    return r;
};




int main() {
    
        //TEST INSERTION AND DELETION OPERATIONS & CONDITIONS, NOT PERFORMANCE. 
        AVL* TREE = NULL;
        AVL* manager = new AVL(0);
        TREE = manager->insertNode(TREE, 45); //TEST INSERTION INTO EMPTY AVL
        TREE = manager->insertNode(TREE, 34); //TEST INSERTION SUBSEQUENTLY
        TREE = manager->insertNode(TREE, 23); //TEST REBALANCING
        TREE = manager->insertNode(TREE, 76); 
        TREE = manager->insertNode(TREE, 2);
        TREE = manager->insertNode(TREE, 99); //TEST REBALANCING AGAIN 
        TREE = manager->deleteNode(TREE, 76); //TEST DELETION WITH TWO CHILDREN
        TREE = manager->insertNode(TREE, 12); // TEST REBALANCING WITH MULTIPLE ROTATIONS
        TREE = manager->insertNode(TREE, 18);
        TREE = manager->deleteNode(TREE, 23); //TEST DELETION WITH ONE CHILD
        TREE = manager->deleteNode(TREE, 18); //TEST DELETION OF LEAF
        TREE = manager->deleteNode(TREE, 34); //TEST DELETION FROM FIRST ROOT (2 children case)

        //We insert 45,34,23,76,2,99,12,18
        //We delete 76,23,18,34
        //Our values left should be (in order of insertion): 45,2,99,12
        //As such, inOrder should give 2 12 45 99
        //preOrder should give 45 12 2 99

        std::cout << "preOrder: "; 
        TREE->preOrder(TREE);
        std::cout << "\n" << std::endl;
        std::cout << "inOrder: ";
        TREE->inOrder(TREE);
        std::cout << "\n" << std::endl;

        //TEST #2 - SORTED AND UNSORTED PERFORMANCE TIMING

        srand(time(NULL));

        int randArr[10000];

        for (int i = 0; i < 10000; i++) {
            int random = rand();
            randArr[i] = random;
        }

        int sortedArray[10000];

        for (int i = 0; i < 10000; i++) {
            sortedArray[i] = i;
        }

        std::map<int, int> unsortedMap;
        std::map<int, int> sortedMap;

        for (int i = 10; i <= 10000; i += 10) {
            AVL* manager = new AVL(0);
            AVL* TREE = NULL;
            int j = 0;
            for (; j < i - 10; j++) {
                TREE = manager->insertNode(TREE, randArr[j]);
            }
            auto start = std::chrono::high_resolution_clock::now();
            for (; j < i; j++) {
                TREE = manager->insertNode(TREE, randArr[j]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            unsortedMap.insert({ i, timeDelta });
        }

        for (int i = 10; i <= 10000; i += 10) {
            AVL* manager = new AVL(0);
            AVL* TREE = NULL;
            int j = 0;
            for (; j < i - 10; j++) {
                TREE = manager->insertNode(TREE, sortedArray[j]);
            }
            auto start = std::chrono::high_resolution_clock::now();
            for (; j < i; j++) {
                TREE = manager->insertNode(TREE, sortedArray[j]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            sortedMap.insert({ i, timeDelta });
        }

        std::ofstream UnsortedData;
        UnsortedData.open("UnsortedData.csv");
        UnsortedData << "Input Size,Unsorted time taken (in nanoseconds) \n";
        for (auto const& pair : unsortedMap) {
            UnsortedData << pair.first << "," << pair.second << "\n";
        }
        UnsortedData.close();
        std::cout << "Unsorted Data Outputted" << std::endl;

        std::ofstream sortedData;
        sortedData.open("sortedData.csv");
        sortedData << "Input Size,Sorted time taken (in nanoseconds) \n";
        for (auto const& pair : sortedMap) {
            sortedData << pair.first << "," << pair.second << "\n";
        }
        sortedData.close();
        std::cout << "Sorted Data Outputted" << std::endl;

        return 0;

}  
