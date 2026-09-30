#pragma once

/* Maximum number of entries */
#define KV_MAX_NENT 128

struct kv_entry {
	unsigned long key;
	char *val;
};

/*
 * The key-value data-structure.
 *
 * We wrap the implementation details in the `kv` struct to
 * encapsulate them, and make it so that we can change the
 * implementation in the future.
 */
struct kv {
	struct kv_entry entries[KV_MAX_NENT];
	/* add your own data here if needed */
};

/**
 * Allocate a new key-value store.
 *
 * Allocate and initialize a new key-value data-structure.
 *
 * - @return -
 *
 *     - The key-value data-structure
 *     - `NULL` on error
 */
struct kv *kv_alloc();

/**
 * Free an existing key-value structure, including all of the keys and
 * values held within the structure.
 *
 * - @kv - the key-value store to be freed.
 */
void kv_free(struct kv *kv);

/**
 * Get the value associated with a key.
 *
 * - @key - lookup the value associated with the `key`
 * - @return -
 *
 *     - the `value` associated with the `key`
 *     - `NULL` if the `key` doesn't exist in the kv store
 */
char *get(struct kv *kv, unsigned long key);

/**
 * Add a value to the kv data-structure associated with a key.
 *
 * - @key - the key value to identify the `value`.
 * - @value - the value to be associated with the `key`.
 * - @return -
 *
 *     - `0` on successful addition
 *     - `-1` if the `key` already exists, the `value` is `NULL`,
 *       `KV_MAX_ITEMS` keys have already been added, or there is a
 *       memory allocation failure
 */
int put(struct kv *kv, unsigned long key, char *value);


/**
 * Compare function for lsearch/lfind 
 * NOTE: you do NOT need to implement this function (check kv.c)
 * 
 *
 * - @a - element 1
 * - @b - element 2
 * - @return - 
 * 
 * 			- `1` if a->key > b-> key
 * 			- `-1` if a->key < b->key 
 *			- `0` if a->key = b->key
*/
int compare(const void *a, const void *b);