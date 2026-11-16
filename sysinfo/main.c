#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>

#define CPU_FIELDS 8 // user nice system idle iowait irq softirq steal

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

int read_cpu(unsigned long long values[CPU_FIELDS]){
	FILE *ptr;
	char usage[256];

	ptr = fopen("/proc/stat", "r");

	if (ptr == NULL){
		printf("Error while opening file");
		exit(1);
	}

	if (fgets(usage, sizeof usage, ptr) == NULL){
		fclose(ptr);
		return -1;
	}	

	fclose(ptr);

	char *tok = strtok(usage, " \n");
	if (tok == NULL || strcmp(tok, "cpu") != 0){
		return -1;
	}

	for (int i = 0; i < CPU_FIELDS; i++){
		tok = strtok(NULL, " \n");
		
		if (tok == NULL) return -1;

		values[i] = strtoull(tok, NULL, 10);

	}

	return 0;
}

void cpu_info(void){
	unsigned long long a[CPU_FIELDS], b[CPU_FIELDS];

	if (read_cpu(a) != 0) return;
	sleep(1);
	if (read_cpu(b) != 0) return;

	unsigned long long totalA = 0, totalB = 0;

	for (int i = 0; i < CPU_FIELDS; i++){
		totalA += a[i];
		totalB += b[i];
	}

	unsigned long long dTotal = totalB - totalA;
	
	// change in idle + iowait
	// iowait is also idle
	unsigned long long dIdle = (b[3] + b[4] - (a[3] + a[4]));

	if (dTotal == 0){
		printf("CPU Usage: n/a\n");
		return;
	}

	printf("CPU Usage	= %.2f%%\n", 100.0 * (double)(dTotal - dIdle) / (double)dTotal);
}


int main(){

	while (1){
		getSysInfo();
		cpu_info();
	}	
	return 0;
}
