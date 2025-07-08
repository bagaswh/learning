#include "rbtree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to create a node with string key for testing
struct rbtree_node *create_test_node(const char *key_str) {
	size_t key_len = strlen(key_str);
	return rbtree_create_node((u8 *)key_str, key_len);
}

// Helper function to manually construct tree relationships
void link_nodes(struct rbtree_node *parent, struct rbtree_node *left, struct rbtree_node *right) {
	if (parent) {
		parent->left = left;
		parent->right = right;
		if (left) left->p = parent;
		if (right) right->p = parent;
	}
}

/* --- Search --- */
void test_search_empty_tree() {
	printf("Test 1: Search in empty tree\n");

	struct rbtree_node *result = NULL;
	bool found = rbtree_search(NULL, (u8 *)"test", 4, &result);

	assert(found == false);
	assert(result == NULL);
	printf("✓ Empty tree search works correctly\n\n");
}

void test_search_single_node() {
	printf("Test 2: Search in single node tree\n");

	struct rbtree_node *root = create_test_node("hello");
	struct rbtree_node *result = NULL;

	// Search for existing key
	bool found = rbtree_search(root, (u8 *)"hello", 5, &result);
	assert(found == true);
	assert(result == root);
	printf("✓ Found existing key in single node\n");

	// Search for non-existing key
	result = NULL;
	found = rbtree_search(root, (u8 *)"world", 5, &result);
	assert(found == false);
	printf("✓ Did not find non-existing key in single node\n");

	free(root);
	printf("\n");
}

void test_search_three_nodes() {
	printf("Test 3: Search in three node tree\n");

	// Create nodes: "dog" (root), "cat" (left), "fox" (right)
	struct rbtree_node *root = create_test_node("dog");
	struct rbtree_node *left = create_test_node("cat");
	struct rbtree_node *right = create_test_node("fox");

	link_nodes(root, left, right);

	struct rbtree_node *result = NULL;

	// Search for root
	bool found = rbtree_search(root, (u8 *)"dog", 3, &result);
	assert(found == true);
	assert(result == root);
	printf("✓ Found root node\n");

	// Search for left child
	result = NULL;
	found = rbtree_search(root, (u8 *)"cat", 3, &result);
	assert(found == true);
	assert(result == left);
	printf("✓ Found left child\n");

	// Search for right child
	result = NULL;
	found = rbtree_search(root, (u8 *)"fox", 3, &result);
	assert(found == true);
	assert(result == right);
	printf("✓ Found right child\n");

	// Search for non-existing key
	result = NULL;
	found = rbtree_search(root, (u8 *)"elephant", 8, &result);
	assert(found == false);
	printf("✓ Did not find non-existing key\n");

	free(root);
	free(left);
	free(right);
	printf("\n");
}

void test_search_deeper_tree() {
	printf("Test 4: Search in deeper tree\n");

	// Create a more complex tree:
	//       "dog"
	//      /     \
    //   "cat"   "fox"
	//   /         \
    // "ant"      "goat"

	struct rbtree_node *root = create_test_node("dog");
	struct rbtree_node *cat = create_test_node("cat");
	struct rbtree_node *fox = create_test_node("fox");
	struct rbtree_node *ant = create_test_node("ant");
	struct rbtree_node *goat = create_test_node("goat");

	link_nodes(root, cat, fox);
	link_nodes(cat, ant, NULL);
	link_nodes(fox, NULL, goat);

	struct rbtree_node *result = NULL;

	// Search for leaf nodes
	bool found = rbtree_search(root, (u8 *)"ant", 3, &result);
	assert(found == true);
	assert(result == ant);
	printf("✓ Found deep left leaf\n");

	found = rbtree_search(root, (u8 *)"goat", 4, &result);
	assert(found == true);
	assert(result == goat);
	printf("✓ Found deep right leaf\n");

	// Search for intermediate nodes
	result = NULL;
	found = rbtree_search(root, (u8 *)"cat", 3, &result);
	assert(found == true);
	assert(result == cat);
	printf("✓ Found intermediate node\n");

	free(root);
	free(cat);
	free(fox);
	free(ant);
	free(goat);
	printf("\n");
}

void test_search_numeric_keys() {
	printf("Test 5: Search with numeric keys\n");

	// Create nodes with numeric data
	uint32_t key1 = 100, key2 = 50, key3 = 150;

	struct rbtree_node *root = rbtree_create_node((u8 *)&key1, sizeof(uint32_t));
	struct rbtree_node *left = rbtree_create_node((u8 *)&key2, sizeof(uint32_t));
	struct rbtree_node *right = rbtree_create_node((u8 *)&key3, sizeof(uint32_t));

	link_nodes(root, left, right);

	struct rbtree_node *result = NULL;
	uint32_t search_key = 50;

	bool found = rbtree_search(root, (u8 *)&search_key, sizeof(uint32_t), &result);
	assert(found == true);
	assert(result == left);
	printf("✓ Found numeric key\n");

	search_key = 200;
	result = NULL;
	found = rbtree_search(root, (u8 *)&search_key, sizeof(uint32_t), &result);
	assert(found == false);
	printf("✓ Did not find non-existing numeric key\n");

	free(root);
	free(left);
	free(right);
	printf("\n");
}

void test_search_edge_cases() {
	printf("Test 6: Edge cases\n");

	// Test with empty key
	struct rbtree_node *root = create_test_node("");
	struct rbtree_node *result = NULL;

	bool found = rbtree_search(root, (u8 *)"", 0, &result);
	assert(found == true);
	assert(result == root);
	printf("✓ Found empty key\n");

	// Test with single character keys
	free(root);
	root = create_test_node("a");
	struct rbtree_node *left = create_test_node("A");  // Different case
	link_nodes(root, left, NULL);

	result = NULL;
	found = rbtree_search(root, (u8 *)"A", 1, &result);
	assert(found == true);
	assert(result == left);
	printf("✓ Found single character key\n");

	free(root);
	free(left);
	printf("\n");
}

/* --- Insertion --- */
// Insert: C, A, B
void test_insertion() {
	printf("Test 6: Insertion\n");

	struct rbtree_node *root = rbtree_insert(NULL, "C", 2);
	assert(memcmp(root->key, "C", 2) == 0);
	assert(root->color == BLACK);

	rbtree_insert(root, "A", 2);
	/*
	        C
	      /
	    A
	*/
	assert(memcmp(root->left->key, "A", 2) == 0);

	rbtree_insert(root, "B", 2);
	/*
	        B
	      /   \
	    A       C (root still holds this)
	*/
	assert(memcmp(root->p->key, "B", 2) == 0);
	assert(memcmp(root->p->right->key, "C", 2) == 0);
	assert(memcmp(root->p->left->key, "A", 2) == 0);
	assert(memcmp(root->p->left->p->key, "B", 2) == 0);

	rbtree_free(root);
}

int main() {
	printf("Running Red-Black Tree Search Tests\n");
	printf("====================================\n\n");

	// test_search_empty_tree();
	// test_search_single_node();
	// test_search_three_nodes();
	// test_search_deeper_tree();
	// test_search_numeric_keys();
	// test_search_edge_cases();

	test_insertion();

	printf("All tests passed! ✓\n");
	return 0;
}