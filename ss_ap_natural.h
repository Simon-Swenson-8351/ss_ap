#ifndef __SS_AP_NATURAL_H
#define __SS_AP_NATURAL_H

#include <stddef.h>
#include <inttypes.h>
#include "ss_ap_err.h"
#include "ss_ap_encoding.h"

struct ss_ap_natural {
    uint32_t *data;
    size_t size;
};

struct ss_ap_natural_division {
    struct ss_ap_natural *quotient;
    struct ss_ap_natural *remainder;
};

enum ss_ap_err ss_ap_natural_init_from_uint32(struct ss_ap_natural *to_init, uint32_t val);
enum ss_ap_err ss_ap_natural_init_from_str(struct ss_ap_natural *to_init, char *val, enum ss_ap_encoding encoding);
enum ss_ap_err ss_ap_natural_add(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_multiply(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_power(struct ss_ap_natural *base, struct ss_ap_natural *exponent, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_divide(struct ss_ap_natural *numerator, struct ss_ap_natural *devisor, struct ss_ap_natural_division *out);

#endif // #ifndef __SS_AP_NATURAL_H