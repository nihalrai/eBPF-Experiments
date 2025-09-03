#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

/*
SEC("tracepoint....") is a macro, it helps identifies and add exact kernel hook it should be attached to
*/
SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx){
    bpf_printk("Hey, A new process is being executed");
    return 0;
}