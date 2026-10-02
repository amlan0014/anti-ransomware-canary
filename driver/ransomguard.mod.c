#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x04784d05, "cdev_add" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x6bde9a2b, "class_create" },
	{ 0x7a26db4a, "cdev_del" },
	{ 0x3dff2093, "device_create" },
	{ 0x51379816, "class_destroy" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x1c303cee, "validate_usercopy_range" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x56781631, "device_destroy" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xe37020e5, "cdev_init" },
	{ 0xfb93e521, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5FCA210BEE44622D0116D95");
