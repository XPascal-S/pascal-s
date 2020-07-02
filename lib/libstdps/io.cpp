//
// Created by kamiyoru on 2020/5/9.
//

#include <cstdio>
#include <cstdint>

#ifdef _WIN32
#define LL_FMT "%I64d"
#else
#define LL_FMT "%lld"
#endif
extern "C" {

int read_char(char *s) {
    return scanf("%c", s);
}

int read_bool(char *s) {
    int bool_input;
    int si = scanf("%d", &bool_input);
    if (bool_input != 0) { *s = 1; } else { *s = 0; }
    return si;
}

int read_int64(int64_t *s) {
    return scanf(LL_FMT, s);
}

int read_int32(int32_t *s) {
    return scanf("%d", s);
}

int read_real(double *s) {
    return scanf("%lf", s);
}

int write_char(char s) {
    return printf("%c", s);
}

int write_bool(char s) {
    return printf("%c", s ? '1' : '0');
}

int write_int64(int64_t s) {
    return printf(LL_FMT, s);
}

int write_int32(int32_t s) {
    return printf("%d", s);
}

int write_real(double s) {
    return printf("%lf", s);
}

//int read_(char *s) {
//    return scanf("%c", s);
//}



}

