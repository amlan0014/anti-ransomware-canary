#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define DEVICE_NAME "ransomguard"
#define CLASS_NAME "ransomguard"
#define BUFFER_SIZE 256

static dev_t device_number;
static struct cdev ransomguard_cdev;
static struct class *ransomguard_class;
static struct device *ransomguard_device;

static char event_buffer[BUFFER_SIZE];
static size_t event_size;

static DEFINE_MUTEX(event_mutex);

static int ransomguard_open(struct inode *inode, struct file *file)
{
    pr_info("ransomguard: device opened\n");
    return 0;
}

static int ransomguard_release(struct inode *inode, struct file *file)
{
    pr_info("ransomguard: device closed\n");
    return 0;
}

static ssize_t ransomguard_write(
    struct file *file,
    const char __user *user_buffer,
    size_t count,
    loff_t *offset)
{
    size_t bytes_to_copy;

    if (count == 0)
        return 0;

    bytes_to_copy = min(count, (size_t)(BUFFER_SIZE - 1));

    mutex_lock(&event_mutex);

    memset(event_buffer, 0, BUFFER_SIZE);

    if (copy_from_user(event_buffer, user_buffer, bytes_to_copy)) {
        mutex_unlock(&event_mutex);
        return -EFAULT;
    }

    event_buffer[bytes_to_copy] = '\0';
    event_size = bytes_to_copy;

    pr_alert("ransomguard: event received: %s\n", event_buffer);

    mutex_unlock(&event_mutex);

    return bytes_to_copy;
}

static ssize_t ransomguard_read(
    struct file *file,
    char __user *user_buffer,
    size_t count,
    loff_t *offset)
{
    ssize_t result;

    mutex_lock(&event_mutex);

    if (*offset >= event_size) {
        mutex_unlock(&event_mutex);
        return 0;
    }

    if (count > event_size - *offset)
        count = event_size - *offset;

    if (copy_to_user(
            user_buffer,
            event_buffer + *offset,
            count)) {
        mutex_unlock(&event_mutex);
        return -EFAULT;
    }

    *offset += count;
    result = count;

    mutex_unlock(&event_mutex);

    return result;
}

static const struct file_operations ransomguard_fops = {
    .owner = THIS_MODULE,
    .open = ransomguard_open,
    .release = ransomguard_release,
    .read = ransomguard_read,
    .write = ransomguard_write,
};

static int __init ransomguard_init(void)
{
    int result;

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0) {
        pr_err("ransomguard: failed to allocate device number\n");
        return result;
    }

    cdev_init(&ransomguard_cdev, &ransomguard_fops);
    ransomguard_cdev.owner = THIS_MODULE;

    result = cdev_add(
        &ransomguard_cdev,
        device_number,
        1
    );

    if (result < 0) {
        unregister_chrdev_region(device_number, 1);
        pr_err("ransomguard: failed to add character device\n");
        return result;
    }

    ransomguard_class = class_create(CLASS_NAME);

    if (IS_ERR(ransomguard_class)) {
        cdev_del(&ransomguard_cdev);
        unregister_chrdev_region(device_number, 1);
        pr_err("ransomguard: failed to create device class\n");
        return PTR_ERR(ransomguard_class);
    }

    ransomguard_device = device_create(
        ransomguard_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME
    );

    if (IS_ERR(ransomguard_device)) {
        class_destroy(ransomguard_class);
        cdev_del(&ransomguard_cdev);
        unregister_chrdev_region(device_number, 1);

        pr_err("ransomguard: failed to create device\n");
        return PTR_ERR(ransomguard_device);
    }

    pr_info("ransomguard: kernel driver loaded\n");
    pr_info("ransomguard: device created at /dev/%s\n", DEVICE_NAME);

    return 0;
}

static void __exit ransomguard_exit(void)
{
    device_destroy(
        ransomguard_class,
        device_number
    );

    class_destroy(ransomguard_class);

    cdev_del(&ransomguard_cdev);

    unregister_chrdev_region(
        device_number,
        1
    );

    pr_info("ransomguard: kernel driver unloaded\n");
}

module_init(ransomguard_init);
module_exit(ransomguard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anti-Ransomware Canary Monitor");
MODULE_DESCRIPTION(
    "Kernel character device for anti-ransomware event reporting"
);
MODULE_VERSION("1.0");
