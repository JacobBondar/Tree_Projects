/*
 * Ex #3: Find the subtree, even greater than odd.
 * ==========================================================
 *
 * This code implements a binary search tree where nodes store integers.
 *  It aims to find and print the node with the most even integers in 
 * its subtree. A recursive function counts even and odd numbers in each
 * subtree to identify the node with the highest count of even integers.
 * If no suitable node is found, it outputs "NOT FOUND".
 *
 * Input: User input sequence of integers as input to build a binary
 *  search tree.
 *
 * Output: The integer value stored in the node with the most even 
 *  integers in its subtree, or "NOT FOUND" if no such node exists.
 */

//-------------- include section --------------

#include <iostream>
#include <cstdlib>

//-------------- using section --------------

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

//-------------- structs section --------------

struct Node
{
    int _data;
    struct Node* _left, * _right;
};

//-------------- prototypes section --------------

struct Node* find_wanted_tree(struct Node* root);
void find_wanted_tree(struct Node* root, struct Node*& wanted, 
					int& size, int& greatest_tree, int& even, int& odd);
void print(struct Node* root);
struct Node* create_tree();
void insert_to_tree(struct Node*& root, int value);
void check_if_allocated(const void* const ptr);
void free_allocation(struct Node* root);

//-------------- main --------------

int main()
{
    struct Node* root = create_tree();
    struct Node* greatest_tree = find_wanted_tree(root);

    print(greatest_tree);

    free_allocation(root);

    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------

// Finds the node with the greatest number of even values in its 
//	subtree.
// Receives: A pointer to the root of the binary tree.
// Returns: A pointer to the node with the greatest number of even 
// 	values.
struct Node* find_wanted_tree(struct Node* root)
{
    struct Node* wanted = NULL;
    int greatest_tree = 0, size = 0;
    int even = 0, odd = 0;
    
    find_wanted_tree(root, wanted, size, greatest_tree, even, odd);
    
    return wanted;
}

//----------------------------------------------------------------------

// Recursive function to find the node with the greatest number of even 
//	values.
// Receives: A pointer to the current node, references to `wanted`,
//	`size`, `greatest_tree`, `even` and `odd`.
// Returns: Void (updates references and values through parameters).
void find_wanted_tree(struct Node* root, struct Node*& wanted, 
					 int& size, int& greatest_tree, int& even, int& odd)
{
    if (root == NULL) return;

    int left_counter = 0, right_counter = 0;
    int left_even = 0, left_odd = 0, right_even = 0, right_odd = 0;
    
    find_wanted_tree(root->_left, wanted, left_counter, greatest_tree, 
						left_even, left_odd);
    find_wanted_tree(root->_right, wanted, right_counter, greatest_tree,
						right_even, right_odd);
    
    if (root->_data % 2 == 0) even++;
    else odd++;
    
	size = left_counter + right_counter + 1;
    even += left_even + right_even;
    odd += left_odd + right_odd;

    if (even > odd)
    {
        if (size > greatest_tree)
        {
            greatest_tree = size;
            wanted = root;
        }
    } 
}

//----------------------------------------------------------------------

// Creates a binary search tree from input values read from `cin`.
// Receives: Nothing directly from parameters; reads input from `cin`.
// Returns: A pointer to the root node of the created binary tree.
struct Node* create_tree()
{
    struct Node* root = NULL;
    int value = 0;

    cin >> value;

    while (!cin.eof())
    {
        insert_to_tree(root, value);
        cin >> value;
    }
    return root;
}

//----------------------------------------------------------------------

// Prints the data of the root node or "NOT FOUND" if the root is NULL.
// Receives: A pointer to the root node.
// Returns: Void (prints the data to standard output).
void print(struct Node* root)
{
    if (root == NULL) cout << "NOT FOUND";
    else cout << root->_data << endl;
}

//----------------------------------------------------------------------

// Inserts a new node with a given value into the binary search tree
// Receives: A reference to the root of the binary search tree and an 
//	integer value to insert.
// Returns: Void (updates the binary search tree).
void insert_to_tree(struct Node* &root, int value)
{
    if (root == NULL)
    {
        root = new (std::nothrow) struct Node();
        check_if_allocated(root);

        root->_data = value;
    }

    else
    {
        if (value > root->_data) insert_to_tree(root->_right, value);
        else insert_to_tree(root->_left, value);
    }

}

//----------------------------------------------------------------------

// Checks if memory allocation was successful.
// Receives: A constant pointer to void which is checked for `NULL`.
// Returns: Void (prints an error message and exits if allocation
//	 fails).
void check_if_allocated(const void * const ptr)
{
    if (ptr == NULL)
    {
        cerr << "Can't allocate memory!" << endl;
        exit (EXIT_FAILURE);
    }
}

//----------------------------------------------------------------------

// Frees memory allocated for the entire binary search tree
// Receives: A pointer to the root of the binary search tree.
// Returns: Void (recursively deletes all nodes.
void free_allocation(struct Node* root)
{
    if (root != NULL)
    {
        free_allocation(root->_left);
        free_allocation(root->_right);
        delete root;
    }
}
