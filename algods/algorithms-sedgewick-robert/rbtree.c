#include "rbtree.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slice.h"

static struct rbtree_node *null_link;

struct rbtree_node *rbtree_create_node(u8 *key, size_t key_len) {
	struct rbtree_node *node = malloc(sizeof(struct rbtree_node) + key_len);
	if (!node) return NULL;

	memcpy(node->key, key, key_len);
	node->key_len = key_len;
	node->left = NULL;
	node->right = NULL;
	node->p = NULL;
	node->color = BLACK;
	node->size = 1;
	return node;
}

void rbtree_traverse_dfs(struct rbtree_node *tree, bool (*cb)(struct rbtree_node *node)) {
	if (tree == NULL) return;
	struct rbtree_node *temp = tree;

	Slice *stack = slice_new(5, 0, sizeof(temp));
	if (stack == NULL) return;
	slice_append(stack, temp);

	while (slice_get_len(stack) > 0) {
	}
}

void rbtree_free(struct rbtree_node *tree) {
	if (tree != NULL) {
		free(tree);
	}
	return;
}

u64 rbtree_size(struct rbtree_node *h) {
	if (h == NULL) {
		return 0;
	}
	return h->size;
}

void rbtree_node_key(struct rbtree_node *node, char *result) {
	if (result == NULL) {
		return;
	}
	if (node == NULL) {
		strcpy(result, "NULL");
	} else {
		memcpy(result, node->key, node->key_len);
	}
}

bool rbtree_node_is_right_child(struct rbtree_node *node) {
	return node->p != NULL && node->p->right != NULL && node->p->right == node;
}

bool rbtree_node_is_left_child(struct rbtree_node *node) {
	return node->p != NULL && node->p->left != NULL && node->p->left == node;
}

static struct rbtree_node *rbtree_rotate_left(struct rbtree_node *node) {
	// char *node_key = malloc(10);
	// rbtree_node_key(node, node_key);
	// printf("rotating: %s\n", node_key);

	struct rbtree_node *temp = node->right;
	// rbtree_node_key(temp, node_key);
	// printf("temp=node->right: %s\n", node_key);

	node->right = temp->left;
	// rbtree_node_key(node->right, node_key);
	// printf("node->right=temp->left: %s\n", node_key);

	temp->left = node;
	// rbtree_node_key(temp->left, node_key);
	// printf("temp->left=node: %s\n", node_key);

	temp->p = node->p;
	// rbtree_node_key(temp->p, node_key);
	// printf("temp->p=node->p: %s\n", node_key);

	if (node->p != NULL) {
		if (rbtree_node_is_left_child(node)) {
			node->p->left = temp;
		} else {
			node->p->right = temp;
		}
	}
	node->p = temp;
	// rbtree_node_key(node->p, node_key);
	// printf("node->p=temp: %s\n", node_key);
	temp->color = node->color;
	node->color = RED;
	temp->size = node->size;
	node->size = 1 + rbtree_size(node->left) + rbtree_size(node->right);
	return node;
}

static struct rbtree_node *rbtree_rotate_right(struct rbtree_node *node) {
	char *node_key = malloc(10);
	rbtree_node_key(node, node_key);
	printf("right_rotating: %s\n", node_key);

	struct rbtree_node *temp = node->left;
	rbtree_node_key(temp, node_key);
	printf("temp=node->left: %s\n", node_key);

	node->left = temp->right;
	rbtree_node_key(node->left, node_key);
	printf("node->left = temp->right: %s\n", node_key);

	temp->right = node;
	rbtree_node_key(temp->right, node_key);
	printf("temp->right=node: %s\n", node_key);

	temp->p = node->p;
	rbtree_node_key(temp->p, node_key);
	printf("temp->p=node->p: %s\n", node_key);

	if (node->p != NULL) {
		if (rbtree_node_is_left_child(node)) {
			node->p->left = temp;
		} else {
			node->p->right = temp;
		}
	}
	node->p = temp;
	rbtree_node_key(node->p, node_key);
	printf("node->p=temp: %s\n", node_key);
	temp->color = node->color;
	node->color = RED;
	temp->size = node->size;
	node->size = 1 + rbtree_size(node->left) + rbtree_size(node->right);
	return node;
}

static void rbtree_flip_colors(struct rbtree_node *node) {
	node->color = RED;
	if (node->left != NULL) {
		node->left->color = BLACK;
	}
	if (node->right != NULL) {
		node->right->color = BLACK;
	}
}

static int compare_key(u8 *key1, u8 *key2, size_t n) {
	return memcmp(key1, key2, n);
}

static bool key_is_equal(u8 *key1, u8 *key2, size_t n) {
	return compare_key(key1, key2, n) == 0;
}

bool rbtree_is_node_root(struct rbtree_node *node) {
	return node != NULL && node->p == NULL;
}

struct rbtree_node *rbtree_node_grandparent(struct rbtree_node *node) {
	if (node == NULL || node->p == NULL || node->p->p == NULL) return NULL;
	return node->p->p;
}

struct rbtree_node *rbtree_node_uncle(struct rbtree_node *node) {
	struct rbtree_node *grandparent = rbtree_node_grandparent(node);
	if (grandparent == NULL) return NULL;
	struct rbtree_node *uncle = NULL;
	if (grandparent->right == node->p) {
		uncle = grandparent->left;
	} else if (grandparent->left == node->p) {
		uncle = grandparent->right;
	}
	return uncle;
}

bool rbtree_is_red(struct rbtree_node *node) {
	if (node == NULL) {
		return false;
	}

	return node->color == RED;
}

