#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "objectDetection.h"
#include "edgeDetect.h"


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
	char value_sw = 0;
	
	unsigned page_addr, page_offset;
	void *ptr;
//	unsigned page_size=sysconf(_SC_PAGESIZE);


	//Read from switches using /dev/mem
	


		printf("out of loop\n");	
	while(1){
		fd = open ("/sys/class/gpio/gpio69/value", O_RDONLY);
		if (fd < 1) {
			perror(argv[0]);
			return -1;
		}
		printf("in loop\n");	
		read(fd,&value_sw,sizeof(char));
		close(fd);
		switch(value_sw){
			case '1':
				objectDetection(argc, argv);
				break;
			default:
				edgeDetection(argc, argv);
				printf("Switch input: %c\n",value_sw);
				break;
		}
	}


	return 0;
}
