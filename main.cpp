#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "objectDetection.h"


int fd;
int get_value(int addr){
	int value;
	unsigned page_addr, page_offset;
	void *ptr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	//Read from switches using /dev/mem
	page_addr = (addr & (~(page_size-1)));
	page_offset = addr - page_addr;
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);
	/* Read value from the device register */
	value = *((unsigned *)(ptr + page_offset));
	munmap(ptr, page_size);
	return value;
}
void write_value(int addr,int input){
	int value;
	unsigned page_addr, page_offset;
	void *ptr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	//Read from switches using /dev/mem
	page_addr = (addr & (~(page_size-1)));
	page_offset = addr - page_addr;
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);
	/* Read value from the device register */
	value = *((unsigned *)(ptr + page_offset));
	*((unsigned *)(ptr + page_offset)) = input;
	munmap(ptr, page_size);
	return;
}
int main(int argc, const char **argv)
{
	printf("map success");
	int value_sw = 0;
	
	unsigned page_addr, page_offset;
	void *ptr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	printf("map success");
	//Read from switches using /dev/mem
	
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror(argv[0]);
		return -1;
	}
	/* mmap the device into memory */
	printf("map success");
	page_addr = (0x41200000 & (~(page_size-1)));
	printf("map success");
	page_offset = 0x41200000 - page_addr;
	printf("map success");
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);
	printf("map success");
	/* Read value from the device register */
	value_sw = *((unsigned *)(ptr + page_offset));
	printf("Switch input: %08x\n",value_sw);
	munmap(ptr, page_size);


	printf("Switch input: %08x\n",get_value(0x41200000));
	while(1){
		value_sw = get_value(0x41200000);
		switch(value_sw){
			case 0:
				objectDetection(argc, argv);
				break;
			default:
				printf("Switch input: %08x\n",value_sw);
				break;
		}
	}


	close(fd);
	return 0;
}
