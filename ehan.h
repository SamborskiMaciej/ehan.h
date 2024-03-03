#ifndef EHAN_H_
#define EHAN_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct GenericReturn {
    long double fp;
    void * val;
    size_t err;
} GenericReturn;

GenericReturn ehanError(size_t error);
#define ehanValue(v) _ehanValue((void *) v)
#define ehanValueFP(fp) _ehanValueFP((long double) fp)
GenericReturn _ehanValue(void * value);
GenericReturn _ehanValueFP(long double value);

#define resultGeneric(type, ret) (*(type *) (&ret.val))
#define resultFP(type, ret) ((type) (ret.fp))

const char * errorToString(const char * errorList[], size_t err);

#define ILog(format, ...)                                                                        \
do {                                                                                             \
fprintf(stderr, "\x1b[34m""info""\x1b[0m"":%s:%d:  " format, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)                                                                 

#define WLog(format, ...)                                                                        \
do {                                                                                             \
fprintf(stderr, "\x1b[33m""warn""\x1b[0m"":%s:%d:  " format, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)                                                                 

#define ELog(format, ...)                                                                        \
do {                                                                                             \
fprintf(stderr, "\x1b[31m""error""\x1b[0m"":%s:%d: " format, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)                                                                 

#ifdef NDEBUG

#define DLog(format, ...)

#else

#define DLog(format, ...)                                                                        \
do {                                                                                             \
fprintf(stderr, "\x1b[32m""debug""\x1b[0m"":%s:%d: " format, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)                                                                 

#endif

#ifdef EHAN_IMPLEMENTATION

GenericReturn _ehanValue(void * value)
{
    return (GenericReturn) {
        .val = value,
        .err = 0,
    };
}

GenericReturn _ehanValueFP(long double value)
{
    return (GenericReturn) {
        .fp = value,
        .val = 0,
        .err = 0,
    };
}

GenericReturn ehanError(size_t error)
{
    return (GenericReturn) {
        .val = 0,
        .err = error,
    };
}

const char * errorToString(const char * errorList[], size_t err)
{
    return errorList[err - 1];
}

#endif // EHAN_IMPLEMENTATION

#endif // EHAN_H_
