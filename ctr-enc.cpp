#include "util.h"

int main()
{
    SSL_load_error_strings();

    u_string key = (unsigned char *) "a_key_simple_key";
    u_string clear_text = (unsigned char *) "1234567890uvwxyz";
    u_string secret_txt = (unsigned char *) "\x14\x2f" "\x7d\x9e" "\xad\x8c" "\x06\x82" "\x30\xe0" "\xf1\x65" "\xa5\x2f" "\xf7\x89";

    std::cerr << "ENCODING: " << (encode(key, clear_text)==secret_txt ? "ok" : "FAIL") << std::endl;
    std::cerr << "ENCODING: " << (char*)clear_text.c_str() << " --> " << (char*)encode(key, clear_text).c_str() << std::endl;
    std::cerr << "DECODING: " << (decode(key, secret_txt)==clear_text ? "ok" : "FAIL") << std::endl;
    std::cerr << "DECODING: " << (char*)secret_txt.c_str() << " --> " << (char*)decode(key, secret_txt).c_str() << std::endl;

    return 0;
}
