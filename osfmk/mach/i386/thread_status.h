/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	thread_status.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1985
 *
 *	This file contains the structure definitions for the thread
 *	state as applied to I386 processors.
 */

#ifndef	_MACH_I386_THREAD_STATUS_H_
#define _MACH_I386_THREAD_STATUS_H_

#include <mach/i386/_structs.h>
#include <mach/message.h>
#include <mach/i386/fp_reg.h>
#include <mach/i386/thread_state.h>
#include <i386/eflags.h>

/*
 * the i386_xxxx form is kept for legacy purposes since these types
 * are externally known... eventually they should be deprecated.
 * our internal implementation has moved to the following naming convention
 *
 *   x86_xxxx32 names are used to deal with 32 bit states
 *   x86_xxxx64 names are used to deal with 64 bit states
 *   x86_xxxx   names are used to deal with either 32 or 64 bit states
 *	via a self-describing mechanism
 */

/*
 * these are the legacy names which should be deprecated in the future
 * they are externally known which is the only reason we don't just get
 * rid of them
 */
#define i386_THREAD_STATE		1
#define i386_FLOAT_STATE		2
#define i386_EXCEPTION_STATE		3

/*
 * THREAD_STATE_FLAVOR_LIST 0
 * 	these are the supported flavors
 */
#define x86_THREAD_STATE32		1
#define x86_FLOAT_STATE32		2
#define x86_EXCEPTION_STATE32		3
#define x86_THREAD_STATE64		4
#define x86_FLOAT_STATE64		5
#define x86_EXCEPTION_STATE64		6
#define x86_THREAD_STATE		7
#define x86_FLOAT_STATE			8
#define x86_EXCEPTION_STATE		9
#define x86_DEBUG_STATE32		10
#define x86_DEBUG_STATE64		11
#define x86_DEBUG_STATE			12
#define THREAD_STATE_NONE		13
/* 15 and 16 are used for the internal x86_SAVED_STATE flavours */
#define x86_AVX_STATE32			16
#define x86_AVX_STATE64			17


/*
 * Largest state on this machine:
 * (be sure mach/machine/thread_state.h matches!)
 */
#define THREAD_MACHINE_STATE_MAX	THREAD_STATE_MAX

/*
 * VALID_THREAD_STATE_FLAVOR is a platform specific macro that when passed
 * an exception flavor will return if that is a defined flavor for that
 * platform. The macro must be manually updated to include all of the valid
 * exception flavors as defined above.
 */
#define VALID_THREAD_STATE_FLAVOR(x)       \
	 ((x == x86_THREAD_STATE32)	|| \
	  (x == x86_FLOAT_STATE32)	|| \
	  (x == x86_EXCEPTION_STATE32)	|| \
	  (x == x86_DEBUG_STATE32)	|| \
	  (x == x86_THREAD_STATE64)	|| \
	  (x == x86_FLOAT_STATE64)	|| \
	  (x == x86_EXCEPTION_STATE64)	|| \
	  (x == x86_DEBUG_STATE64)	|| \
	  (x == x86_THREAD_STATE)	|| \
	  (x == x86_FLOAT_STATE)	|| \
	  (x == x86_EXCEPTION_STATE)	|| \
	  (x == x86_DEBUG_STATE)	|| \
	  (x == x86_AVX_STATE32)	|| \
	  (x == x86_AVX_STATE64)	|| \
	  (x == THREAD_STATE_NONE))

struct x86_state_hdr {
	int	flavor;
	int	count;
};
typedef struct x86_state_hdr x86_state_hdr_t;

/*
 * Default segment register values.
 */
    
#define USER_CODE_SELECTOR	0x0017
#define USER_DATA_SELECTOR	0x001f
#define KERN_CODE_SELECTOR	0x0008
#define KERN_DATA_SELECTOR	0x0010

/*
 * to be deprecated in the future
 */
typedef _STRUCT_X86_THREAD_STATE32 i386_thread_state_t;
#define i386_THREAD_STATE_COUNT	((mach_msg_type_number_t) \
    ( sizeof (i386_thread_state_t) / sizeof (int) ))

typedef _STRUCT_X86_THREAD_STATE32 x86_thread_state32_t;
#define x86_THREAD_STATE32_COUNT	((mach_msg_type_number_t) \
    ( sizeof (x86_thread_state32_t) / sizeof (int) ))

