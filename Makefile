obj-m += char_device.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) write_dev.cpp -o write
	$(CC) read_dev.cpp -o read
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
