#include <stdlib.h>
#include "ss_ap_natural.h"

enum ss_ap_err ss_ap_natural_init_from_uint32(struct ss_ap_natural *to_init, uint32_t val) {
    to_init->data = (uint32_t *)malloc(sizeof(uint32_t));
    if(to_init->data == NULL)
        return SAE_ALLOC_FAILED;
    to_init->data[0] = val;
    to_init->size = 1;
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_init_from_str(struct ss_ap_natural *to_init, char *val, enum ss_ap_encoding encoding) {

    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_add(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out) {

    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_multiply(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out) {

    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_power(struct ss_ap_natural *base, struct ss_ap_natural *exponent, struct ss_ap_natural *out) {

    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_divide(struct ss_ap_natural *numerator, struct ss_ap_natural *devisor, struct ss_ap_natural_division *out) {

    return SAE_NO_ERR;
}