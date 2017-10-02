#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#define ABORT() (fprintf(stderr, "%s\nAborting in %s at %s:%d\n",\
            ERR_error_string(ERR_get_error(), NULL), __PRETTY_FUNCTION__, __FILE__, __LINE__), abort(), 0)

#ifndef _UTIL_H_
#define _UTIL_H_

typedef std::basic_string<unsigned char> u_string;
u_string encode(u_string key, u_string data);
u_string decode(u_string key, u_string data);

#endif
