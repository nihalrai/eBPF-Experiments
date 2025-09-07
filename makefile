CLANG ?= clang
BPFTOOL ?= bpftool

TARGETS = simple

all: $(TARGETS)

# Rule to compile the BPF program
simple.bpf.o: simple.c
	$(CLANG) -g -O2 -target bpf -mcpu=v3 -fno-stack-protector -fno-builtin -c $< -o $@

# Rule to generate the skeleton BPF
simple.bpf.skel.h: simple.bpf.o
	$(BPFTOOL) gen skeleton $< > $@

# Rule to compile the user space loader
simple: simple_user.c simple.bpf.skel.h simple.bpf.o
	$(CLANG) -Wall -o $@ simple_user.c -lbpf -lz

clean:
	rm -f $(TARGETS) *.o *.skel.h

.PHONY: clean
