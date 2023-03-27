// --------------------------------------------------------
//    file: EncryptedPixelArray.cpp
//  Author: COP 3003 Programming II
// Purpose: class def file for steganography encryptor
// --------------------------------------------------------

#ifndef ENCRYPTED_PIXELARRAY_H
#define ENCRYPTED_PIXELARRAY_H

#include <string>
#include "PixelArray.h"

class EncryptedPixelArray : public PixelArray {
public:
    EncryptedPixelArray(int width, int height, int depth);

    int encrypt(std::string message);
    std::string decode();

private:
};


#endif //ENCRYPTED_PIXELARRAY_H
