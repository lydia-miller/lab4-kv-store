# Lab 4: Key-Value Store and Testing

## Overview & Objectives

- Practice using `man` pages to learn about APIs.
- Demonstrate ability to use a documented libc function.
- Understand function pointers, and `void *` references.
- Understand the interface for, and implement a simple key-value store.
- Prepare for a key-value store implementation with more complex libc functions.

## Lab

For this lab, we'll use `lsearch`/`lfind` from within the standard library to implement a simple key-value store.
Then you're going to learn how to test your implementation.
Key-value stores are used pervasively in our applications -- each post on social media has at least a key used to locate the post's data.
The next homework will be to expand on this lab.

### Specification

A key-value store Application Programming Interface (API) includes four functions:

- `struct kv *kv_alloc()` - allocate a new, empty key-value store, and return it.
- `void kv_free(struct kv *kv)` - deallocate the key-value store.
- `char *kv_get(struct kv *kv, unsigned long key)` - which looks up (returns) a value that corresponds to the `key` argument.
	Return `NULL` if the `key` has not been added to the data-structure.
- `int kv_put(struct kv *kv, unsigned long key, char *value)` - which adds a `value` to the data-structure and associates it with `key`.
	Returns `-1` if the `key` already exists in the data-structure, if `value` is `NULL`, or if more than `KV_MAX_ITEMS` have been added to the data-structure, and `0` if the `put` is otherwise successful.

Note that this looks a lot like the internal structure in a hash-table, that maps a hashed value (e.g. like our `key`s) to a string.

See an initial skeleton of these functions in `kv.c`, with a "starter" implementation of the allocation and free functions.

**Questions & Tasks (2 min):**

1. *Discuss*: Where do you think key-value stores are used?
2. *Discuss*: Data-structures in C often have `_alloc` and `_free` functions.
   How is this similar to, and different from Java?

### TODOs

Read about `lsearch` and `lfind`.
You'll use these functions to implement your key-value store.
Focus on what conditions you must consider and implement when using these functions.

When implementing the above specification, you'll likely think of potential errors that you'd like to check for, but can't.
C provides `NULL` as a universal value applicable to all pointer types against which you can always explicitly check (e.g. `if (p == NULL) { handle_error(); }`).
These include things like "has the client passed in a valid pointer?", "did the client pass in a pointer of the correct type?".
C doesn't really allow your functions any way to test for this.
If a pointer is passed in to the implementation, there is no way for the implementation to know that it is pointing to something of the valid type.
The best one can do is to test the implementation based on the *values* in the arguments (i.e. what the pointer references), and rely on `valgrind` for the rest.

> To understand `lsearch`/`lfind`, recall that
>
> 1. function pointers enable you to add functionality specific to the types of your implementation (like `compar`, or "compare", so that you can compare if an entry in the data-structure holds a specific key), and
> 2. the `void *`s that are arguments to the function pointer simply denote "any pointer type", so you'll want to *cast* them to whatever pointer type(s) you use.

**Questions & Tasks (10 min):**

1. *Discuss*: What are the asymtotic runtime properties of `lsearch`/`lfind`?
2. *Discuss*: What are the conditions that the implementation of these functions must consider?
3. *Write-down*: What are some key inputs that you should use to test *all* conditions?

**Questions & Tasks (30 min):**

1. *Code*: Implement `kv_put` and test it using its return values, and carefully constructed inputs.
2. *Code*: Implement `kv_get` and test it along with `kv_put`.
3. *Code*: Implement test cases that cover *all* cases.

### Bonus

C is *not* a garbage-collected language.
This means that providing an API with only function prototypes is not sufficient.
We must *also* specify if the *caller* or the *callee* is responsible for `free`ing any pointers passed into the functions, or returned from the function.
This decision has significant impacts on how the functions are implemented, and how the caller uses the API.
For example, lets think about:

```c
char *saved_val;

void
save_val(char *key)
{
	char *val = kv_get(kvstore, key);

	if (val) {
		/* Lets  squirrel this away for later use */
		saved_val = val;
	}
}
```

If your key-value implementation is responsible for freeing the values returned from `kv_get`, then this can cause problems!
The key-value store could free the returned value, and now we have a *dangling pointer* to its memory in `saved_val`!