void rbtree_node_color(struct rbtree_node *node, char *result) {
	if (node == NULL || result == NULL) {
		return;
	}

	switch (node->color) {
	case RED:
		strcpy(result, "RED");
		break;
	case BLACK:
		strcpy(result, "BLACK");
		break;
	}
}

struct rbtree_node *rbtree_insert(struct rbtree_node *tree, u8 *key, size_t key_len) {
	struct rbtree_node *node = rbtree_create_node(key, key_len);
	if (node == NULL) {
		return NULL;
	}
	node->size = 1;
	if (tree == NULL) {
		// node is root
		node->color = BLACK;
		return node;
	}

	// char *node_color = malloc(10);
	// rbtree_node_color(node, node_color);
	// printf("root color=%s\n", node_color);

	struct rbtree_node *result;
	int search_ret = rbtree_search(tree, key, key_len, &result);
	if (search_ret == RBTREE_SEARCH_FOUND) {
		return result;
	}

	struct rbtree_node *parent = result;
	parent->size++;
	node->color = RED;
	node->p = parent;
	if (search_ret == RBTREE_SEARCH_MISS_LEFT) {
		parent->left = node;
	} else {
		parent->right = node;
	}

	// rbtree_node_color(parent, node_color);
	// printf("parent of %s: %s, color=%s\n", node->key, parent->key, node_color);
	// fflush(stdout);
	// if (grandparent != NULL) {
	// 	rbtree_node_color(grandparent, node_color);
	// 	printf("grandparent of %s: %s, color=%S\n", node->key, grandparent->key, node_color);
	// 	fflush(stdout);
	// }

	struct rbtree_node *grandparent = rbtree_node_grandparent(node);
	struct rbtree_node *uncle = rbtree_node_uncle(node);

	while (rbtree_is_red(parent)) {
		if (rbtree_is_node_root(parent)) {
			parent->color = BLACK;
			break;
		}

		if (uncle != NULL) {
			if (rbtree_is_red(uncle)) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				parent = grandparent;
			} else {
				if (rbtree_node_is_right_child(node)) {
					rbtree_rotate_left(parent);
					// rbtree_rotate_right(grandparent);
				} else {
					// printf("grandparent rotate right inside uncle\n");
					// fflush(stdout);

					rbtree_rotate_right(parent);
					// rbtree_rotate_left(grandparent);
				}
				parent->color = BLACK;
				grandparent->color = RED;
			}
		} else {
			if (rbtree_node_is_left_child(parent)) {
				if (rbtree_node_is_right_child(node)) {
					printf("rbtree_rotate_left parent %s\n", parent->key);
					rbtree_rotate_left(parent);
				} else {
					char *node_key = malloc(10);
					rbtree_node_key(grandparent, node_key);
					printf("node_key: %s\n", node_key);
					rbtree_rotate_right(grandparent);
					parent = parent->p;
				}
			}
			// else {
			// 	if (rbtree_node_is_right_child(node)) {
			// 		rbtree_rotate_right(parent);
			// 	} else {
			// 		rbtree_rotate_left(grandparent);
			// 	}
			// }
		}

		parent->size = 1 + rbtree_size(parent->left) + rbtree_size(parent->right);
	}

	return node;
}

int rbtree_search(struct rbtree_node *tree, u8 *key, size_t key_len, struct rbtree_node **result) {
	struct rbtree_node *prev_temp = tree, *temp = tree;

	u8 last_link_dir = 0;
	while (true) {
		if (temp == NULL) {
			*result = prev_temp;
			return last_link_dir;
		}
		int comp = compare_key(temp->key, key, key_len);
		if (comp == 0) {
			if (result == NULL) {
				return RBTREE_SEARCH_ERROR;
			}
			*result = temp;
			return RBTREE_SEARCH_FOUND;
		}
		prev_temp = temp;
		if (comp > 0) {
			last_link_dir = RBTREE_SEARCH_MISS_LEFT;
			temp = temp->left;
		} else {
			last_link_dir = RBTREE_SEARCH_MISS_RIGHT;
			temp = temp->right;
		}
	}
}

// struct rbtree_node *rbtree_min_node(struct rbtree_node *tree) {
// 	if (tree == NULL) {
// 		return NULL;
// 	}
// 	if (tree->left == NULL) {
// 		return tree;
// 	}
// 	struct rbtree_node *temp = tree->left;
// 	while (temp != NULL) {
// 		temp = temp->left;
// 	}
// 	return temp;
// }

// struct rbtree_node *rbtree_max_node(struct rbtree_node *tree) {
// 	if (tree == NULL) {
// 		return NULL;
// 	}
// 	if (tree->right == NULL) {
// 		return tree;
// 	}
// 	struct rbtree_node *temp = tree->right;
// 	while (temp->right != NULL) {
// 		temp = temp->right;
// 	}
// 	return temp;
// }

// int rbtree_length(struct rbtree_node *tree) {
// 	if (tree == NULL) {
// 		return NULL;
// 	}
// 	struct rbtree_node *min = rbtree_min(tree);
// 	struct rbtree_node *max = rbtree_max(tree);
// 	if (min == max) {
// 		return 1;
// 	}
// 	int length = 1;
// 	struct rbtree_node *temp = tree->right;
// 	while (temp != NULL) {
// 		length++;
// 		temp = temp->right;
// 	}
// 	return length;
// }

// void draw_tree(struct rbtree_node *tree) {
// 	struct rbtree_node *min = rbtree_min(tree);
// 	struct rbtree_node *max = rbtree_max(tree);
// 	int length = rbtree_length(tree);
// }