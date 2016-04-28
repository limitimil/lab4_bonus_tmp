#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "objectDetection.h"
#include "edgeDetect.h"
#include "findContours_demo.h"

int fd1,fd2;
int get_value(int addr){
	int value;
	unsigned page_addr, page_offset;
	void *ptr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	//Read from switches using /dev/mem
	page_addr = (addr & (~(page_size-1)));
	page_offset = addr - page_addr;
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, page_addr);
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
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, page_addr);
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
		fd1 = open ("/sys/class/gpio/gpio69/value", O_RDONLY);
		if (fd1 < 1) {
			perror(argv[0]);
			return -1;
		}
		printf("in loop\n");	
		read(fd1,&value_sw,sizeof(char));
		close(fd1);
		switch(value_sw){
			case '1':
				fd2 = open("/sys/class/gpio/gpio70/value",O_RDONLY);
				read(fd2,&value_sw,sizeof(char));
				if(value_sw == '0')
					objectDetection(argc, argv);
				else
					findContours(argc,argv);
				close(fd2);
				break;
			default:
				edgeDetection(argc, argv);
				printf("Switch input: %c\n",value_sw);
				break;
		}
	}


	return 0;
}
