#include "bitop_macros.h"
#include "paste.h"
#include "static_inline.h"

/* **** */

#define __BITOP_PTR_TYPE_REF __BITOP_TYPE *const

#define __BITOP_TYPE_REF const __BITOP_TYPE

/* **** */

#define __BITOP(_) __PASTE(_, __BITOP_BITSv)
#define __BITOPab(_a,_b) __PASTE(__BITOP(_a),_b)

#define __BITOP_FN__(_, ...) \
	__STATIC__ __INLINE__ __attribute__((warn_unused_result)) \
	__BITOP_TYPE _(__BITOP_TYPE_REF v, const unsigned bit, ##__VA_ARGS__)

#define __BITOP_FN(_, ...) __BITOP_FN__(__BITOP(_), ##__VA_ARGS__)

#define __BITOP_FNab(_a,_b, ...) __BITOP_FN__(__BITOPab(_a,_b), ##__VA_ARGS__)

/* **** */

#define __BITOPp(_) __PASTE(__BITOP(_),p)
#define __BITOPp_(_a,_b) __PASTE(__BITOPp(_a),_b)

#define __BITOPp_FN__(_, ...) \
	__STATIC__ __INLINE__ \
	__BITOP_TYPE _(__BITOP_PTR_TYPE_REF v, const unsigned bit, ##__VA_ARGS__)

#define __BITOPp_FN(_, ...) __BITOPp_FN__(__BITOPp(_), ##__VA_ARGS__)

#define __BITOPp_FNab(_a,_b, ...) __BITOPp_FN__(__BITOPp_(_a,_b), ##__VA_ARGS__)

/* **** */

#define __BITOPpp(_) __PASTE(__BITOPp(_),p)
#define __BITOPpp_(_a,_b) __PASTE(__BITOPpp(_a),_b)

#define __BITOPpp_FN__(_, ...) \
	__STATIC__ __INLINE__ \
	__BITOP_TYPE _(void*, __BITOP_PTR_TYPE_REF v, const unsigned bit, ##__VA_ARGS__)

#define __BITOPpp_FN(_, ...) __BITOPpp_FN__(__BITOPpp(_), ##__VA_ARGS__)

#define __BITOPpp_FNab(_a,_b, ...) __BITOPpp_FN__(__BITOPpp_(_a,_b), ##__VA_ARGS__)

/* **** */

__BITOP_FN(bclr) { return(_BCLR(v, bit)); }
__BITOPp_FN(bclr) { return(BCLR(*v, bit)); }
__BITOPpp_FN(bclr) { return(__BITOPp(bclr)(v, bit)); }

__BITOP_FN(bext) { return(_BEXT(v, bit)); }

__BITOP_FN(bmas, const unsigned as) { return(_BMAS(v, bit, as)); }
__BITOPp_FN(bmas, const unsigned as) { return(BMAS(*v, bit, as)); }
__BITOPpp_FN(bmas, const unsigned as) { return(__BITOPp(bmas)(v, bit, as)); }

__STATIC__ __INLINE__ __attribute__((warn_unused_result))
__BITOP_TYPE __BITOP(bmov)(__BITOP_TYPE_REF v, const unsigned from, const unsigned to)
{ return(_BMOV(v, from, to)); }

__BITOP_FN(bset) { return(_BSET(v, bit)); }
__BITOPp_FN(bset) { return(BSET(*v, bit)); }
__BITOPpp_FN(bset) { return(__BITOPp(bset)(v, bit)); }

__BITOP_FNab(bset,_as, const unsigned as) { return(_BSET_AS(v, bit, as)); }
__BITOPp_FNab(bset,_as, const unsigned as) { return(BSET_AS(*v, bit, as)); }
__BITOPpp_FNab(bset,_as, const unsigned as) { return(__BITOPp_(bset,_as)(v, bit, as)); }

__BITOP_FN(btst) { return(_BTST(v, bit)); }

__STATIC__ __INLINE__ __attribute__((warn_unused_result))
__BITOP_TYPE __BITOP(bxmi)(__BITOP_TYPE_REF dst, const unsigned dst_bit, __BITOP_TYPE_REF src, const unsigned src_bit)
{ return(_BXMI(dst, dst_bit, src, src_bit)); }

__STATIC__ __INLINE__
__BITOP_TYPE __BITOPp(bxmi)(__BITOP_PTR_TYPE_REF dst, const unsigned dst_bit, __BITOP_TYPE_REF src, const unsigned src_bit)
{ return(BXMI(*dst, dst_bit, src, src_bit)); }

__BITOP_FN(bxor) { return(_BXOR(v, bit)); }
__BITOPp_FN(bxor) { return(BXOR(*v, bit)); }
__BITOPpp_FN(bxor) { return(__BITOPp(bxor)(v, bit)); }

#include "bitops_undef.h"
