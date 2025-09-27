#pragma once

#define KE_EXPAND(x) x
#define KE_CAT(a,b) KE_CAT_I(a,b)
#define KE_CAT_I(a,b) a##b

#define KE_1(WHAT, X) WHAT(X)
#define KE_2(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_1(WHAT, __VA_ARGS__))
#define KE_3(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_2(WHAT, __VA_ARGS__))
#define KE_4(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_3(WHAT, __VA_ARGS__))
#define KE_5(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_4(WHAT, __VA_ARGS__))
#define KE_6(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_5(WHAT, __VA_ARGS__))
#define KE_7(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_6(WHAT, __VA_ARGS__))
#define KE_8(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_7(WHAT, __VA_ARGS__))
#define KE_9(WHAT, X, ...) WHAT(X),     KE_EXPAND(KE_8(WHAT, __VA_ARGS__))
#define KE_10(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_9(WHAT, __VA_ARGS__))
#define KE_11(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_10(WHAT, __VA_ARGS__))
#define KE_12(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_11(WHAT, __VA_ARGS__))
#define KE_13(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_12(WHAT, __VA_ARGS__))
#define KE_14(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_13(WHAT, __VA_ARGS__))
#define KE_15(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_14(WHAT, __VA_ARGS__))
#define KE_16(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_15(WHAT, __VA_ARGS__))
#define KE_17(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_16(WHAT, __VA_ARGS__))
#define KE_18(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_17(WHAT, __VA_ARGS__))
#define KE_19(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_18(WHAT, __VA_ARGS__))
#define KE_20(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_19(WHAT, __VA_ARGS__))
#define KE_21(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_20(WHAT, __VA_ARGS__))
#define KE_22(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_21(WHAT, __VA_ARGS__))
#define KE_23(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_22(WHAT, __VA_ARGS__))
#define KE_24(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_23(WHAT, __VA_ARGS__))
#define KE_25(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_24(WHAT, __VA_ARGS__))
#define KE_26(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_25(WHAT, __VA_ARGS__))
#define KE_27(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_26(WHAT, __VA_ARGS__))
#define KE_28(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_27(WHAT, __VA_ARGS__))
#define KE_29(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_28(WHAT, __VA_ARGS__))
#define KE_30(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_29(WHAT, __VA_ARGS__))
#define KE_31(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_30(WHAT, __VA_ARGS__))
#define KE_32(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_31(WHAT, __VA_ARGS__))
#define KE_33(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_32(WHAT, __VA_ARGS__))
#define KE_34(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_33(WHAT, __VA_ARGS__))
#define KE_35(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_34(WHAT, __VA_ARGS__))
#define KE_36(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_35(WHAT, __VA_ARGS__))
#define KE_37(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_36(WHAT, __VA_ARGS__))
#define KE_38(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_37(WHAT, __VA_ARGS__))
#define KE_39(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_38(WHAT, __VA_ARGS__))
#define KE_40(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_39(WHAT, __VA_ARGS__))
#define KE_41(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_40(WHAT, __VA_ARGS__))
#define KE_42(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_41(WHAT, __VA_ARGS__))
#define KE_43(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_42(WHAT, __VA_ARGS__))
#define KE_44(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_43(WHAT, __VA_ARGS__))
#define KE_45(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_44(WHAT, __VA_ARGS__))
#define KE_46(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_45(WHAT, __VA_ARGS__))
#define KE_47(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_46(WHAT, __VA_ARGS__))
#define KE_48(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_47(WHAT, __VA_ARGS__))
#define KE_49(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_48(WHAT, __VA_ARGS__))
#define KE_50(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_49(WHAT, __VA_ARGS__))
#define KE_51(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_50(WHAT, __VA_ARGS__))
#define KE_52(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_51(WHAT, __VA_ARGS__))
#define KE_53(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_52(WHAT, __VA_ARGS__))
#define KE_54(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_53(WHAT, __VA_ARGS__))
#define KE_55(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_54(WHAT, __VA_ARGS__))
#define KE_56(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_55(WHAT, __VA_ARGS__))
#define KE_57(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_56(WHAT, __VA_ARGS__))
#define KE_58(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_57(WHAT, __VA_ARGS__))
#define KE_59(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_58(WHAT, __VA_ARGS__))
#define KE_60(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_59(WHAT, __VA_ARGS__))
#define KE_61(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_60(WHAT, __VA_ARGS__))
#define KE_62(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_61(WHAT, __VA_ARGS__))
#define KE_63(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_62(WHAT, __VA_ARGS__))
#define KE_64(WHAT, X, ...) WHAT(X),    KE_EXPAND(KE_63(WHAT, __VA_ARGS__))


#define GET_KE_MACRO(                                                                                                               \
    _1,     _2,     _3,     _4,     _5,     _6,     _7,     _8,     _9,     _10,    _11,    _12,    _13,    _14,    _15,    _16,    \
    _17,    _18,    _19,    _20,    _21,    _22,    _23,    _24,    _25,    _26,    _27,    _28,    _29,    _30,    _31,    _32,    \
    _33,    _34,    _35,    _36,    _37,    _38,    _39,    _40,    _41,    _42,    _43,    _44,    _45,    _46,    _47,    _48,    \
    _49,    _50,    _51,    _52,    _53,    _54,    _55,    _56,    _57,    _58,    _59,    _60,    _61,    _62,    _63,    _64,    \
    NAME, ...) NAME

#define KE_FOR_EACH(WHAT, ...)                                                                                      \
    KE_EXPAND(GET_KE_MACRO(__VA_ARGS__,                                                                             \
    KE_64, KE_63, KE_62, KE_61, KE_60, KE_59, KE_58, KE_57, KE_56, KE_55, KE_54, KE_53, KE_52, KE_51, KE_50, KE_49, \
    KE_48, KE_47, KE_46, KE_45, KE_44, KE_43, KE_42, KE_41, KE_40, KE_39, KE_38, KE_37, KE_36, KE_35, KE_34, KE_33, \
    KE_32, KE_31, KE_30, KE_29, KE_28, KE_27, KE_26, KE_25, KE_24, KE_23, KE_22, KE_21, KE_20, KE_19, KE_18, KE_17, \
    KE_16, KE_15, KE_14, KE_13, KE_12, KE_11, KE_10, KE_9,  KE_8,  KE_7,  KE_6,  KE_5,  KE_4,  KE_3,  KE_2,  KE_1)  \
    (WHAT, __VA_ARGS__))

#define STRIZE(x) #x