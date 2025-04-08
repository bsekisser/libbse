#pragma once

#define PAGE(_x)		((_x) >> PAGE_SHIFT)
#define PAGES(_x)		(PAGE_ALIGN(_x) >> PAGE_SHIFT)
#define PAGE_ALIGN(_x)	(((_x) + PAGE_OFFSET_MASK) & PAGE_MASK)
#define PAGE_MASK		(~PAGE_OFFSET_MASK)
#define PAGE_OFFSET(_x) ((_x) & PAGE_OFFSET_MASK)
#define PAGE_OFFSET_MASK (PAGE_SIZE - 1)
#define PAGE_SHIFT		12
#define PAGE_SIZE		(1U << PAGE_SHIFT)

#define PTD(_x) ((PAGE(_x) >> PTE_BITS) & PTD_MASK)

#ifndef PTD_BITS
	#define PTD_BITS 10
#endif

#define PTD_MASK (PTD_SIZE - 1)
#define PTD_SIZE (1U << PTD_BITS)

#define PTE(_x) (PAGE(_x) & PTE_MASK)

#ifndef PTE_BITS
	#define PTE_BITS 10
#endif

#define PTE_MASK (PTE_SIZE - 1)
#define PTE_SIZE (1U << PTE_BITS)
