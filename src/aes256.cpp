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

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <iostream>
#include <string.h>

// On Linux, we'll seed openssl with /dev/urandom, on others we use the time
#ifdef __unix__
#include <fstream>
#elif _win32
#include <Wincrypt.h>
#endif

/*!
 * Generates 16 random numbers for the initialization vector.
 * On Linux, this uses /dev/urandom, on other platforms, it uses c's rand() function
 * \param ivec An unsigned char[16] to fill with random numbers
 * \return True on success, false otherwise
 */
bool getRandomIvec(unsigned char* ivec){
	
#ifdef __unix__

	// Read 16 bytes from /dev/urandom
	std::ifstream fin("/dev/urandom", std::ios_base::in | std::ios_base::binary);
	if(!fin.fail()){
		fin.read((char*)ivec, 16);
	}
	else{
		fin.open("/dev/urandom", std::ios_base::in | std::ios_base::binary);
		if(!fin.fail()){
			fin.read((char*)ivec, 16);
		}
		else return false;
	}
	fin.close();
	return true;

#elif _win32
	
	// I don't have a clue if this works..
	HCRYPTPROV hCryptProv;
	CryptAcquireContext( &hCryptProv,  NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)
	if(CryptGenRandom(hCryptProv, 16, (BYTE*) ivec)){
		printf("Random sequence generated. \n");
	}
	else{
		std::cout << "ERROR: CryptGenRandom failed." << std::endl;
		return NULL;
	}

#else

	// uhh...

#endif
}

/*!
 * Encrypts a string using AES 256
 * Note: If the key is less than 32 bytes, it will be null padded.
 *       If the key is greater than 32 bytes, it will be truncated
 * \param in The string to encrypt
 * \param key The key to encrypt with
 * \return The encrypted data
 */
std::string aes_encrypt(std::string in, std::string key){

	unsigned char ivec[16];
	getRandomIvec(ivec);
	std::string ivecString((char*) ivec, 16); // Save this for later

	// Always pad the key to 32 bits.. because we can
	if(key.length() < 32){
		key.append(32 - key.length(), '\0');
	}
	
	// Get some space ready for the output
	unsigned char *output = new unsigned char[in.length() + AES_BLOCK_SIZE];
	
	// Encrypt the data
	int length, finalLength = 0;
	EVP_CIPHER_CTX *encryptHandle = new EVP_CIPHER_CTX;
	EVP_CIPHER_CTX_init(encryptHandle);
	EVP_EncryptInit_ex(encryptHandle, EVP_aes_256_cbc(), NULL, (unsigned char*) key.c_str(), ivec);
	EVP_EncryptUpdate(encryptHandle, output, &length, (unsigned char*)in.c_str(), in.length());
	finalLength += length;
	EVP_EncryptFinal_ex(encryptHandle, output + length, &length);
	finalLength += length;

	// Make the data into a string
	std::string ret((char*) output, finalLength);
	
	// clean up
	delete output;
	EVP_CIPHER_CTX_cleanup(encryptHandle);
	delete encryptHandle;
	
	return ivecString + ret;
}

/*!
 * Decrypts a string using AES 256
 * Note: If the key is less than 32 bytes, it will be null padded.
 *       If the key is greater than 32 bytes, it will be truncated
 * \param in The string to decrypt
 * \param key The key to decrypt with
 * \return The decrypted data
 */
std::string aes_decrypt(std::string in, std::string key){

	// Get the ivec from the front
	unsigned char ivec[16];
	strncpy((char*)ivec, in.c_str(), 16);
	in = in.substr(16);

	// Always pad the key to 32 bits.. because we can
	if(key.length() < 32){
		key.append(32 - key.length(), '\0');
	}

	// Create some space for output
	unsigned char *output = new unsigned char[in.length()];	
	int length, finalLength = 0;
	
	// Decrypt the string
	EVP_CIPHER_CTX *encryptHandle = new EVP_CIPHER_CTX;
	EVP_CIPHER_CTX_init(encryptHandle);
	EVP_DecryptInit_ex(encryptHandle, EVP_aes_256_cbc(), NULL, (unsigned char*) key.c_str(), ivec);
	EVP_DecryptUpdate(encryptHandle, output, &length, (unsigned char*)in.c_str(), in.length());
	finalLength += length;
	EVP_DecryptFinal_ex(encryptHandle, output + length, &length);
	finalLength += length;
	
	std::cout << finalLength << std::endl;
	
	// Make the output into a string
	std::string ret((char*) output, finalLength);
	
	// Clean up
	delete output;
	EVP_CIPHER_CTX_cleanup(encryptHandle);
	delete encryptHandle;
	
	return ret;
}
