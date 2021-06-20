#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "amount.h"


amount_t amount_inf()
{
    return INT_MAX;
}

bool amount_is_inf(amount_t a)
{
    return a == amount_inf();
}

bool amount_le(amount_t a1, amount_t a2)
{
    bool res;
    if(amount_is_inf(a1)) {
        res = false;
    }else if (amount_is_inf(a2)) {
        res = true;
    }else {
        res = a1 <= a2;
    }
    return res;
}

bool amount_lt(amount_t a1, amount_t a2)
{
    bool res;
    if(amount_is_inf(a1)) {
        res = false;
    }else if (amount_is_inf(a2)) {
        res = true;
    }else {
        res = a1 < a2;
    }
    return res;
}

amount_t amount_sum(amount_t a1, amount_t a2)
{
    amount_t res;
    if (amount_is_inf(a1) || amount_is_inf(a2)) {
        res = amount_inf();
    } else {
        res = a1 + a2;
    }
    return res;
}

void amount_dump(amount_t a)
{
    if (amount_is_inf(a)) {
        printf("#");
    } else {
        printf("%d", a);
    }
}
