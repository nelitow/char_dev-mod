#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void){
	printk(KERN_INFO "Hello world\n");
	return 0;
}

void cleanup_module(void){
	printk(KERN_INFO "Bye world\n");
}

//codigos no quadro
/dev/meudev
int meuopen(struct inode* in, struct file* s){}

file_operations opts;
opts.open = meuopen;
opts.write = meuwrite;
int fd = open("/dev/ttyS0");
write(fd, 'x');

ssize_t meuwrite(struct file * t , const char * c){}
