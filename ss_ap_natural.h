#ifndef SS_AP_NATURAL_H
#define SS_AP_NATURAL_H

#include <stddef.h>
#include <inttypes.h>
#include "ss_ap_err.h"

struct ss_ap_natural {
    uint32_t *data;
    size_t size;
};

struct ss_ap_natural_division {
    struct ss_ap_natural *quotient;
    struct ss_ap_natural *remainder;
};

enum ss_ap_err ss_ap_natural_init_from_zero(struct ss_ap_natural *to_init);
enum ss_ap_err ss_ap_natural_init_from_uint32(struct ss_ap_natural *to_init, uint32_t val);
enum ss_ap_err ss_ap_natural_init_from_uint64(struct ss_ap_natural *to_init, uint64_t val);
enum ss_ap_err ss_ap_natural_init_from_str(struct ss_ap_natural *to_init, char *str);

enum ss_ap_err ss_ap_natural_terminate(struct ss_ap_natural *to_terminate);

enum ss_ap_err ss_ap_natural_add(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_subtract(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_multiply(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_divide(struct ss_ap_natural *numerator, struct ss_ap_natural *devisor, struct ss_ap_natural_division *out);
enum ss_ap_err ss_ap_natural_power(struct ss_ap_natural *base, struct ss_ap_natural *exponent, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_root(struct ss_ap_natural *base, struct ss_ap_natural *root, struct ss_ap_natural *out);

// Returns -1 if the first number is smaller, 0 if both numbers are equal, and 
// 1 if the first number is larger.
enum ss_ap_err ss_ap_natural_compare(struct ss_ap_natural *in1, struct ss_ap_natural *in2, int *out);

// If this function returns an error that the buffer was too small, required_size will be set to the 
enum ss_ap_err ss_ap_natural_to_str(struct ss_ap_natural *in, char *out, size_t out_size);

#endif // #ifndef SS_AP_NATURAL_H