#pragma once

#if _HAS_CXX17
#define CONSTEXPR_INLINE inline
#define NODISC					[[nodiscard]]
#define NODISC_MSG(warnMessage)	[[nodiscard(warnMessage)]]
#else
#define CONSTEXPR_INLINE
#define NODISC
#define NODISC_MSG(warnMessage)
#endif

#define KE_COMMA()      ,
#define KE_SEMICOLON()  ;

#define KE_EXPAND(x) x
#define KE_CAT_I(a,b) a##b
#define KE_CAT(a,b) KE_CAT_I(a,b)

#define KE_1(WHAT,  SEP, X) WHAT(X)
#define KE_2(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_1(WHAT,  SEP, __VA_ARGS__))
#define KE_3(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_2(WHAT,  SEP, __VA_ARGS__))
#define KE_4(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_3(WHAT,  SEP, __VA_ARGS__))
#define KE_5(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_4(WHAT,  SEP, __VA_ARGS__))
#define KE_6(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_5(WHAT,  SEP, __VA_ARGS__))
#define KE_7(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_6(WHAT,  SEP, __VA_ARGS__))
#define KE_8(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_7(WHAT,  SEP, __VA_ARGS__))
#define KE_9(WHAT,  SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_8(WHAT,  SEP, __VA_ARGS__))
#define KE_10(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_9(WHAT,  SEP, __VA_ARGS__))
#define KE_11(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_10(WHAT, SEP, __VA_ARGS__))
#define KE_12(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_11(WHAT, SEP, __VA_ARGS__))
#define KE_13(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_12(WHAT, SEP, __VA_ARGS__))
#define KE_14(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_13(WHAT, SEP, __VA_ARGS__))
#define KE_15(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_14(WHAT, SEP, __VA_ARGS__))
#define KE_16(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_15(WHAT, SEP, __VA_ARGS__))
#define KE_17(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_16(WHAT, SEP, __VA_ARGS__))
#define KE_18(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_17(WHAT, SEP, __VA_ARGS__))
#define KE_19(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_18(WHAT, SEP, __VA_ARGS__))
#define KE_20(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_19(WHAT, SEP, __VA_ARGS__))
#define KE_21(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_20(WHAT, SEP, __VA_ARGS__))
#define KE_22(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_21(WHAT, SEP, __VA_ARGS__))
#define KE_23(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_22(WHAT, SEP, __VA_ARGS__))
#define KE_24(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_23(WHAT, SEP, __VA_ARGS__))
#define KE_25(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_24(WHAT, SEP, __VA_ARGS__))
#define KE_26(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_25(WHAT, SEP, __VA_ARGS__))
#define KE_27(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_26(WHAT, SEP, __VA_ARGS__))
#define KE_28(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_27(WHAT, SEP, __VA_ARGS__))
#define KE_29(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_28(WHAT, SEP, __VA_ARGS__))
#define KE_30(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_29(WHAT, SEP, __VA_ARGS__))
#define KE_31(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_30(WHAT, SEP, __VA_ARGS__))
#define KE_32(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_31(WHAT, SEP, __VA_ARGS__))
#define KE_33(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_32(WHAT, SEP, __VA_ARGS__))
#define KE_34(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_33(WHAT, SEP, __VA_ARGS__))
#define KE_35(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_34(WHAT, SEP, __VA_ARGS__))
#define KE_36(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_35(WHAT, SEP, __VA_ARGS__))
#define KE_37(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_36(WHAT, SEP, __VA_ARGS__))
#define KE_38(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_37(WHAT, SEP, __VA_ARGS__))
#define KE_39(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_38(WHAT, SEP, __VA_ARGS__))
#define KE_40(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_39(WHAT, SEP, __VA_ARGS__))
#define KE_41(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_40(WHAT, SEP, __VA_ARGS__))
#define KE_42(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_41(WHAT, SEP, __VA_ARGS__))
#define KE_43(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_42(WHAT, SEP, __VA_ARGS__))
#define KE_44(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_43(WHAT, SEP, __VA_ARGS__))
#define KE_45(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_44(WHAT, SEP, __VA_ARGS__))
#define KE_46(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_45(WHAT, SEP, __VA_ARGS__))
#define KE_47(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_46(WHAT, SEP, __VA_ARGS__))
#define KE_48(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_47(WHAT, SEP, __VA_ARGS__))
#define KE_49(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_48(WHAT, SEP, __VA_ARGS__))
#define KE_50(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_49(WHAT, SEP, __VA_ARGS__))
#define KE_51(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_50(WHAT, SEP, __VA_ARGS__))
#define KE_52(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_51(WHAT, SEP, __VA_ARGS__))
#define KE_53(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_52(WHAT, SEP, __VA_ARGS__))
#define KE_54(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_53(WHAT, SEP, __VA_ARGS__))
#define KE_55(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_54(WHAT, SEP, __VA_ARGS__))
#define KE_56(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_55(WHAT, SEP, __VA_ARGS__))
#define KE_57(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_56(WHAT, SEP, __VA_ARGS__))
#define KE_58(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_57(WHAT, SEP, __VA_ARGS__))
#define KE_59(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_58(WHAT, SEP, __VA_ARGS__))
#define KE_60(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_59(WHAT, SEP, __VA_ARGS__))
#define KE_61(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_60(WHAT, SEP, __VA_ARGS__))
#define KE_62(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_61(WHAT, SEP, __VA_ARGS__))
#define KE_63(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_62(WHAT, SEP, __VA_ARGS__))
#define KE_64(WHAT, SEP, X, ...) WHAT(X) SEP() KE_EXPAND(KE_63(WHAT, SEP, __VA_ARGS__))

