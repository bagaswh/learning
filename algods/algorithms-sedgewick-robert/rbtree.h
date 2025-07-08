#ifndef RBTREE_H
#define RBTREE_H

#include <stdbool.h>
#include <unistd.h>

#include "util.h"

static const u8 RED = 5;
static const u8 BLACK = 6;

#define RBTREE_SEARCH_FOUND 0
#define RBTREE_SEARCH_MISS_LEFT 1
#define RBTREE_SEARCH_MISS_RIGHT 2
#define RBTREE_SEARCH_ERROR -1

struct rbtree_node {
	struct rbtree_node *p;
	struct rbtree_node *left;
	struct rbtree_node *right;
	u64 size;
	u8 color;
	u64 key_len;
	u8 key[];
};

struct rbtree_node *rbtree_create_node(u8 *key, size_t key_len);
struct rbtree_node *rbtree_free(u8 *key, size_t key_len);
u64 rbtree_size(struct rbtree_node *h);
struct rbtree_node *rbtree_insert(, u8 *key, size_t key_len);
int rbtree_search(struct rbtree_node *tree, u8 *key, size_t key_len, struct rbtree_node **result);

#endif  // RBTREE_H