//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jesse Draper
// Version     : 1.0
// Copyright   : Copyright � 2017 SNHU COCE
// Description : A Binary Search Tree to read from a file and store in structure for iteration.
//============================================================================

#include <iostream>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
//add file import here
// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;//> values
    Node* right;//< values

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
        Node() {
        this->bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    //private members
    Node* root;
    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void removeNode(string bidId);
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    Bid Search(string bidId);
    void postOrder();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::postOrder() {
    // FixMe (3): Post order root
    // postOrder root
    this->postOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        root = new Node(bid);

    }
    else {
        this->addNode(root, bid);
    }
    // if no root node create
  // else
    // add Node root and bid
}

/**
 * Remove a bid
 */
void BinarySearchTree::removeNode(string bidId) {
    // remove node root bidID
    if (root = nullptr) {
        return;
    }
    while (root) {
        if (root->bid.bidId.compare(bidId)) {
            removeNode(root, bidId);
            return;
        }
        else {
            if (root->right->bid.bidId > bidId) {
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
    }
}
// edge case check root, if next nodes id is larger move left else move right

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* currentNode = root;
    while (currentNode) {
        if (currentNode->bid.bidId.compare(root->bid.bidId)) {
            return currentNode->bid;
        }
        else if (currentNode->bid.bidId < bidId) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        // keep looping downwards until bottom reached or matching bidId found
            // if match found, return current bid

            // if bid is smaller than current node then traverse left
            // else larger so traverse right
    }
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) { 
    // if node is larger then add to left
    if (node->bid.bidId.compare(bid.bidId)) {
        if (node->left = nullptr) {
            node->left = new Node(bid);
        }
        else {
            if (node->right = nullptr) {
                node->right = new Node(bid);

            }
            else {
                addNode(node->right, bid);
            }
        }
    }
    // if no left node
        // this node becomes left
    // else recurse down the left node
// else
    // if no right node
        // this node becomes right
    //else
        // recurse down the left node
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        this->inOrder(root);
        cout << node->bid.bidId << " || " << node->bid.title << " || " << node->bid.amount << " ||" << node->bid.fund;
    }
    inOrder(right);
}
//if node is not equal to null ptr
//InOrder not left
//output bidID, title, amount, fund
//InOder right
}
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        postOrder(node);
    }
    postOrder(left);
    postOrder(right);
    //postOrder left
    //postOrder right
    //output bidID, title, amount, fund

}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        cout << node->bid.bidId << " || " << node->bid.title << " || " << node->bid.amount << " ||" << node->bid.fund;
    }
    preOrder(left);
    preOrder(right);
    //output bidID, title, amount, fund
    //postOrder left
    //postOrder right      
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
