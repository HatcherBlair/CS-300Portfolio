// Name     : Project2CS-300.cpp
// Author   : Hatcher Blair
// Version  : 1.0
// Date     : 4/15/2023

#include <iostream>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

// Global definitions visible to all methods and classes

// Structure to hold all class information
struct Course {
    string courseNum;
    string courseName;
    vector<string> prerequisites;
    Course() {
        courseNum = "NAN";
        courseName = "N/A";
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    //Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //Initialize with a course
    Node(Course acourse) :
        Node() {
        course = acourse;
    }
};

// Binary search tree class definition

class BinarySearchTree {

private:
    Node* root;

    void printAll(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void DestroyRecursive(Node* node);
    void AddNode(Course course);
    void PrintAll();
    Course Search(string courseNum);
    
};

// Default constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    DestroyRecursive(root);
}

// Recursive destructor
void BinarySearchTree::DestroyRecursive(Node* node) {
    if (node) {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

// Traverse and print the tree in order
void BinarySearchTree::PrintAll() {
    printAll(root);
}

// Traverse and print the tree starting at given node
void BinarySearchTree::printAll(Node* node) {
    
    // Empty node, return
    if (node == NULL) {
        return;
    }

    printAll(node->left); // Travel left

    // Print out the current course
    cout << node->course.courseNum << ", " << node->course.courseName;
    for (auto const& c : node->course.prerequisites) {
        cout << ", " << c;
    }
    cout << endl;

    printAll(node->right); // Travel right
}

// Search for a course
Course BinarySearchTree::Search(string courseNum) {

    // Initialize cur and set it equal to root
    Node* cur = root;

    // Search for node
    while (cur != nullptr) {
        if (cur->course.courseNum == courseNum) { // Node found
            return cur->course;
        }
        else if (courseNum < cur->course.courseNum) { // Course num is smaller than current so go left
            cur = cur->left;
        }
        else { // Course num is larger than current so go right
            cur = cur->right;
        }
    }

    // Course not found return empty course
    Course course;
    return course;
}

// Add a node to the tree
void BinarySearchTree::AddNode(Course course) {

    // Declaring and initializing the new node
    Node* newNode;
    newNode = new Node(course);

    // If the root doesn't have an entry at is, the newNode is the root
    if (root == nullptr) {
        root = newNode;
    }
    else { // Else loop through the tree to find the insertion point
        Node* cur = root;
        while (cur != nullptr) {
            if (course.courseNum < cur->course.courseNum) { // If the new courseNum is less than the current courseNum, it goes on the left
                if (cur->left == nullptr) {
                    cur->left = newNode;
                    cur = nullptr;
                }
                else {
                    cur = cur->left;
                }

            }
            else { // Otherwise it goes on the right
                if (cur->right == nullptr) {
                    cur->right = newNode;
                    cur = nullptr;
                }
                else {
                    cur = cur->right;
                }
            }
        }
    }
}


// Load in the courses
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // Open the file
    ifstream file(csvPath);

    if (!file) {
        cout << "Error opening the file: " << csvPath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string value;
        while (getline(ss, value, ',')) {
            row.push_back(value);
        }
        Course course;
        course.courseNum = row.at(0);
        row.erase(row.begin());
        course.courseName = row.at(0);
        row.erase(row.begin());
        for (auto const& c : row) {
            course.prerequisites.push_back(c);
        }
        bst->AddNode(course);
    }

    file.close();
}
int main(int argc, char* argv[]) {
    
    // Process the command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv";
    }

    // Define variables to use in switch
    string courseNum = "N/A";

    // Define a timer variable
    clock_t ticks;

    // Define a binary tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "1. Load course data:" << endl;
        cout << "2. Print course list:" << endl;
        cout << "3. Print course:" << endl;
        cout << "9. Exit program:" << endl;
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading courses
            ticks = clock();

            // Complete the method call to load the courses
            loadCourses(csvPath, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->PrintAll();
            cout << endl;
            break;

        case 3:
            cout << "Please enter a course number: ";
            cin >> courseNum;
            cout << endl;

            course = bst->Search(courseNum);

            if (course.courseName == "N/A") {
                cout << "Course " << courseNum << " not found." << endl;
            }
            else {
                cout << course.courseNum << ", " << course.courseName;
                for (auto const& c : course.prerequisites) {
                    cout << ", " << c;
                }
                cout << endl << endl;
            }
            break;

        case 9:
            cout << "Good bye." << endl;
            break;

        default:
            cout << "Enter a valid input" << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

