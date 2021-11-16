#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>

static int readio_init(void)
{
	int port, r, t0, t1, i, sum;
	pr_info("readio begin\n");
	for (port = 0; port < 0xffff; port++) {
		sum = 0;
		for (i = 0; i < 100; i++) {
			t0 = rdtsc_ordered();
			r = inb(port);
			t1 = rdtsc_ordered();
			sum += (t1 - t0);
		}
		pr_info("port:%x , r = %d, time = %d\n", port, r, sum / 100);
	}

	pr_info("readio end\n");
	return -1;
}


static void readio_exit(void)
{

}
module_init(readio_init);
module_exit(readio_exit);

MODULE_ALIAS("readio");
MODULE_LICENSE("GPL v2");
