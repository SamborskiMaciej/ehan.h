#include <stdio.h>
#include <stdlib.h>

#define EHAN_IMPLEMENTATION
#include "ehan.h"

typedef enum errorEnum {
    DUMB,
    UGLY,
    GREEDY,
    ABRASIVE,
    GRUMPY,
    MOROSE,
} errorEnum;

static const char * errorList[] = {
    "dumb error",
    "ugly error",
    "greedy error",
    "abrasive error",
    "grumpy error",
    "morose error",
};

GenericReturn f()
{
    return ehanValueFP(42.42f);
}

GenericReturn g()
{
    return ehanValue("YAY");
}

GenericReturn h()
{
    return ehanError(ABRASIVE);
}

int main(void)
{
    GenericReturn r = f();
    if (r.err > 0)
    {
        ELog("FAILURE %s\n", errorToString(errorList, r.err));
        /* HANDLE ERROR */
        goto exit;
    }

    ILog("SUCCESS: %.2f\n", resultFP(float, r));

    r = g();
    if (r.err > 0)
    {
        ELog("FAILURE %s\n", errorToString(errorList, r.err));
        /* HANDLE ERROR */
        goto exit;
    }

    ILog("SUCCESS: %s\n", resultGeneric(char *, r));

    r = h();
    if (r.err > 0)
    {
        ELog("FAILURE %s\n", errorToString(errorList, r.err));
        /* HANDLE ERROR */
        goto exit;
    }

    ILog("SUCCESS: %s\n", resultGeneric(char *, r));

    return 0;

exit:
    /* DO CLEANUP */
    return 1;
}
