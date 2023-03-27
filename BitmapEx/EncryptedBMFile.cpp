// --------------------------------------------------------
//    File: EncryptedBMFile.cpp
//  Author: Mohammed Azam Siddiqui
// Purpose: class implementation for a bitmap file object that
//			extends BMFile by allowing user to encrypt or decode
//			a bitmap image with an encrypted message using steganography
// --------------------------------------------------------

#include "BMFile.h"
#include "EncryptedBMFile.h"
#include "EncryptedPixelArray.h"


// constructors
// ----------------------------------------------------

/**
 * default constructor
 */
EncryptedBMFile::EncryptedBMFile(std::ifstream* reader, std::ofstream* writer) {
	this->reader = BMReader(reader);
	this->writer = BMWriter(writer);
}

/**
 * destructor
 */
EncryptedBMFile::~EncryptedBMFile() {}


// member methods
// ----------------------------------------------------

/**
 * encrypt bitmap file with secret message
 * @param message	- secret message to hide in bitmap file
 * @return int		- number of bytes read
 */
int EncryptedBMFile::encrypt(std::string message) {
	int bytesRead = 0;
	EncryptedPixelArray* encryptedArray = reinterpret_cast<EncryptedPixelArray*>(&pixels);
	bytesRead += encryptedArray->encrypt(message);
	return bytesRead;
}

/**
 * decode bitmap file with secret message
 * @param inFilename - name of bitmap image file to decode
 * @return string - decoded secret message
 */
std::string EncryptedBMFile::decode() {
	std::string message = "";
	EncryptedPixelArray* encryptedArray = reinterpret_cast<EncryptedPixelArray*>(&pixels);
	message = encryptedArray->decode();
	return message;
}
