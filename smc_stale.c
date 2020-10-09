#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

unsigned char *testfun;

int main(void) {
	unsigned int ra;
	unsigned long page_size;
	unsigned char* ptr;
	unsigned int offset;

	page_size = getpagesize();
	printf("page_size = %ld\n", page_size); //Yong
	testfun = malloc(1023+page_size+1); // why 1023 + pagesize+1?

	if(testfun == NULL)
		return 1;

	//need to align the address on a page boundary
	printf("%p\n", testfun);
	testfun = (unsigned char*)(((long)testfun + page_size - 1) & ~(page_size - 1));
	printf("%p\n", testfun);
	
	//reason of aligning is for this.	
	if(mprotect(testfun, 1024, PROT_READ | PROT_EXEC | PROT_WRITE)) {
		printf("mprotect failed\n");
		return 1;
	}
	
	//xxxxxx: b8 0d 00 00 00 	mov	$0xd,%eax
	//xxxxxx: c3			retq
	testfun[0] = 0xb8;
	testfun[1] = 0x0d;
	testfun[2] = 0x00;
	testfun[3] = 0x00;
	testfun[4] = 0x00;
	testfun[5] = 0xc3;

	for(int i = 0; i < 100000; i++)
		ra = ((unsigned int(*)())testfun)();
	printf("0x%02X\n", ra);

	//xxxxxx: 31 c0			xor 	$eax, $eax
	//xxxxxx: b8 20 00 00 00	mov	$0x20, %eax
	//xxxxxx: c3			retq
	testfun[0] = 0x31;
	testfun[1] = 0xc0;
	testfun[2] = 0xb8;
	testfun[3] = 0x20;
	testfun[4] = 0x00;
	testfun[5] = 0x00;
	testfun[6] = 0x00;
	testfun[7] = 0xc3;

	ra = ((unsigned int(*)())testfun)();
	printf("0x%02X\n", ra);
		
	return 0;
}
