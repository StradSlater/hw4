#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"


using namespace std;


int main(int argc, char *argv[])
{
  AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(2, 8));
	testTree.insert(std::make_pair(1, -50));
	testTree.insert(std::make_pair(3, 0));
	testTree.insert(std::make_pair(10, 0));
	testTree.insert(std::make_pair(15, 0));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "Before any removals, tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(-1);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({2, 1, 3, 10, 15})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	testTree.print();
///#endif

	testTree.remove(2);
	//EXPECT_EQ(10, testTree.root_->item_.first);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({1, 3, 10, 15})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 2 (the root), tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(10);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({1, 3, 15})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 10, tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(1);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({3, 15})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 1, tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(3);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({15})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 3, tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(15);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 15 (the last element), tree is: " << std::endl;
	testTree.print();
//#endif

	testTree.remove(15);
	//EXPECT_TRUE(verifyAVL(testTree, std::set<int>({})));

//#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 15 (which doesn't exist), tree is: " << std::endl;
	testTree.print();
//#endif

  std::cout << testTree.isBalanced() << std::endl;
  std::cout << testTree.isBalanced() << std::endl;
  testTree.print();



    /*
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    */

    return 0;
}
