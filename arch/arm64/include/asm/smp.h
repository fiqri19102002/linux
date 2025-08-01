/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

#include <linux/const.h>

/* Values for secondary_data.status */
#define CPU_STUCK_REASON_SHIFT		(8)
#define CPU_BOOT_STATUS_MASK		((UL(1) << CPU_STUCK_REASON_SHIFT) - 1)

#define CPU_MMU_OFF			(-1)
#define CPU_BOOT_SUCCESS		(0)
/* The cpu invoked ops->cpu_die, synchronise it with cpu_kill */
#define CPU_KILL_ME			(1)
/* The cpu couldn't die gracefully and is looping in the kernel */
#define CPU_STUCK_IN_KERNEL		(2)
/* Fatal system error detected by secondary CPU, crash the system */
#define CPU_PANIC_KERNEL		(3)

#define CPU_STUCK_REASON_52_BIT_VA	(UL(1) << CPU_STUCK_REASON_SHIFT)
#define CPU_STUCK_REASON_NO_GRAN	(UL(2) << CPU_STUCK_REASON_SHIFT)

#ifndef __ASSEMBLY__

#include <linux/threads.h>
#include <linux/cpumask.h>
#include <linux/thread_info.h>

#define raw_smp_processor_id() (current_thread_info()->cpu)

/*
 * Logical CPU mapping.
 */
extern u64 __cpu_logical_map[NR_CPUS];
extern u64 cpu_logical_map(unsigned int cpu);

static inline void set_cpu_logical_map(unsigned int cpu, u64 hwid)
{
	__cpu_logical_map[cpu] = hwid;
}

struct seq_file;

/*
 * Discover the set of possible CPUs and determine their
 * SMP operations.
 */
extern void smp_init_cpus(void);

enum ipi_msg_type {
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_CPU_STOP_NMI,
	IPI_TIMER,
	IPI_IRQ_WORK,
	NR_IPI,
	/*
	 * Any enum >= NR_IPI and < MAX_IPI is special and not tracable
	 * with trace_ipi_*
	 */
	IPI_CPU_BACKTRACE = NR_IPI,
	IPI_KGDB_ROUNDUP,
	MAX_IPI
};

/*
 * Register IPI interrupts with the arch SMP code
 */
extern void set_smp_ipi_range_percpu(int ipi_base, int nr_ipi, int ncpus);

static inline void set_smp_ipi_range(int ipi_base, int n)
{
	set_smp_ipi_range_percpu(ipi_base, n, 0);
}

/*
 * Called from the secondary holding pen, this is the secondary CPU entry point.
 */
asmlinkage void secondary_start_kernel(void);

/*
 * Initial data for bringing up a secondary CPU.
 * @status - Result passed back from the secondary CPU to
 *           indicate failure.
 */
struct secondary_data {
	struct task_struct *task;
	long status;
};

extern struct secondary_data secondary_data;
extern long __early_cpu_boot_status;
extern void secondary_entry(void);

extern void arch_send_call_function_single_ipi(int cpu);
extern void arch_send_call_function_ipi_mask(const struct cpumask *mask);

#ifdef CONFIG_ARM64_ACPI_PARKING_PROTOCOL
extern void arch_send_wakeup_ipi(unsigned int cpu);
#else
static inline void arch_send_wakeup_ipi(unsigned int cpu)
{
	BUILD_BUG();
}
#endif

extern int __cpu_disable(void);

static inline void __cpu_die(unsigned int cpu) { }
extern void __noreturn cpu_die(void);
extern void __noreturn cpu_die_early(void);

static inline void __noreturn cpu_park_loop(void)
{
	for (;;) {
		wfe();
		wfi();
	}
}

static inline void update_cpu_boot_status(int val)
{
	WRITE_ONCE(secondary_data.status, val);
	/* Ensure the visibility of the status update */
	dsb(ishst);
}

/*
 * The calling secondary CPU has detected serious configuration mismatch,
 * which calls for a kernel panic. Update the boot status and park the calling
 * CPU.
 */
static inline void __noreturn cpu_panic_kernel(void)
{
	update_cpu_boot_status(CPU_PANIC_KERNEL);
	cpu_park_loop();
}

/*
 * If a secondary CPU enters the kernel but fails to come online,
 * (e.g. due to mismatched features), and cannot exit the kernel,
 * we increment cpus_stuck_in_kernel and leave the CPU in a
 * quiesecent loop within the kernel text. The memory containing
 * this loop must not be re-used for anything else as the 'stuck'
 * core is executing it.
 *
 * This function is used to inhibit features like kexec and hibernate.
 */
bool cpus_are_stuck_in_kernel(void);

extern void crash_smp_send_stop(void);
extern bool smp_crash_stop_failed(void);

#endif /* ifndef __ASSEMBLY__ */

#endif /* ifndef __ASM_SMP_H */
