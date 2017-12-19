#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h> //linux 4. sl o q

int init_module(void);
void cleanup_module(void);
static int char_device_open(struct inode *, struct file *);
static ssize_t char_device_read(struct file *, char *, size_t, loff_t *);
static ssize_t char_device_write(struct file *, const char *, size_t, loff_t *);

static int Major;
static char * io_buffer;
int buffsize = 0;
int aux;
static struct file_operations fops = {
	.read = char_device_read,
	.write = char_device_write,
	.open = char_device_open
};

ssize_t char_device_write( struct file *file,const char *buf, size_t length, loff_t *f_pos){
    // copia os dados do segmento de usuario para o de kernel
    aux = copy_from_user(io_buffer,buf,length);

    printk(KERN_INFO "Escreveu: %s\n", io_buffer);
    buffsize = length;
    return length;
}

ssize_t char_device_read(struct file * _file, char *buf, size_t length, loff_t *offset){
    int res;
    if (* io_buffer == 0) return 0; //se estiver no final do arq

    //se o buffsize for menor que a largura da palavra
    if (buffsize < length) res = buffsize;
    else res = length;
  
    //copia os dados do segmento de kernel para o de usuario
    aux = copy_to_user(buf, io_buffer, res);

    if(aux){
        printk(KERN_INFO "copy to user fail");
        return -EFAULT;
    }else{
        printk(KERN_INFO "copy to user succeed\n");
        buffsize -= res;
        return res;
    }

}

int char_device_open(struct inode * _inode, struct file * _file){
	printk(KERN_INFO "Hello: opened %s\n", _file->f_path.dentry->d_name.name);
	return 0;//SUCCESS
}

int init_module(void){
	static struct file_operations fops;
	Major = register_chrdev(60, "char_device", &fops);

	io_buffer = (char*) kmalloc(4096, GFP_KERNEL);
	
	fops.write = char_device_write;
	fops.read = char_device_read;
	fops.open = char_device_open;

	printk(KERN_INFO "Hello World\n");
	return 0;
}

void cleanup_module(void){
	unregister_chrdev(60, "char_device");
	kfree(io_buffer);
	printk(KERN_INFO "Bye World\n");
}
