#ifndef __WEITUO_LIB_H__
#define __WEITUO_LIB_H__

#include <stdint.h>
#include <string>

void init_lib();
int gen_key1(unsigned char *out, unsigned char *in);
void  client_en_de_crypt(unsigned char* out_buff, unsigned char* src_buff, int32_t *len_ptr, unsigned char* key1, unsigned char* key2, int en_or_de);
void gen_key2(unsigned char *src, int32_t len, unsigned char *dst, int32_t *len_ptr, unsigned char *src2);

void server_en_de_crypt(unsigned char* out_buff, unsigned char* src_buff, int32_t *len_ptr, unsigned char* key1, unsigned char* key2, int en_or_de);

void signature(unsigned char *src, int32_t len, unsigned char *dst, int32_t *len_ptr, unsigned char *src2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
