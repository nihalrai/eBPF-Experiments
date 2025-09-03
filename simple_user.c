#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "simple.bpf.skel.h"

static volatile sig_atomic_t exiting = 0;

void sig_handler(int sig){
    exiting = 1;
}

int main(int argc, char **argv){
    struct simple_bpf *skel;
    int err;

    // Register signal handler to exit gracefully
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    // Load BPF program
    skel = simple_bpf__open_and_load();
    if (!skel){
        fprintf(stderr, "Failed to open and load BPF skeleton");
        return 1;
    }

    // Attach the BPF program to its tracepoint
    err = simple_bpf__attach(skel);
    if (err){
        fprintf(stderr, "Failed to attach BPF skeleton");
    }

    printf("Successfully started! waiting for events, Do a ctrl+C to exit\n");

    while (!exiting){
        sleep(1);
    }

    cleanup:
        simple_bpf__destroy(skel);
        return err < 0 ? -err : 0;
}