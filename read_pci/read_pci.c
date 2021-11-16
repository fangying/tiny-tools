#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>

static long int bus = 0;
module_param(bus, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(bus, "bus");

static long int slot = 0;
module_param(slot, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(slot, "slot");

static long int func = 0;
module_param(func, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(func, "func");

#define PCI_DEVFN(slot,func)    ((((slot) & 0x1f) << 3) | ((func) & 0x07))

static int read_pci_init(void)
{
	int i;
	volatile int value = 0;
	int t0, t1 ;
	int sum, j;

	pr_info("read pci device=%lx:%lx.%lx\n", bus, slot, func);
	if (bus > 255 || slot > 32 || func >8) {
		pr_info("invalid bdf format\n");
		return -1;
	}

	for(i=0; i<256/4; i++) {
		sum = 0;
		for (j=0; j<100; j++) {
			t0 = rdtsc_ordered();
			outl(0x80000000 | ((bus & 0xff) << 16) | (PCI_DEVFN(slot, func) << 8) | ((i<<2) & ~3), 0xcf8);
			value = inl(0xcfc);
			t1 = rdtsc_ordered();
			sum += (t1 - t0);
		}
		printk("cfg offset=0x%x value=0x%x elapse=%d\n", (i<<2), value, sum / 100);
	}
	return 0;
}


static void read_pci_exit(void)
{

}
module_init(read_pci_init);
module_exit(read_pci_exit);

MODULE_ALIAS("read_pci");
MODULE_LICENSE("GPL v2");
