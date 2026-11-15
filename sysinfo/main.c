#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/utsname.h>

void getSysInfo(){
	
	struct utsname buf1;
	errno = 0;

	if (uname(&buf1) != 0){
		perror("uname : error");
		exit(EXIT_FAILURE);
	}

	printf("System Name = %s\n", buf1.sysname);
	printf("Nodename = %s\n", buf1.nodename);
	printf("Release = %s\n", buf1.release);
	printf("Version = %s\n", buf1.version);
	printf("Hardware = %s\n", buf1.machine);

}


int main(){
	getSysInfo();
	return 0;
}
