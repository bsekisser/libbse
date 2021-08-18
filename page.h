#define PAGE_SHIFT		12
#define PAGE_SIZE		(1UL << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))
#define PAGE_ALIGN(_x)	(((_x) + PAGE_SIZE - 1) & PAGE_MASK)
#define PAGES(_x)		(PAGE_ALIGN(_x) >> PAGE_SHIFT)
