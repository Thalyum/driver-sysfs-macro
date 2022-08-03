#include <stdio.h>
#include <stdlib.h>

#define EMPTY

#define DEV_ATTR_RO(sysfile) static int sysfile=0
#define DEV_ATTR_WO(sysfile) static int sysfile=0
#define DEV_ATTR_RW(sysfile) static int sysfile=0

#define FILL_RO(sysfile, startaddr, count)				\
	static void sysfile ##_show( int a ) {				\
		for( int i=0; i < count; i++) {			\
			printf( #sysfile ": show %#x: %d\n",		\
				startaddr + i, i);			\
		}							\
	}

#define FILL_WO(sysfile, startaddr, count)				\
	static void sysfile ##_store( int a ) {			\
		for( int i=0; i < count; i++) {			\
			printf( #sysfile ": store %#x: %d\n",		\
				startaddr + i, i);			\
		}							\
	}

#define FILL_RW(sysfile, startaddr, count)		\
	FILL_WO(sysfile, startaddr, count)		\
	FILL_RO(sysfile, startaddr, count)

#define add(sysfile, mode, startaddr, count)		\
	FILL_##mode( sysfile, startaddr, count )	\
	DEV_ATTR_##mode( sysfile )

add(foo,RW, 0x50, 3);
add(bar,RO, 0x10, 6);
add(baz,WO, 0x14, 2);

	;

int main() {
	int i = 1;
	printf("osef\n");
	foo_show(i);
	foo_store(i);
	++i;
	bar_show(i);
	baz_store(i);

	return 0;
}
