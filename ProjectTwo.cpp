//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Louis Dimaano
// Description : ABCU Advising Assistance Program. Reads course data from a
//               CSV file into a binary search tree, then lets an advisor
//               print the course list in order or look up one course and
//               its prerequisites. A binary search tree was used since it
//               keeps courses in order automatically and searching is
//               reasonably fast.
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

//============================================================================
// Course data structure
//============================================================================

// Holds all the information for a single course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

//============================================================================
// Binary Search Tree to hold Course objects, ordered by courseNumber
//============================================================================

class CourseTree {

private:
    // node for the tree, holds one course plus pointers to its children
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node(Course aCourse) : Node() {
            course = aCourse;
        }
    };

    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyRecursive(Node* node);

public:
    CourseTree();
    ~CourseTree();
    void Insert(Course course);
    void PrintAll();
    Course Search(string courseNumber);
    bool IsEmpty();
};

CourseTree::CourseTree() {
    root = nullptr;
}

CourseTree::~CourseTree() {
    destroyRecursive(root);
}

// delete every node so the tree does not leak memory
void CourseTree::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

// true if no courses have been loaded yet
bool CourseTree::IsEmpty() {
    return root == nullptr;
}

void CourseTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}

// walk down the tree and add the new course in the right spot
void CourseTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}

void CourseTree::PrintAll() {
    this->inOrder(root);
}

// in-order (left, current, right) prints courses in sorted order
void CourseTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.name << endl;
        inOrder(node->right);
    }
}

// looks for a course by course number, returns an empty Course if not found
Course CourseTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }

        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // not found, return an empty course
    Course emptyCourse;
    return emptyCourse;
}

//============================================================================
// Helper functions
//============================================================================

// makes a string all uppercase so course number lookups aren't case
// sensitive (csci400 will still match CSCI400)
string toUpper(string text) {
    for (size_t i = 0; i < text.size(); ++i) {
        text[i] = toupper(text[i]);
    }
    return text;
}

// strips off trailing \r (from Windows line endings) and extra spaces
string trim(string text) {
    while (!text.empty() && (text.back() == '\r' || text.back() == '\n'
        || text.back() == ' ')) {
        text.pop_back();
    }
    size_t start = 0;
    while (start < text.size() && text[start] == ' ') {
        start++;
    }
    text = text.substr(start);

    // Windows "Copy as path" wraps the path in quotes, so strip those off
    // if they are there, otherwise the file will not be found
    if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
        text = text.substr(1, text.size() - 2);
    }

    return text;
}

// splits one line of the CSV file into tokens on the comma
vector<string> splitLine(string line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// reads the course file and loads each valid line into the tree.
// skips any line that doesn't have at least a course number and a title
void loadDataStructure(string fileName, CourseTree& courses) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Could not open file: " << fileName << endl;
        return;
    }

    int coursesLoaded = 0;
    string line;

    while (getline(file, line)) {
        line = trim(line);

        // skip any blank lines in the file
        if (line.empty()) {
            continue;
        }

        vector<string> tokens = splitLine(line);

        // every line needs at least a course number and a course name
        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Skipping malformed line: " << line << endl;
            continue;
        }

        Course course;
        course.courseNumber = toUpper(tokens[0]);
        course.name = tokens[1];

        // any remaining non-empty tokens are prerequisite course numbers
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(toUpper(tokens[i]));
            }
        }

        courses.Insert(course);
        coursesLoaded++;
    }

    file.close();
    cout << coursesLoaded << " courses loaded successfully." << endl;
}

// Prints the menu options
void printMenu() {
    cout << endl;
    cout << "   1. Load Data Structure." << endl;
    cout << "   2. Print Course List." << endl;
    cout << "   3. Print Course." << endl;
    cout << "   9. Exit" << endl;
    cout << endl;
    cout << "What would you like to do? ";
}

// reads a line of input and checks that it's a valid integer before
// converting it, so the program doesn't crash on bad input
bool getMenuChoice(int& choice) {
    string input;
    getline(cin, input);
    input = trim(input);

    // an empty line is not a valid choice
    if (input.empty()) {
        cout << input << " is not a valid option." << endl;
        return false;
    }

    // make sure every character is a digit before converting
    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i])) {
            cout << input << " is not a valid option." << endl;
            return false;
        }
    }

    choice = stoi(input);
    return true;
}

//============================================================================
// Main
//============================================================================

int main() {

    CourseTree courseTree;

    cout << "Welcome to the course planner." << endl;

    int choice = 0;

    while (choice != 9) {
        printMenu();

        if (!getMenuChoice(choice)) {
            continue;
        }

        switch (choice) {

        case 1: {
            cout << "Enter the file name that contains the course data: ";
            string fileName;
            getline(cin, fileName);
            fileName = trim(fileName);
            loadDataStructure(fileName, courseTree);
            break;
        }

        case 2: {
            if (courseTree.IsEmpty()) {
                cout << "Please load the data structure first (Option 1)."
                    << endl;
                break;
            }
            cout << "Here is a sample schedule:" << endl << endl;
            courseTree.PrintAll();
            break;
        }

        case 3: {
            if (courseTree.IsEmpty()) {
                cout << "Please load the data structure first (Option 1)."
                    << endl;
                break;
            }
            cout << "What course do you want to know about? ";
            string courseNumber;
            getline(cin, courseNumber);
            courseNumber = toUpper(trim(courseNumber));

            Course course = courseTree.Search(courseNumber);

            if (course.courseNumber.empty()) {
                cout << courseNumber << " was not found." << endl;
            }
            else {
                cout << course.courseNumber << ", " << course.name << endl;

                cout << "Prerequisites: ";
                if (course.prerequisites.empty()) {
                    cout << "None" << endl;
                }
                else {
                    cout << endl;
                    for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                        // look up each prerequisite so its title can be
                        // printed alongside its course number
                        Course prereq = courseTree.Search(
                            course.prerequisites[i]);

                        cout << "  " << course.prerequisites[i];
                        if (!prereq.courseNumber.empty()) {
                            cout << ", " << prereq.name;
                        }
                        cout << endl;
                    }
                }
            }
            break;
        }

        case 9:
            // exit handled by the while loop condition
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
