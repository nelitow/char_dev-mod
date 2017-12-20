#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#define  DEVICE_NAME "char_device"
#define  CLASS_NAME  "mod"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nelito");
MODULE_DESCRIPTION("char device nem sei se essa parte precisa mas tava dando erro em algo por aqui");
MODULE_VERSION("0.123456789");

static int    major;
static char   mes_buf[2048] = {0};
static short  size_of_mes_buf;
static struct class*  chardevClass  = NULL;
static struct device* chardevDevice = NULL;

static int     dev_open(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
};

int init_module(void){
   major = register_chrdev(0, DEVICE_NAME, &fops);
   chardevClass = class_create(THIS_MODULE, CLASS_NAME);
   chardevDevice = device_create(chardevClass, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
   printk(KERN_INFO "char device criado\n");
   return 0;
}

static void __exit chardev_exit(void){
   device_destroy(chardevClass, MKDEV(major, 0));
   class_unregister(chardevClass);
   class_destroy(chardevClass);
   unregister_chrdev(major, DEVICE_NAME);
   printk(KERN_INFO "char device saiu\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "char device abertp \n");
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   error_count = copy_to_user(buffer, mes_buf, size_of_mes_buf);

      return (size_of_mes_buf=0);

}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   sprintf(mes_buf, "%s", buffer);
   size_of_mes_buf = strlen(mes_buf);
   return len;
}
