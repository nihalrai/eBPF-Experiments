#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
    bpf_printk("Hey, A new process is being executed\n");
    return 0;
}

char LICENSE[] SEC("license") = "GPL";