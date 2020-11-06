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
	{ 0x751a24c5, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0xe3684a00, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xccc7a2eb, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x9ea10bb1, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x451d3e2b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x9d25c316, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x2dee278d, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0xdfa47286, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0xdc8b9660, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x4d2bb1cd, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x162455f7, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x8a8930a9, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x41979d26, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xe56d5ae0, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x828c5504, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x28d3875d, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:ds3231_drv");

MODULE_INFO(srcversion, "D3231EA43C049849A17915A");
