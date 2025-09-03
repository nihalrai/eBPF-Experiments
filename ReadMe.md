# Small notes for code reference

## eBPF
```code
It is moer like a virtual sandbox where you can run an user space program within kernel space (?).
It helps extend functionality, collect special data, invoke on special events.

Small use in Graphics is profiler, inject the uprobes (user space probes) to an graphics API runtime library
or a graphics driver, then start collecing drawcalls or memory allocation (alloc, free), data movement between 
GPU and CPU, collect hardware counters (use perf_events in linux, window you may need to use Performance Monitor tool
like event tracing for windows, mostly used in DX drivers?, Thats a seprate topic to Cover, like consumer, controllers, providers)

Another broad level topic is PMU (for hardware counters specifically), its built in a processor itself, to measure instruction cycles,
cache hits, miss (the WinPIX profilers tags, i known :),  you can use the processor libs/dlls with api calls to perform your tool requirements.

LLVM can be used here, like to create a compiler for eBPF bytecode, but clang already does and unless you want something specific, clang or gcc
is far better to use for compilation of eBPF code.
```

## Flow

> Write an eBPF code, adhere to guidelines, with making sure it passes the verifier check on eBPF to not crash the system.

> Compile it, example command is like: clang -O2 -g -target bpf -c source.c -o source.o

> If want to check the raw bytecode: bpftool prog dump xlated file source.o

> The binary format has its own specificaiton, BTF type (BPF Type Format), To load it, follow below steps

```code
- Compile again and generate skeleton (c header file) from source.o, It just simplify the source code (user space) to make it
  callable via other programs that will use this source.o for the tooling, requirements. This helps avoid low level system calls
  of bpf()
```

## Code Content

> Once source code named simple.c is just a call if a new process is called.

> Another is a lightweight eBPF program and python use case (just a mixture)

Thanks 