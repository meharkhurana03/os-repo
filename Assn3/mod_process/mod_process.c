#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to get info of a pid"); 
MODULE_AUTHOR("Mehar Khurana");

int process_id;
module_param(process_id, int, 0); // try changing perm
MODULE_PARAM_DESC(process_id, "PID of the process");

static int __init procmod_init(void) {
    struct pid *this_proc_struct = find_get_pid(process_id);
    struct task_struct *this_task_struct = pid_task(this_proc_struct, PIDTYPE_PID);

    printk(KERN_INFO "\nProcess Info:\n");
    printk(KERN_INFO "pid     : %d\n", this_task_struct->pid);
    printk(KERN_INFO "user_id : %d\n", this_task_struct->upid);
    printk(KERN_INFO "pg_id   : %d\n", this_task_struct->pgrp);
    printk(KERN_INFO "comm    : %s\n", this_task_struct->comm);
    return 0;   
}

static void __exit procmod_exit(void) {
    printk(KERN_INFO "-----End-----\n");
}


module_init(procmod_init);      
module_exit(procmod_exit);   