#define GET_KE_MACRO(                                                                                                               \
    _1,     _2,     _3,     _4,     _5,     _6,     _7,     _8,     _9,     _10,    _11,    _12,    _13,    _14,    _15,    _16,    \
    _17,    _18,    _19,    _20,    _21,    _22,    _23,    _24,    _25,    _26,    _27,    _28,    _29,    _30,    _31,    _32,    \
    _33,    _34,    _35,    _36,    _37,    _38,    _39,    _40,    _41,    _42,    _43,    _44,    _45,    _46,    _47,    _48,    \
    _49,    _50,    _51,    _52,    _53,    _54,    _55,    _56,    _57,    _58,    _59,    _60,    _61,    _62,    _63,    _64,    \
    NAME, ...) NAME

#define KE_FOR_EACH(WHAT, SEPARATOR, ...)                                                                           \
    KE_EXPAND(GET_KE_MACRO(__VA_ARGS__,                                                                             \
    KE_64, KE_63, KE_62, KE_61, KE_60, KE_59, KE_58, KE_57, KE_56, KE_55, KE_54, KE_53, KE_52, KE_51, KE_50, KE_49, \
    KE_48, KE_47, KE_46, KE_45, KE_44, KE_43, KE_42, KE_41, KE_40, KE_39, KE_38, KE_37, KE_36, KE_35, KE_34, KE_33, \
    KE_32, KE_31, KE_30, KE_29, KE_28, KE_27, KE_26, KE_25, KE_24, KE_23, KE_22, KE_21, KE_20, KE_19, KE_18, KE_17, \
    KE_16, KE_15, KE_14, KE_13, KE_12, KE_11, KE_10, KE_9,  KE_8,  KE_7,  KE_6,  KE_5,  KE_4,  KE_3,  KE_2,  KE_1)  \
    (WHAT, SEPARATOR, __VA_ARGS__))

#define STRIZE(x) #x

#define INVALID_INDEX(T) static_cast<T>(-1)

#define DELETE_COPYABLE(ClassName)						\
	ClassName(const ClassName&) = delete;				\
	ClassName& operator=(const ClassName&) = delete;	

#define DELETE_MOVEABLE(ClassName)				\
	ClassName(ClassName&&) = delete;			\
	ClassName& operator=(ClassName&&) = delete;

#define NONCOPYABLE(ClassName)	\
	DELETE_COPYABLE(ClassName)	\
	DELETE_MOVEABLE(ClassName)

#define DELETE_CONSTRUCTOR(ClassName)	\
	ClassName() = delete;				\
	NONCOPYABLE(ClassName)

#define DEFAULT_COPYABLE(ClassName)						\
	ClassName(const ClassName&) = default;				\
	ClassName& operator=(const ClassName&) = default;

#define DEFAULT_MOVEABLE(ClassName)				\
	ClassName(ClassName&&) = default;			\
	ClassName& operator=(ClassName&&) = default;

#define DEFAULTABLE(ClassName)	\
	DEFAULT_COPYABLE(ClassName)	\
	DEFAULT_MOVEABLE(ClassName)