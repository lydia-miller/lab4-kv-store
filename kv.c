#include <stdlib.h>
#include <string.h>
#include <search.h>

#include <kv.h>

/* There's an error in this function! Where? */
struct kv *
kv_alloc()
{
	struct kv *kv = malloc(sizeof(struct kv));

	/*
	 * Initialize the structure to all zeros. Recall `NULL` is
	 * equivalent to `0`, so this initializes all `val` fields to
	 * `NULL`.
	 */
	memset(kv, 0, sizeof(struct kv));

	return kv;
}

void
kv_free(struct kv *kv)
{
	int i;

	for (i = 0; i < KV_MAX_NENT; i++) {
		char *val = kv->entries[i].val;

		if (val != NULL) free(val);
	}

	free(kv);
}

char *
get(struct kv *kv, unsigned long key)
{
	/* Your implementation with `lsearch`/`lfind` here! */

	return NULL;
}

int
put(struct kv *kv, unsigned long key, char *value)
{
	/* Your implementation with `lsearch`/`lfind` here! */

	return 0;
}

/* This is a helper function! How are you going to use it? */
int compare(const void *a, const void *b){
	struct kv_entry * c = (struct kv_entry *)(a);
	struct kv_entry * d = (struct kv_entry *)(b);

	//check here 
	if ((int)(c->key)>(int)(d->key)){
		return 1;
	
	}

	else if ((int)(c->key)<(int)(d->key)){
		return -1;
	}

	return 0;
	
}