/*
 * to be deprecated in the future
 */
typedef _STRUCT_X86_FLOAT_STATE32 i386_float_state_t;
#define i386_FLOAT_STATE_COUNT ((mach_msg_type_number_t) \
		(sizeof(i386_float_state_t)/sizeof(unsigned int)))

typedef _STRUCT_X86_FLOAT_STATE32 x86_float_state32_t;
#define x86_FLOAT_STATE32_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_float_state32_t)/sizeof(unsigned int)))

typedef _STRUCT_X86_AVX_STATE32 x86_avx_state32_t;
#define x86_AVX_STATE32_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_avx_state32_t)/sizeof(unsigned int)))

/*
 * to be deprecated in the future
 */
typedef _STRUCT_X86_EXCEPTION_STATE32 i386_exception_state_t;
#define i386_EXCEPTION_STATE_COUNT	((mach_msg_type_number_t) \
    ( sizeof (i386_exception_state_t) / sizeof (int) ))

typedef _STRUCT_X86_EXCEPTION_STATE32 x86_exception_state32_t;
#define x86_EXCEPTION_STATE32_COUNT	((mach_msg_type_number_t) \
    ( sizeof (x86_exception_state32_t) / sizeof (int) ))

#define I386_EXCEPTION_STATE_COUNT i386_EXCEPTION_STATE_COUNT

typedef _STRUCT_X86_DEBUG_STATE32 x86_debug_state32_t;
#define x86_DEBUG_STATE32_COUNT       ((mach_msg_type_number_t) \
	( sizeof (x86_debug_state32_t) / sizeof (int) ))

#define X86_DEBUG_STATE32_COUNT x86_DEBUG_STATE32_COUNT

typedef _STRUCT_X86_THREAD_STATE64 x86_thread_state64_t;
#define x86_THREAD_STATE64_COUNT	((mach_msg_type_number_t) \
    ( sizeof (x86_thread_state64_t) / sizeof (int) ))

typedef _STRUCT_X86_FLOAT_STATE64 x86_float_state64_t;
#define x86_FLOAT_STATE64_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_float_state64_t)/sizeof(unsigned int)))

typedef _STRUCT_X86_AVX_STATE64 x86_avx_state64_t;
#define x86_AVX_STATE64_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_avx_state64_t)/sizeof(unsigned int)))

typedef _STRUCT_X86_EXCEPTION_STATE64 x86_exception_state64_t;
#define x86_EXCEPTION_STATE64_COUNT	((mach_msg_type_number_t) \
    ( sizeof (x86_exception_state64_t) / sizeof (int) ))

#define X86_EXCEPTION_STATE64_COUNT x86_EXCEPTION_STATE64_COUNT

typedef _STRUCT_X86_DEBUG_STATE64 x86_debug_state64_t;
#define x86_DEBUG_STATE64_COUNT	((mach_msg_type_number_t) \
    ( sizeof (x86_debug_state64_t) / sizeof (int) ))

#define X86_DEBUG_STATE64_COUNT x86_DEBUG_STATE64_COUNT

/*
 * Combined thread, float and exception states
 */
struct x86_thread_state {
	x86_state_hdr_t			tsh;
	union {
	    x86_thread_state32_t	ts32;
	    x86_thread_state64_t	ts64;
	} uts;
};

struct x86_float_state {
	x86_state_hdr_t			fsh;
	union {
		x86_float_state32_t	fs32;
		x86_float_state64_t	fs64;
	} ufs;
};

struct x86_exception_state {
	x86_state_hdr_t			esh;
	union {
		x86_exception_state32_t	es32;
		x86_exception_state64_t	es64;
	} ues;
};

struct x86_debug_state {
	x86_state_hdr_t			dsh;
	union {
		x86_debug_state32_t	ds32;
		x86_debug_state64_t	ds64;
	} uds;
};

typedef struct x86_thread_state x86_thread_state_t;
#define x86_THREAD_STATE_COUNT	((mach_msg_type_number_t) \
		( sizeof (x86_thread_state_t) / sizeof (int) ))

typedef struct x86_float_state x86_float_state_t;
#define x86_FLOAT_STATE_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_float_state_t)/sizeof(unsigned int)))

typedef struct x86_exception_state x86_exception_state_t;
#define x86_EXCEPTION_STATE_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_exception_state_t)/sizeof(unsigned int)))

