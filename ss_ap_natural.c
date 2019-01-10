#include <stdlib.h>
#include "ss_ap_natural.h"

// Modify the underlying data in in1 such that a digit is borrowed wherever it 
// can be. We define this as a separate function, since we may need to carry 
// from more than just the immediate left digit if that digit is zero.
static void borrow(struct ss_ap_natural *in1, size_t digit_that_needs_the_borrow);

enum ss_ap_err ss_ap_natural_init_from_zero(struct ss_ap_natural *to_init) {
    to_init->data = NULL;
    to_init->size = 0;
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_init_from_uint32(struct ss_ap_natural *to_init, uint32_t val) {
    if(val == 0)
        return ss_ap_natural_init_from_zero(to_init);
    to_init->data = (uint32_t *)malloc(sizeof(uint32_t));
    if(!to_init->data)
        return SAE_ALLOC_FAILED;
    to_init->data[0] = val;
    to_init->size = 1;
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_init_from_uint64(struct ss_ap_natural *to_init, uint64_t val) {
    if (val <= (uint64_t)0xFFFFFFFF)
        return ss_ap_natural_init_from_uint32(to_init, (uint32_t)val);
    to_init->data = (uint32_t *)calloc(2, sizeof(uint32_t));
    if(!to_init->data)
        return SAE_ALLOC_FAILED;
    to_init->data[0] = (uint32_t)(val & 0xFFFFFFFF);
    to_init->data[1] = (uint32_t)((val >> 32) & 0xFFFFFFFF);
    to_init->size = 2;
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_init_from_str(struct ss_ap_natural *to_init, char *str) {
    
}

enum ss_ap_err ss_ap_natural_terminate(struct ss_ap_natural *to_terminate) {
    free(to_terminate->data);
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_add(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out) {
    // Ensure that in1 <= in2
    if(in1->size > in2->size) {
        struct ss_ap_natural *tmp = in1;
        in1 = in2;
        in2 = tmp;
    }
    // Usually, the answer will only be of size greater. Hedge our bets on this 
    // usual case.
    out->data = (uint32_t *)calloc(in2->size, sizeof(uint32_t));
    if(!out->data)
        return SAE_ALLOC_FAILED;

    uint32_t carry = 0;
    size_t i = 0;
    for(i = 0; i < in2->size; i++) {
        uint64_t cur = (uint64_t)in2->data[i] + (uint64_t)carry;
        if(i < in1->size)
            cur += (uint64_t)in1->data[i];
        out->data[i] = (uint32_t)(cur & 0xFFFFFFFF);
        carry = (uint32_t)((cur >> 32) & 0x00000001);
    }
    if(carry) {
        uint32_t *tmp = out->data;
        out->data = (uint32_t *)calloc(i + 1, sizeof(uint32_t));
        if(!out->data) {
            free(tmp);
            return SAE_ALLOC_FAILED;
        }
        memcpy(out->data, tmp, i * sizeof(uint32_t));
        out->data[i] = carry;
        out->size = i + 1;
    } else {
        out->size = i;
    }
    return SAE_NO_ERR;
}

enum ss_ap_err ss_ap_natural_subtract(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out) {
    int compare;
    enum ss_ap_err compare_err = ss_ap_natural_compare(in1, in2, &compare);
    if(compare_err != SAE_NO_ERR)
        return compare_err;
    if(compare < 0)
        return SAE_SUB_WITH_SMALLER_MINUEND;
    if(compare == 0)
        return ss_ap_natural_init_from_zero(out);
    // Probably, the output will be the same size as the minuend.
    out->data = (uint32_t *)calloc(in1->size, sizeof(uint32_t));
    size_t i = 0;
    for(i = 0; i < in2->size; i++) {
        uint64_t cur = (uint64_t)in1->data[i];
        if(in1->data[i] < in2->data[i]) {
            borrow(in1, i);
            cur |= ((uint64_t)1 << 32));
        }
        cur -= in2->data[i];
        out->data[i] = cur;
    }
    memcpy(out->data + i, in1->data + i; in1->size - i);
    if(out->data[in1->size - 1] == 0) {
        
    }
}
enum ss_ap_err ss_ap_natural_multiply(struct ss_ap_natural *in1, struct ss_ap_natural *in2, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_divide(struct ss_ap_natural *numerator, struct ss_ap_natural *devisor, struct ss_ap_natural_division *out);
enum ss_ap_err ss_ap_natural_power(struct ss_ap_natural *base, struct ss_ap_natural *exponent, struct ss_ap_natural *out);
enum ss_ap_err ss_ap_natural_root(struct ss_ap_natural *base, struct ss_ap_natural *root, struct ss_ap_natural *out);

// Returns -1 if the first number is smaller, 0 if both numbers are equal, and 
// 1 if the first number is larger.
enum ss_ap_err ss_ap_natural_compare(struct ss_ap_natural *in1, struct ss_ap_natural *in2, int *out);

// If this function returns an error that the buffer was too small, required_size will be set to the 
enum ss_ap_err ss_ap_natural_to_str(struct ss_ap_natural *in, char *out, size_t out_size);

static void borrow(struct ss_ap_natural *in1, size_t digit_that_needs_the_borrow);