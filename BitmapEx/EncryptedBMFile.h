// --------------------------------------------------------
//    File: EncryptedBMFile.h
//  Author: Mohammed Azam Siddiqui
// Purpose: class definition for a bitmap file object that
//			extends BMFile by allowing user to encrypt or decode
//			a bitmap image with an encrypted message using steganography
// --------------------------------------------------------

#ifndef ENCRYPTED_BMFILE_H
#define ENCRYPTED_BMFILE_H

#include "BMFile.h"       // Bitmap File
#include "BMWriter.h"     // File writer


class EncryptedBMFile : public BMFile {
public:
	// constructors
	// ----------------------------------------------------
	EncryptedBMFile(std::ifstream* reader, std::ofstream* writer);
	~EncryptedBMFile();

	// member methods
	// ----------------------------------------------------
	int encrypt(std::string message);
	std::string decode();


private:
};

#endif // ENCRYPTED_BMFILE_H