typedef struct x86_debug_state x86_debug_state_t;
#define x86_DEBUG_STATE_COUNT ((mach_msg_type_number_t) \
		(sizeof(x86_debug_state_t)/sizeof(unsigned int)))

/*
 * Machine-independent way for servers and Mach's exception mechanism to
 * choose the most efficient state flavor for exception RPC's:
 */
#define MACHINE_THREAD_STATE		x86_THREAD_STATE
#define MACHINE_THREAD_STATE_COUNT	x86_THREAD_STATE_COUNT

/*
 * when reloading the segment registers on
 * a return out of the kernel, we may take
 * a GeneralProtection or SegmentNotPresent
 * fault if one or more of the segment
 * registers in the saved state was improperly
 * specified via an x86_THREAD_STATE32 call
 * the frame we push on top of the existing
 * save area looks like this... we need to
 * carry this as part of the save area
 * in case we get hit so that we have a big
 * enough stack
 */
struct x86_seg_load_fault32 {
	unsigned int    trapno;
	unsigned int    err;
	unsigned int    eip;
	unsigned int    cs;
	unsigned int    efl;
};

#ifdef XNU_KERNEL_PRIVATE

#define x86_SAVED_STATE32		THREAD_STATE_NONE + 1
#define x86_SAVED_STATE64		THREAD_STATE_NONE + 2

/*
 * Subset of saved state stored by processor on kernel-to-kernel
 * trap.  (Used by ddb to examine state guaranteed to be present
 * on all traps into debugger.)
 */
struct x86_saved_state32_from_kernel {
	unsigned int	gs;
	unsigned int	fs;
	unsigned int	es;
	unsigned int	ds;
	unsigned int	edi;
	unsigned int	esi;
	unsigned int	ebp;
	unsigned int	cr2;	/* kernel esp stored by pusha - we save cr2 here later */
	unsigned int	ebx;
	unsigned int	edx;
	unsigned int	ecx;
	unsigned int	eax;
	unsigned int	trapno;
	unsigned int	err;
	unsigned int	eip;
	unsigned int	cs;
	unsigned int	efl;
};

/*
 * The format in which thread state is saved by Mach on this machine.  This
 * state flavor is most efficient for exception RPC's to kernel-loaded
 * servers, because copying can be avoided:
 */
struct x86_saved_state32 {
	unsigned int	gs;
	unsigned int	fs;
	unsigned int	es;
	unsigned int	ds;
	unsigned int	edi;
	unsigned int	esi;
	unsigned int	ebp;
	unsigned int	cr2;	/* kernel esp stored by pusha - we save cr2 here later */
	unsigned int	ebx;
	unsigned int	edx;
	unsigned int	ecx;
	unsigned int	eax;
	unsigned int	trapno;
	unsigned int	err;
	unsigned int	eip;
	unsigned int	cs;
	unsigned int	efl;
	unsigned int	uesp;
	unsigned int	ss;
};
typedef struct x86_saved_state32 x86_saved_state32_t;

#define x86_SAVED_STATE32_COUNT	((mach_msg_type_number_t) \
	(sizeof (x86_saved_state32_t)/sizeof(unsigned int)))

#pragma pack(4)
struct x86_saved_state32_tagged {
	uint32_t			tag;
	struct x86_saved_state32	state;
};
typedef struct x86_saved_state32_tagged x86_saved_state32_tagged_t;

struct x86_sframe32 {
	/*
	 * in case we throw a fault reloading
	 * segment registers on a return out of
	 * the kernel... the 'slf' state is only kept
	 * long enough to rejigger (i.e. restore
	 * the save area to its original state)
	 * the save area and throw the appropriate
	 * kernel trap pointing to the 'ssf' state
	 */
        struct x86_seg_load_fault32	slf;
        struct x86_saved_state32_tagged ssf;
};
typedef struct x86_sframe32 x86_sframe32_t;

/*
 * This is the state pushed onto the 64-bit interrupt stack
 * on any exception/trap/interrupt.
 */
struct x86_64_intr_stack_frame {
	uint32_t	trapno;
#if defined(__LP64__) && defined(KERNEL)
	uint32_t 	_pad;
	uint64_t	trapfn;
#else
	uint32_t	trapfn;
#endif
	uint64_t	err;
	uint64_t	rip;
	uint64_t	cs;
	uint64_t	rflags;
	uint64_t	rsp;
	uint64_t	ss;
};
typedef struct x86_64_intr_stack_frame x86_64_intr_stack_frame_t;

