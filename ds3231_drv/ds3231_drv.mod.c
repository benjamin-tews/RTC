#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbca7617b, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe3684a00, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x9ea10bb1, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x451d3e2b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xccc7a2eb, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x162455f7, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x8a8930a9, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x41979d26, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xe56d5ae0, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D6BC160DEEE4B1C593575EF");
