#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define LEN 1024

char shellcode1[] = "\xb8\x0d\x00\x00\x00\xc3";
char shellcode2[] = "\x31\xc0\xb8\x20\x00\x00\x00\xc3";

int main(void) {
	int ra;
	void* ptr = mmap(0, LEN, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);

	memcpy(ptr, shellcode1, sizeof(shellcode1));
	ra = ((unsigned int(*)())ptr)();

	printf("0x%02X ", ra);

	memcpy(ptr, shellcode2, sizeof(shellcode2));
	ra = ((unsigned int(*)())ptr)();

	printf("0x%02X", ra);

	return 0;
}
