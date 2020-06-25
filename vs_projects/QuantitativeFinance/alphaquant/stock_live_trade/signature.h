#ifndef __SIGNATURE_LIB_H__
#define __SIGNATURE_LIB_H__

#include <stdint.h>
#include <string>

std::string pkc_sign(const unsigned char* data, int32_t len, const unsigned char* private_key, int32_t key_len);
bool pkc_verify(const unsigned char* data, int32_t len, const unsigned char* signature, int32_t sig_len, const unsigned char* public_key, int32_t key_len);

//std::string pkc_sign_with_key(const unsigned char* data, int32_t len);
bool pkc_verify_with_key(const unsigned char* data, int32_t len, const unsigned char* signature, int32_t sig_len);

#endif
