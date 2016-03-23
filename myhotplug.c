#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>  // for task_struct
#include <linux/time.h>   // for using jiffies 
#include <linux/timer.h>
#include <linux/cpu.h>
#include <linux/smpboot.h>



struct task_struct *my_hotplugd;


static void run_my_hotplugd(unsigned int cpu);

static struct smp_hotplug_thread my_hotplug_threads = {
        .store                  = &my_hotplugd,
        .thread_fn              = run_my_hotplugd,
        .thread_comm            = "my_hotplugd/%u",
};




static void run_my_hotplugd(unsigned int cpu){

unsigned long j0,j1;
int delay = 60*HZ;
j0 = jiffies;
j1 = j0 + delay;

printk(KERN_INFO "Aditya: Start My Hotplugd/%u ", cpu);

while (time_before(jiffies, j1))
        schedule();


	
}


static __init int my_spawn_hotplug_threads(void){

         BUG_ON(smpboot_register_percpu_thread(&my_hotplug_threads));
         return 0;
}

static __exit void exit_hotplug(void){
	
	printk(KERN_INFO "Aditya: Exit from hotplug");
}


module_init(my_spawn_hotplug_threads);
module_exit(exit_hotplug);
