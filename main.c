#include <kv.h>
#include <assert.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	struct kv * kv = kv_alloc();
	assert(get(kv, 0) == NULL);
	assert(get(kv, 42) == NULL);

	return 0;
}
