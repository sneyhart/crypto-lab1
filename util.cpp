#include "util.h"

u_string encode(u_string key, u_string data)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex (ctx, EVP_aes_128_ecb(), NULL, key.c_str(), NULL);
    EVP_CIPHER_CTX_set_padding(ctx, false);
    unsigned char buffer[1024], *pointer = buffer;
    int outlen;
    EVP_EncryptUpdate (ctx, pointer, &outlen, data.c_str(), data.length()) or ABORT();
    pointer += outlen;
    EVP_EncryptFinal_ex(ctx, pointer, &outlen) or ABORT();
    pointer += outlen;
    EVP_CIPHER_CTX_free(ctx);
    return u_string(buffer, pointer-buffer);
}

u_string decode(u_string key, u_string data)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex (ctx, EVP_aes_128_ecb(), NULL, key.c_str(), NULL);
    EVP_CIPHER_CTX_set_padding(ctx, false);
    unsigned char buffer[1024], *pointer = buffer;
    int outlen;
    EVP_DecryptUpdate (ctx, pointer, &outlen, data.c_str(), data.length()) or ABORT();
    pointer += outlen;
    EVP_DecryptFinal_ex(ctx, pointer, &outlen) or ABORT();
    pointer += outlen;
    EVP_CIPHER_CTX_free(ctx);
    return u_string(buffer, pointer-buffer);
}
