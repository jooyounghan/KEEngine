#pragma once

#ifdef _DEBUG
#define KE_DEV
#define KE_NATVIS
#endif

#if _HAS_CXX17
#define CONSTEXPR_INLINE inline
#else
#define CONSTEXPR_INLINE

#endif

#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(maybe_unused)
#define KE_MAYBE_UNUSED [[maybe_unused]]
#else
#define KE_MAYBE_UNUSED
#endif
#if __has_cpp_attribute(nodiscard)
#define NODISC					[[nodiscard]]
#define NODISC_MSG(warnMessage)	[[nodiscard(warnMessage)]]
#else
#define NODISC
#define NODISC_MSG(warnMessage)
#endif
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

#define KE_1T(WHAT,  SEP, FIXED, X) WHAT(FIXED, X)
#define KE_2T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_1T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_3T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_2T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_4T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_3T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_5T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_4T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_6T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_5T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_7T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_6T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_8T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_7T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_9T(WHAT,  SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_8T(WHAT,  SEP, FIXED, __VA_ARGS__))
#define KE_10T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_9T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_11T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_10T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_12T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_11T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_13T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_12T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_14T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_13T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_15T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_14T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_16T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_15T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_17T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_16T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_18T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_17T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_19T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_18T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_20T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_19T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_21T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_20T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_22T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_21T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_23T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_22T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_24T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_23T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_25T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_24T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_26T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_25T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_27T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_26T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_28T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_27T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_29T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_28T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_30T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_29T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_31T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_30T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_32T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_31T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_33T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_32T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_34T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_33T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_35T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_34T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_36T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_35T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_37T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_36T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_38T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_37T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_39T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_38T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_40T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_39T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_41T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_40T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_42T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_41T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_43T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_42T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_44T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_43T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_45T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_44T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_46T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_45T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_47T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_46T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_48T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_47T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_49T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_48T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_50T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_49T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_51T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_50T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_52T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_51T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_53T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_52T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_54T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_53T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_55T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_54T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_56T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_55T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_57T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_56T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_58T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_57T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_59T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_58T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_60T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_59T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_61T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_60T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_62T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_61T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_63T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_62T(WHAT, SEP, FIXED, __VA_ARGS__))
#define KE_64T(WHAT, SEP, FIXED, X, ...) WHAT(FIXED, X) SEP() KE_EXPAND(KE_63T(WHAT, SEP, FIXED, __VA_ARGS__))



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

#define KE_FOR_EACH_WITH_FIXED(WHAT, SEPARATOR, FIXED, ...)                                                                                       \
    KE_EXPAND(GET_KE_MACRO(__VA_ARGS__,                                                                                             \
    KE_64T, KE_63T, KE_62T, KE_61T, KE_60T, KE_59T, KE_58T, KE_57T, KE_56T, KE_55T, KE_54T, KE_53T, KE_52T, KE_51T, KE_50T, KE_49T, \
    KE_48T, KE_47T, KE_46T, KE_45T, KE_44T, KE_43T, KE_42T, KE_41T, KE_40T, KE_39T, KE_38T, KE_37T, KE_36T, KE_35T, KE_34T, KE_33T, \
    KE_32T, KE_31T, KE_30T, KE_29T, KE_28T, KE_27T, KE_26T, KE_25T, KE_24T, KE_23T, KE_22T, KE_21T, KE_20T, KE_19T, KE_18T, KE_17T, \
    KE_16T, KE_15T, KE_14T, KE_13T, KE_12T, KE_11T, KE_10T, KE_9T,  KE_8T,  KE_7T,  KE_6T,  KE_5T,  KE_4T,  KE_3T,  KE_2T,  KE_1T)  \
    (WHAT, SEPARATOR, FIXED, __VA_ARGS__))

#define STRIZE(x) #x

#define KE_CAST_TO(T, x) static_cast<T>(x)

#define INVALID_INDEX(T) KE_CAST_TO(T, -1)

#define DELETE_DEFAULT_CONSTRUCTOR(ClassName)	\
	ClassName() = delete

#define DELETE_COPYABLE(ClassName)						\
	ClassName(const ClassName&) = delete;				\
	ClassName& operator=(const ClassName&) = delete	

#define DELETE_MOVEABLE(ClassName)				\
	ClassName(ClassName&&) = delete;			\
	ClassName& operator=(ClassName&&) = delete

#define NONCOPYABLE(ClassName)	\
	DELETE_COPYABLE(ClassName);	\
	DELETE_MOVEABLE(ClassName)

#define DELETE_CONSTRUCTOR(ClassName)		\
	DELETE_DEFAULT_CONSTRUCTOR(ClassName);	\
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