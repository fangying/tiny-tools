#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>
#include <asm/delay.h>

static long unsigned int base_addr = 0;
static long unsigned int size = 0;

module_param(base_addr, ulong, S_IRUSR);
MODULE_PARM_DESC(base_addr, "base mmio address");

module_param(size, ulong, S_IRUSR);
MODULE_PARM_DESC(size, "size to read/write");

static int readmmio_init(void)
{
	int t0, t1, j = 0, sum = 0;
	volatile int r;
	void __iomem *addr;
	void __iomem *i;

	pr_info("mmio read test begin\n");
	addr = ioremap_uc(base_addr, size);

	pr_info("ioremap_uc base_addr:0x%p size:0x%lx\n", addr, size);
	for(i = addr; i < addr + size; i += 4) {
		j = 0;
		sum = 0;
		while (j < 100) {
			t0 = rdtsc_ordered();
			r = ioread32(addr);
			t1 = rdtsc_ordered();
			sum += (t1 - t0);
			j++;
		}
		udelay(10);
		pr_info("read mmio 0x%p average time = %d\n", addr, sum / 100);
	}

	pr_info("mmio test end\n");
	iounmap(addr);
	return 0;
}


static void readmmio_exit(void)
{

}
module_init(readmmio_init);
module_exit(readmmio_exit);

MODULE_ALIAS("iotest");
MODULE_LICENSE("GPL v2");
