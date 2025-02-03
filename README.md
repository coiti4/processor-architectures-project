# Processor Architecture & Memory Hierarchy

This repository focuses on various aspects of **processor architecture**—from reading the CPU Time Stamp Counter (TSC) to simulating caches and TLBs, and analyzing MIPS assembly pipeline behavior. It is divided into four main parts:

1. [TSC_Utilities](#1-tsc_utilities)  
2. [Matrix_Operations](#2-matrix_operations)  
3. [MIPS_Pipeline_Examples](#3-mips_pipeline_examples)  
4. [Cache_TLB_Simulation](#4-cache_tlb_simulation)

## Repository Structure

```
PROCESSOR_ARCHITECTURE/
├─ .vscode/
│   └─ tasks.json
├─ latex/
│   ├─ main.tex
│   ├─ ref.bib
│   ├─ ...
│   └─ (LaTeX sources for the report)
├─ html/
├─ TSC_Utilities/
│   ├─ main.c
│   ├─ tsc_test.elf
│   ├─ tsc.c
│   └─ tsc.h
├─ Matrix_Operations/
│   ├─ main.c
│   ├─ matrix_ops.c
│   ├─ matrix_ops.h
│   ├─ Makefile
│   └─ matrix.elf
├─ MIPS_Pipeline_Examples/
│   ├─ sum.s
│   ├─ sumf.s
│   ├─ mul.s
│   ├─ mulf.s
│   ├─ divf.s
│   ├─ abs.s
│   ├─ double.s
│   ├─ fib.s
│   ├─ daxpy.s
│   ├─ power_naive.s
│   └─ power_binary.s
├─ Cache_TLB_Simulation/
│   ├─ cache_tlb_sim.h
│   ├─ cache_tlb_sim.c
│   ├─ simulate_cache.c
│   └─ (other simulation helpers if needed)
├─ .gitignore
├─ Doxyfile
└─ README.md
```

## 1. TSC_Utilities

**Location**: `TSC_Utilities/`  
**Description**: Provides code to read the processor’s Time Stamp Counter (TSC).

- **`tsc.c` / `tsc.h`**: Helper functions (`start_timer()`, `stop_timer()`, `dtime()`) for cycle-accurate timing.
- **`main.c`**: Example usage of the TSC utilities.

### How to Build (Example)

```bash
cd TSC_Utilities
gcc -o tsc_test main.c tsc.c -O2
./tsc_test
```

## 2. Matrix_Operations

**Location:** `Matrix_Operations/`
**Description:** C code for basic linear algebra operations (copy, add, dot product, matrix multiply) with TSC-based performance measurement.

    **Key files:**
        **`main.c`**, **`matrix_ops.c`**, **`matrix_ops.h`**
        Makefile producing **`matrix.elf`**
    **Functions:**
        **`copy_ij()`**, **`copy_ji()`**, **`add_ij()`**, **`add_ji()`**
        **`ps() (dot product)
        **`mm_ijk()`**, **`mm_ikj()`**, **`mm_b_ijk()`** (matrix multiplication strategies)

### How to Build

Using the provided Makefile:
```bash
cd Matrix_Operations
make
./matrix.elf
```
Or compile manually:
```bash
gcc -O2 -I../TSC_Utilities main.c matrix_ops.c ../TSC_Utilities/tsc.c -o matrix.elf -lm
./matrix.elf
```

## 3. MIPS_Pipeline_Examples


