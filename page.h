#pragma once

#define PAGE(_x)		((_x) >> PAGE_SHIFT)
#define PAGES(_x)		(PAGE_ALIGN(_x) >> PAGE_SHIFT)
#define PAGE_ALIGN(_x)	(((_x) + PAGE_SIZE - 1) & PAGE_MASK)
#define PAGE_MASK		(~(PAGE_SIZE - 1))
#define PAGE_OFFSET(_x) ((_x) & (PAGE_SIZE - 1))
#define PAGE_SHIFT		12
#define PAGE_SIZE		(1U << PAGE_SHIFT)
