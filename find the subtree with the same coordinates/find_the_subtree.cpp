/*
 * Find the subtree with the same coordinates.
 * ==========================================================
 *
 * This program utilizes a binary search tree structure (Node) to store
 *  integer IDs and corresponding coordinates (Point). It aims to find 
 * and print the node whose subtree best meets specified geometric 
 * criteria based on its coordinates' quadrant placement.
 *
 * Input: User input consists of integer IDs followed by their
 *  coordinates.
 *
 * Output: The coordinates of the node with the largest subtree 
 * satisfying the quadrant conditions, or "00" if no such node is found.
 * 
 * RunTime: o(n^2) when "n" represents the amount of nodes we have in
 *  the tree. We are talking about the overall run time of the code,
 *  so to build the tree, in the worst time (when the tree is skewed),
 *  we will have to run 1 + 2 + ... + n times, which is n^2.
 */

//-------------- include section --------------

#include <iostream>
#include <cstdlib>

//-------------- using section --------------

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

//-------------- enum section --------------

enum quarter_t { DEFAULT_QUAR, FIRST_QUAR, SECOND_QUAR, THIRD_QUAR, 
					FOURTH_QUAR };

//-------------- structs section --------------

struct Point {
    int _x;
    int _y;
};

struct Node {
    int _id;
    struct Point* _data;
    struct Node* _left, * _right;
};

//-------------- prototypes section --------------

struct Node* find_biggest_tree_quarter(struct Node* const root);
bool find_biggest_tree_quarter(struct Node* root, int& greatest_tree, 
					   struct Node*& wanted, int& size, quarter_t& pos);
quarter_t find_pos(const struct Node* const root);
struct Node* create_tree();
bool valid_tree(quarter_t left_pos, quarter_t right_pos, 
				quarter_t curr_pos);
void print_node(struct Node* new_root);
void input_tree(struct Node*& root, int id);
void check_if_allocated(const void* const ptr);
void free_allocation(struct Node* root);

//-------------- main --------------

int main()
{
    struct Node* root = create_tree();

    struct Node* new_root = find_biggest_tree_quarter(root);

	print_node(new_root);

    free_allocation(root);

    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------

// Finds the node with the largest subtree that meets the specified 
//	quarter criteria.
// Receives: A constant pointer to the root of the binary tree.
// Returns: A pointer to the node with the largest subtree that meets 
//	the criteria.
struct Node* find_biggest_tree_quarter(struct Node* const root)
{
    int greatest_tree = 0, size = 0;;
    struct Node* wanted = NULL;
    quarter_t pos = DEFAULT_QUAR;

    find_biggest_tree_quarter(root, greatest_tree, wanted, size, pos);

    return wanted;
}

//----------------------------------------------------------------------

// Recursively finds the largest subtree that meets the quarter 
//	criteria.
// Receives: A pointer to the current node, references to 
//	`greatest_tree`, `wanted`, `size`, and `curr_pos`.
// Returns: Boolean indicating if the subtree rooted at `root` is valid 
//	and contributes to `greatest_tree`.
bool find_biggest_tree_quarter(struct Node* root, int& greatest_tree, 
				   struct Node*& wanted, int& size, quarter_t& curr_pos)
{
    int left_counter = 0, right_counter = 0;
    quarter_t left_pos = DEFAULT_QUAR, right_pos = DEFAULT_QUAR;

    if (root == NULL) return true;
    
    bool left = find_biggest_tree_quarter(root->_left, greatest_tree, 
										wanted, left_counter, left_pos);
    bool right = find_biggest_tree_quarter(root->_right, greatest_tree,
									  wanted, right_counter, right_pos);

    size = left_counter + right_counter + 1;

    curr_pos = find_pos(root);
    
    if (valid_tree(left_pos, right_pos, curr_pos) && left && right)
    {
        if (size > greatest_tree)
        {
            wanted = root;
            greatest_tree = size;
        }

        return true;
    }
    
    size = 0;
    return false;
}

//----------------------------------------------------------------------

// Checks if a subtree with the given left, right, and current quarter
//	 positions is valid
// Receives: Quarter positions `left_pos`, `right_pos`, and `curr_pos`.
// Returns: Boolean indicating if the subtree is valid.
bool valid_tree(quarter_t left_pos, quarter_t right_pos, 
				quarter_t curr_pos)
{
    if ((left_pos == DEFAULT_QUAR && right_pos == DEFAULT_QUAR)
        || (left_pos == DEFAULT_QUAR && curr_pos == right_pos)
        || (right_pos == DEFAULT_QUAR && curr_pos == left_pos)
        || (curr_pos == left_pos && curr_pos == right_pos))
        return true;
    return false;
}

//----------------------------------------------------------------------

// Determines the quarter position (FIRST_QUAR, SECOND_QUAR, THIRD_QUAR,
//	 FOURTH_QUAR) of a node based on its coordinates
// Receives: A constant pointer to the node root.
// Returns: Quarter position based on the coordinates of `root->_data`.
quarter_t find_pos(const struct Node* const root)
{
    if (root->_data->_x > 0 && root->_data->_y > 0) return FIRST_QUAR;
    if (root->_data->_x < 0 && root->_data->_y > 0) return SECOND_QUAR;
    if (root->_data->_x < 0 && root->_data->_y < 0) return THIRD_QUAR;
    return FOURTH_QUAR;
}

//----------------------------------------------------------------------

// Creates a binary search tree from input IDs and coordinates
// Receives: Nothing directly from parameters; reads input from `cin`.
// Returns: A pointer to the root of the created binary search tree.
struct Node* create_tree()
{
    struct Node* root = NULL;
    int id = 0;

    cin >> id;

    while (!cin.eof())
    {
        input_tree(root, id);
        cin >> id;
    }
    return root;
}

//----------------------------------------------------------------------

// Inserts a node into the binary search tree based on its ID and 
//	coordinates.
// Receives: A reference to the root of the binary search tree and an ID
//	to insert.
// Returns: Void.
void input_tree(struct Node*& root, int id)
{
    if (root == NULL)
    {
        int x, y;
        cin >> x >> y;

        root = new (std::nothrow) struct Node();
        check_if_allocated(root);

        root->_id = id;

        root->_data = new (std::nothrow) struct Point();
        check_if_allocated(root->_data);

        root->_data->_x = x;
        root->_data->_y = y;

    }
    else if (id > root->_id) input_tree(root->_right, id);
    else input_tree(root->_left, id);
}

//----------------------------------------------------------------------

// Prints the root of the new_root.
// Recieves: A pointer to the root of the tree.
// Returns: void.
void print_node(struct Node* new_root)
{
	if (new_root != NULL)
    {
        cout << new_root->_data->_x << " " << new_root->_data->_y 
																<< endl;
    }
    else cout << 0 << " " << 0 << endl;
}

//----------------------------------------------------------------------

// Checks if memory allocation was successful.
// Receives: A constant pointer to void which is checked for `NULL`.
// Returns: Void, but prints an error message and exits if allocation
//	 fails.
void check_if_allocated(const void* const ptr)
{
    if (ptr == NULL)
    {
        cerr << "Can't allocate memory\n";
        exit(EXIT_FAILURE);
    }
}

//----------------------------------------------------------------------

// Frees memory allocated for the entire binary search tree
// Receives: A pointer to the root of the binary search tree.
// Returns: Void, but recursively deletes all nodes.
void free_allocation(struct Node* root)
{
    if (root != NULL)
    {
        free_allocation(root->_left);
        free_allocation(root->_right);
        delete root->_data;
        delete root;
    }
}
