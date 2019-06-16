
#include<linux/module.h>
#include<linux/errno.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/slab.h>			/* for kmalloc() and kfree() */
#include<asm/uaccess.h> 		/* for copy to/from users */
#include<linux/mman.h>			/* for mmap() operation */
#include<asm/io.h>
#include<linux/string.h>
#include<linux/ctype.h>
#include<asm/semaphore.h>		/* for struct semaphore, down(), up()  */
#include<linux/spinlock.h>  	/* for spinlock_t , spin_lock(), spin_unlock() */
#include<linux/rwsem.h>     	/* for rw_semaphore - Read/Write semaphore */
#include<linux/completion.h>	/* for DECLARE_COMPLETION(), wait_for_completion() */

#include "pinchar_ioctl.h"


#define DEVICE_NAME		"pinchar"

static int major_no=-1;
static char *pinchar_buffer = NULL;
static char *kmalloc_area=NULL;
static int device_opened = 0;

//static DECLARE_COMPLETION(pinchar_comp);

//static struct semaphore pinchar_sem;
//static struct rw_semaphore pinchar_rwsem;
//static spinlock_t write_lock = SPIN_LOCK_UNLOCKED;
//static spinlock_t read_lock = SPIN_LOCK_UNLOCKED;

char *strUpper(char *buffer)
{
	char *tmp=NULL;

	for(tmp=buffer; *tmp != '\0'; tmp++)
	{
		*tmp = (char)toupper(*tmp);
	}
	return(buffer);
}

static ssize_t pinchar_read(struct file *file, char *buff, size_t length, loff_t *pos)
{
	//unsigned long flags;
	
    printk("<PINCHAR> : Reading....\n");
    if(pinchar_buffer == NULL) 
    {
        printk("<PINCHAR> : Buffer Empty...\n");
        return -ENOMEM;
    }
	//down_read(&pinchar_rwsem);
	/*
	if(down_interruptible(&pinchar_sem)) 
	{
		printk("<PINCHAR> : pinchar_read - semaphore is DOWN.\n");
		return -ERESTARTSYS;
	}
	*/
	//spin_lock_irqsave(&read_lock, flags);
	//wait_for_completion(&pinchar_comp);
    if(copy_to_user(buff,pinchar_buffer,length)) 
	{
		//up(&pinchar_sem);
		//up_read(&pinchar_rwsem);
		return -EFAULT;
	}
	//printk("<PINCHAR> : pinchar_read - semaphore is Released.\n");
	//up(&pinchar_sem);
	//spin_unlock_irqrestore(&read_lock, flags);
	//up_read(&pinchar_rwsem);
    return(length);
}

static ssize_t pinchar_write(struct file *file, const char *buff, size_t length, loff_t *pos)
{
	//unsigned long flags;
	
    printk("<PINCHAR> : Writing....\n");
	printk("<PINCHAR> : Length = %d\n",length);

	//down_write(&pinchar_rwsem);
	/*
	if(down_interruptible(&pinchar_sem)) 
	{
		printk("<PINCHAR> : pinchar_write - semaphore is DOWN.\n");
		return -ERESTARTSYS;
	}
	*/
	//spin_lock_irqsave(&write_lock, flags);
	
    pinchar_buffer = kmalloc(length*sizeof(char),GFP_KERNEL);
    memset(pinchar_buffer,'\0',length*sizeof(char));
    if(copy_from_user(pinchar_buffer,buff,length)) 
	{
		//up(&pinchar_sem);
		//up_write(&pinchar_rwsem);
		return -EFAULT;
	}
	pinchar_buffer[strlen(buff)+1] = '\0';
	printk("<PINCHAR> : pinchar_buffer = %s\n",pinchar_buffer);
	//complete(&pinchar_comp);
	//up(&pinchar_sem);
	//printk("<PINCHAR> : pinchar_write - semaphore is Released.\n");
	//spin_unlock_irqrestore(&write_lock, flags);
	//up_write(&pinchar_rwsem);
    return(length);
}

static int pinchar_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int len=0;
	char *buffer=NULL;

	printk("<PINCHAR> : Device - IOCTL - called....\n");
	switch(cmd)
	{
		case PINCHAR_IOCLENGTH:
			len = strlen(pinchar_buffer);
			__put_user(len,(int __user *)arg);
			return(len);
		break;

		case PINCHAR_IOCUPPER:
			buffer = strUpper(pinchar_buffer);
			printk("<PINCHAR> : IOC buffer - %s\n",buffer);
			len = strlen(buffer);
			if(copy_to_user((char *)arg,buffer,len)) return -EFAULT;
			//__put_user(buffer, (char __user *)arg);
		break;

		case PINCHAR_IOCEMPTY:
			len = strlen(pinchar_buffer);
			memset(pinchar_buffer,'\0',len);
		break;
		
		default:
			return -EINVAL;

	}
	return(0);
}

static int pinchar_mmap(struct file *file, struct vm_area_struct *vma)
{
	printk("<PINCHAR> : %s - called....\n",__FUNCTION__);
	if(remap_pfn_range(vma,vma->vm_start,vma->vm_pgoff,(vma->vm_end-vma->vm_start),vma->vm_page_prot))
	//if(remap_pfn_range(vma,vma->vm_start,virt_to_phys((void*)kmalloc_area) << PAGE_SHIFT,(vma->vm_end-vma->vm_start),PAGE_SHARED))
	{
		return -EAGAIN;
	}
	return 0;
}

static int pinchar_open(struct inode *inode, struct file *file)
{
    printk("<PINCHAR> : Device opened....\n");
	//outb_p(0xed,0x60);
	//udelay(1000);
	//outb_p(0x04,0x60); udelay(1000);
	//if(down_interruptible(&pinchar_sem)) return -ERESTARTSYS;
	device_opened++;
	printk("Device Opened : %d\n",device_opened);
	//MOD_INC_USE_COUNT;
    return(0);
}

static int pinchar_close(struct inode *inode, struct file *file)
{
    printk("<PINCHAR> : Device is Closed....\n");
    pinchar_buffer=NULL;
    kfree(pinchar_buffer);
	device_opened--;
	if(device_opened < 0) device_opened = 0;
	//up(&pinchar_sem);
	//MOD_DEC_USE_COUNT;
    return(0);
}


struct file_operations pinchar_fops = {
    .owner = THIS_MODULE,
    .read  = pinchar_read,
    .write = pinchar_write,
    .ioctl = pinchar_ioctl,
    .open  = pinchar_open,
    .mmap  = pinchar_mmap,
    .release = pinchar_close,
};


static int __init pinchar_init(void)
{
    printk("<PINCHAR> : Device Initialized......\n");
    major_no = register_chrdev(0, DEVICE_NAME, &pinchar_fops);
    if(major_no < 0)
    {
        printk("<PINCHAR> : Registration Failed....\n");
        return(-1);
    }
	//MKDEV(major_no, 0);
    printk("<PINCHAR> : Device Registered Successfully...!\n");
    printk("<PINCHAR> : Major Number - %d\n",major_no);

	/* Initialize the semaphore */
	//sema_init(&pinchar_sem, 1);
	//init_rwsem(&pinchar_rwsem);
    return(0);
}

static void __exit pinchar_exit(void)
{
    printk("<PINCHAR> : Device exited..\n");
    unregister_chrdev(major_no, DEVICE_NAME);
}


module_init(pinchar_init);
module_exit(pinchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PINTU KUMAR");
MODULE_DESCRIPTION("pinchar Driver...!");

