
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>
#include "md5.h"
#include "GBase64.h"

using namespace std;


#include <windows.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/des.h>
#include <memory>

RSA* createPublicRSA(std::string key) {
	RSA *rsa = NULL;
	BIO *keybio;
	const char* c_string = key.c_str();
	keybio = BIO_new_mem_buf((void*)c_string, -1);
	if (keybio == NULL) {
		return 0;
	}
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	return rsa;
}

RSA* createPrivateRSA(std::string key) {
	RSA *rsa = NULL;
	const char* c_string = key.c_str();
	BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
	if (keybio == NULL) {
		return 0;
	}
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	return rsa;
}

bool RSAVerifySignature(RSA* rsa, const unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen) {
	//*Authentic = false;
	EVP_PKEY* pubKey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pubKey, rsa);
	EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

	bool ret;

	if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, pubKey) <= 0) {
		ret = false;
	}
	if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
		ret = false;
	}
	int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
	if (AuthStatus == 1) {
		//*Authentic = true;
		
		ret = true;
	}
	else if (AuthStatus == 0) {
		//*Authentic = false;
		ret = true;
	}
	else {
		//*Authentic = false;
		ret = false;
	}

	EVP_PKEY_free(pubKey);
	EVP_MD_CTX_destroy(m_RSAVerifyCtx);

	return ret;
}

std::string RSASign(RSA* rsa,
	const unsigned char* Msg,
	size_t MsgLen
	) 
{
	size_t MsgLenEnc = 0;
	std::string ret;
	EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_create();
	EVP_PKEY* priKey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(priKey, rsa);
	if (EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_sha256(), NULL, priKey) <= 0) {
		EVP_PKEY_free(priKey);
		return ret;
	}
	if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
		EVP_PKEY_free(priKey);
		EVP_MD_CTX_destroy(m_RSASignCtx);
		return ret;
	}
	if (EVP_DigestSignFinal(m_RSASignCtx, NULL, &MsgLenEnc) <= 0) {
		EVP_PKEY_free(priKey);
		EVP_MD_CTX_destroy(m_RSASignCtx);
		return ret;
	}
	
	std::auto_ptr<unsigned char> ptr(new unsigned char[MsgLenEnc]);

	if (EVP_DigestSignFinal(m_RSASignCtx, ptr.get(), &MsgLenEnc) <= 0) {
		EVP_PKEY_free(priKey);
		EVP_MD_CTX_destroy(m_RSASignCtx);
		return ret;
	}

	EVP_MD_CTX_destroy(m_RSASignCtx);
	EVP_PKEY_free(priKey);

	return Base64::Encode((const char*)ptr.get(), MsgLenEnc);
}

std::string PUBLIC_KEY = "-----BEGIN PUBLIC KEY-----\n"
"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCRiwSQLmRckBoBXrxj1+TE5lF1\n"
"AHvyKeDKU6nt6UnFKlxacl6KqZPUTfD9FlV1ddpTOGUZL3z+yq6Z2GOCAPiid9dg\n"
"0VED2bvBxtCMEo/RQJFBUHWP3UaKZyu0btcDAUAGWhJydqMaoHEIRrHJbcN/FACa\n"
"XRu7YKQqbdkEr5ze0QIDAQAB\n"
"-----END PUBLIC KEY-----";



std::string pkc_sign(const unsigned char* data, int32_t len, const unsigned char* private_key, int32_t key_len)
{
	RSA* rsa = createPrivateRSA(std::string((const char*)private_key, key_len));

	std::string ret = RSASign(rsa, data, len);

	//RSA_free(rsa);

	return ret;
}

bool pkc_verify(const unsigned char* data, int32_t len, const unsigned char* b64_signature, int32_t b64_sig_len, const unsigned char* public_key, int32_t key_len)
{
	RSA* rsa = createPublicRSA(std::string((const char*)public_key, key_len));

	std::string signature = Base64::Decode(std::string((const char*)b64_signature, b64_sig_len));

	bool ret = RSAVerifySignature(rsa, (const unsigned char*)signature.c_str(), signature.size(), (const char*)data, len);

	//RSA_free(rsa);

	return ret;
}

/*
std::string pkc_sign_with_key(const unsigned char* data, int32_t len)
{
	return pkc_sign(data, len, (const unsigned char*)PRIVATE_KEY.c_str(), PRIVATE_KEY.size());
}
*/

bool pkc_verify_with_key(const unsigned char* data, int32_t len, const unsigned char* signature, int32_t sig_len)
{
	return pkc_verify(data, len, signature, sig_len, (const unsigned char*)PUBLIC_KEY.c_str(), PUBLIC_KEY.size());
}
