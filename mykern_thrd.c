#include <linux/init_task.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/smpboot.h>

#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)

static void my_kernel_thread_create_1(void);
static void my_kernel_thread_create_2(void);

static void m_k_t_do_something_1(void *);
static void m_k_t_do_something_2(void *);


static void my_kernel_thread_create_1(void){
  int mypid;
  printk(KERN_NOTICE "Aditya: Calling kernel_thread(my_ker_thd_1)\n");
  mypid = kernel_thread(m_k_t_do_something_1, NULL, CLONE_KERNEL);
  printk(KERN_NOTICE "Aditya: my_ker_thd_1 = %d\n", mypid);
}

static void my_kernel_thread_create_2(void){
  int mypid;
  printk(KERN_NOTICE "Aditya: Calling kernel_thread(my_ker_thd_2)\n");
  mypid = kernel_thread(m_k_t_do_something_2, NULL, CLONE_KERNEL);
  printk(KERN_NOTICE "Aditya: my_ker_thd_2 = %d\n", mypid);
}


static void m_k_t_do_something_1(void *){
  struct task_struct *curtask = current;
  strcpy(curtask->comm, "Aditya: m_k_t_do_something_1");
  set_task_state(curtask, TASK_RUNNING);
  printk(KERN_NOTICE "Aditya: m_k_t_do_something_1 is about to be scheduled.\n");
  schedule();
  printk(KERN_NOTICE "Aditya: m_k_t_do_something_1 is now scheduled.\n");
  

}

static void m_k_t_do_something_2(void *){
  struct task_struct *curtask = current;
  strcpy(curtask->comm, "Aditya: m_k_t_do_something_2");
  set_task_state(curtask, TASK_RUNNING);
  printk(KERN_NOTICE "Aditya: m_k_t_do_something_2 is about to be scheduled.\n");
  schedule();
  printk(KERN_NOTICE "Aditya: m_k_t_do_something_2 is now scheduled.\n");
  
}


static int __init mykernel_init(void){
    
    printk(KERN_NOTICE "Aditya: m_k_t_do_something threads are about to be created.\n");
    my_kernel_thread_create_1();
    my_kernel_thread_create_2();
    printk(KERN_NOTICE "Aditya: m_k_t_do_something threads are created.\n");
}




