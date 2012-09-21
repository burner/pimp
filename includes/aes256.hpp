/*!
 * Simple AES
 * Brendan Long
 * March 29, 2010
 * 
 * Simplified encryption and decryption using OpenSSL's AES library.
 * Remember to compile with -lcrypto and link against the library
 * g++ (your stuff) -lcrypto simpleAes.cpp (or simpleAes.o)
 *
 * Implementation note: Using the default ivec (0) is not secure. For
 *                      the full security that AES offers, use a different
 *                      ivec each time (it does not need to be secret,
 *                      just different.
 *
 * This code is released into the public domain. Yada yada..
 * Read this for details: http://creativecommons.org/licenses/publicdomain/
 *
 * If for some reason public domain isn't good enough, you may use, alter,
 * distribute or do anything else you want with this code with no restrictions.
 */

#include <string>

std::string aes_encrypt(std::string in, std::string key);
std::string aes_encrypt(std::string in, std::string key, unsigned char ivec[16]);

std::string aes_decrypt(std::string in, std::string key);
std::string aes_decrypt(std::string in, std::string key, unsigned char ivec[16]);
