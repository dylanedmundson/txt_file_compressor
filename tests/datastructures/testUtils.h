typedef enum PASS_TEST {PASS, FAIL} testPass;
typedef enum boolean {F, T} boolean;

#define PASS_TEST return 0
#define FAIL_TEST return 1
#define ASSERT_EQUALS(A, B)\
    if ((A) != (B)) {\
        return FAIL;\
    }
#define ASSERT_NOT_EQUALS(A, B)\
    if ((A) != (B)) {\
        return PASS;\
    }
#define ASSERT_PASS_TEST(A)\
    if ((A) == PASS) {\
        PASS_TEST;\
    } else {\
        FAIL_TEST;\
    }