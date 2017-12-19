#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	char *conteudo = (char *) malloc(4096);
	int abre = open("/dev/char_device", O_WRONLY);
	scanf(" %[^\n]", conteudo);
	write(abre, conteudo, 4096);
}
