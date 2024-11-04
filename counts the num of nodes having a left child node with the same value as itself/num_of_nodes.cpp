/*
 * Number of Nodes that meet the condition.
 * ==========================================================
 *
 * This program implements a binary search tree structure (Node) to 
 * store integer values and counts nodes that satisfy a specific 
 * condition: having a left child node with the same value as itself. 
 *
 * Input: The input consists of integer values from the user.
 *
 * Output: The count of such nodes that meet the conditions within the
 *  tree.
 */

//-------------- include section --------------

#include <iostream>
#include <cstdlib>

//-------------- using section --------------

using std::endl;
using std::cout;
using std::cin;
using std::cerr;

//-------------- structs section --------------

struct Node {
    int _value;
    Node* _left, * _right;
};

//-------------- prototypes section --------------

void insert_value_in_root(struct Node*& root, int value);
struct Node* create_root();
void junction_counter(struct Node* root, int& counter);
void check_allocation(const void* const ptr);
void free_allocation(struct Node* &root);

//-------------- main --------------

int main()
{
    struct Node* root = create_root();

    int counter = 0;
    junction_counter(root, counter);

    cout << counter;

	free_allocation(root);

    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------

// Counts the number of junctions (nodes with a left child having the 
//	same value as itself
// Receives: A pointer to the root of the binary tree and a reference to
//	 an integer to store the count of junctions.
// Returns: Void, but updates `counter` via reference with the count of 
//	junctions.
void junction_counter(struct Node* root, int &counter)
{
    if(root != NULL)
    {
        if (root->_left != NULL)
        {
            if (root->_value == root->_left->_value)
                junction_counter(root->_left, ++counter);
            else junction_counter(root->_left, counter);
        }
        junction_counter(root->_right, counter);
    }
}

//----------------------------------------------------------------------

// Creates a binary search tree by reading values from standard input 
//	and inserts them into the tree
// Receives: Nothing directly from parameters, reads values from `cin`.
// Returns: A pointer to the root of the created binary search tree.
struct Node* create_root()
{
    struct Node* root = NULL;
    int value;

    cin >> value;
    while (!cin.eof())
    {
        insert_value_in_root(root, value);
        cin >> value;
    }
    return root;
}

//----------------------------------------------------------------------

// Inserts a new node with a given value into the tree.
// Receives: A reference to the root of the binary search tree and an
//	 integer value to insert.
// Returns: Void.
void insert_value_in_root(struct Node* &root, int value)
{
    if (root == NULL)
    {
        root = new (std::nothrow) struct Node();
        check_allocation(root);
        root->_value = value;
    }

    else if 
	   (value > root->_value) insert_value_in_root(root->_right, value);
    else insert_value_in_root(root->_left, value);
}

//----------------------------------------------------------------------

// Checks if memory allocation was successful.
// Receives: A constant pointer to void which is checked for `NULL`.
// Returns: Void, but prints an error message and exits if allocation
//	 fails.
void check_allocation(const void * const ptr)
{
    if(ptr == NULL)
    {
        cerr << "Can't allocate Memory \n";
        exit (EXIT_FAILURE);
    }
}

//----------------------------------------------------------------------

// Frees memory allocated for the entire binary search tree.
// Receives: A reference to the root of the binary search tree.
// Returns: Void.
void free_allocation(struct Node* &root)
{
    if (root != NULL)
    {
        free_allocation(root->_left);
        free_allocation(root->_right);
    }
    delete root;
}