/*
 * This defines the state saved before entry into compatibility mode.
 * The machine state is pushed automatically and the compat state is
 * synthethized in the exception handling code.
 */
struct x86_saved_state_compat32 {
	struct x86_saved_state32_tagged	iss32;
#if defined(__LP64__) && defined(KERNEL)
#else
	uint32_t			pad_for_16byte_alignment[2];
#endif
	struct	x86_64_intr_stack_frame	isf64;
};
typedef struct x86_saved_state_compat32 x86_saved_state_compat32_t;

struct x86_sframe_compat32 {
        struct x86_64_intr_stack_frame  slf;
#if defined(__LP64__) && defined(KERNEL)
#else
	uint32_t	pad_for_16byte_alignment[2];
#endif
        struct x86_saved_state_compat32 ssf;
	uint32_t			empty[4];
};
typedef struct x86_sframe_compat32 x86_sframe_compat32_t;

/*
 * thread state format for task running in 64bit long mode
 * in long mode, the same hardware frame is always pushed regardless
 * of whether there was a change in privlege level... therefore, there
 * is no need for an x86_saved_state64_from_kernel variant
 */
struct x86_saved_state64 {
        /*
	 * saved state organized to reflect the
	 * system call ABI register convention
	 * so that we can just pass a pointer
	 * to the saved state when calling through
	 * to the actual system call functions
	 * the ABI limits us to 6 args passed in 
	 * registers... I've add v_arg6 - v_arg8
	 * to accomodate our most 'greedy' system
	 * calls (both BSD and MACH)... the individual
	 * system call handlers will fill these in
	 * via copyin if needed...
	 */
        uint64_t	rdi;		/* arg0 for system call */
	uint64_t	rsi;
	uint64_t	rdx;
        uint64_t	r10;
        uint64_t	r8;
        uint64_t	r9;		/* arg5 for system call */
        uint64_t	v_arg6;
        uint64_t	v_arg7;
        uint64_t	v_arg8;

        uint64_t	cr2;
        uint64_t	r15;
        uint64_t	r14;
        uint64_t	r13;
        uint64_t	r12;
        uint64_t	r11;
	uint64_t	rbp;
	uint64_t	rbx;
	uint64_t	rcx;
	uint64_t	rax;

	uint32_t	gs;
	uint32_t	fs;
#ifdef __x86_64__
	uint32_t		_pad_for_alignment[3];
#endif
	struct	x86_64_intr_stack_frame	isf;
};
typedef struct x86_saved_state64 x86_saved_state64_t;
#define x86_SAVED_STATE64_COUNT	((mach_msg_type_number_t) \
	(sizeof (struct x86_saved_state64)/sizeof(unsigned int)))

struct x86_saved_state64_tagged {
	uint32_t		tag;
	x86_saved_state64_t	state;
};
typedef struct x86_saved_state64_tagged x86_saved_state64_tagged_t;

struct x86_sframe64 {
        struct x86_64_intr_stack_frame	slf;
#ifdef __i386__
		uint32_t		_pad_for_alignment[3];
#endif
        struct x86_saved_state64_tagged	ssf;
};
typedef struct x86_sframe64 x86_sframe64_t;

extern uint32_t get_eflags_exportmask(void);

/*
 * Unified, tagged saved state:
 */
typedef struct {
	uint32_t			flavor;
	union {
		x86_saved_state32_t	ss_32;
		x86_saved_state64_t	ss_64;
	} uss;
} x86_saved_state_t;
#define	ss_32	uss.ss_32
#define	ss_64	uss.ss_64
#pragma pack()

static inline boolean_t
is_saved_state64(x86_saved_state_t *iss)
{
	return (iss->flavor == x86_SAVED_STATE64);
}

static inline boolean_t
is_saved_state32(x86_saved_state_t *iss)
{
	return (iss->flavor == x86_SAVED_STATE32);
}

static inline x86_saved_state32_t *
saved_state32(x86_saved_state_t *iss)
{
	return &iss->ss_32; 
}

static inline x86_saved_state64_t *
saved_state64(x86_saved_state_t *iss)
{
	return &iss->ss_64; 
}

#endif /* XNU_KERNEL_PRIVATE */

#endif	/* _MACH_I386_THREAD_STATUS_H_ */
