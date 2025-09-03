CLANG ?= clang
BPFTOOL ?= bpftool

TARGETS = simple

all: $(TARGETS)

# Rule to compile the BPF program
simple.bpf.o: simple.c
	$(CLANG) -g -O2 -target bpf -c $< -o $@

# Rule to generate the skeleton BPF
simple.bpf.skel.h: simple.bpf.o
	$(BPFTOOL) gen skeleton $< > $@

# Rule to compile the user space loader
simple: simple.c simple.bpf.skel.h
	$(CLANG) -Wall -o $@ $< -lbpf

clean:
	rm -f $(TARGETS)  *.o *.skel.h