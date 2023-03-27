// --------------------------------------------------------
//    file: EncryptedPixelArray.cpp
//  Author: COP 3003 Programming II, Mohammed Azam Siddiqui
// Purpose: implementation file for steganography encryptor
// --------------------------------------------------------
#include "EncryptedPixelArray.h"
#include <math.h>           // pow

/**
 * default constructor
 * @param width - of bitmap in pixels
 * @param height - of bitmap in rows
 */
EncryptedPixelArray::EncryptedPixelArray(int width, int height, int depth)
    : PixelArray{ width, height, depth } {
}

/**
 * encrypt existing pixel array with message
 * @param string - message to encrypt into bitmap
 * @return int   - number of bytes read
 */
int EncryptedPixelArray::encrypt(std::string message) {

    int bytes = 0;
    int row = 0, column = 0;
    Pixel* nextPixel = &pixels[row][column];                    // grab start of pixel array

    for (int next = 0; next < message.length(); next++) {       // for the amount of chars in the message
        char nextChar = message[next];

        for (int bit = 0; bit < 8; bit++) {

            nextPixel = &pixels[row][column];                   // grab next pixel

            BYTE blue = nextPixel->getBlue();                   // grab pixel's blue value

            if (nextChar & 0b00000001) {                        // check if there is a 1 in the 0-bit position of char
                blue |= 0b00000001;                             // retain blue's color value but set 0-bit to 1
            }
            else {
                blue &= 0b11111110;                             // retain blue's color value but set 0-bit to 0
            }

            nextPixel->setBlue(blue);                           // update blue pixel's value

            nextChar >>= 1;

            column++;

        }

        if (column == width) {                                  // go down to start of next row of pixels if bitmap width reached
            row++;
            column = 0;
        }

        nextChar = message[next + 1];                       // look at next char in message
        bytes++;
    }

    // Make the next 8 pixels' blue 0-bit a 0 (null terminator)
    for (int term = 0; term < 8; term++) {
        Pixel* nextPixel = &pixels[row][column];

        BYTE blue = nextPixel->getBlue();

        blue &= 0b11111110;

        nextPixel->setBlue(blue);

        column++;

        if (column == width) {
            row++;
            column = 0;
        }

        bytes++;
    }

    return bytes;
}


/**
 * decode message from existing pixel array
 * @return string - message encrypted into bitmap
 */
std::string EncryptedPixelArray::decode() {

    std::string decodedMessage = "";
    char charValue = 0;                                         // the total value of the char, summed up from each blue 0-bit

    int row = 0, column = 0;                                    
    Pixel* nextPixel = &pixels[row][column];                    // grab start of pixel array

    bool charsLeft = true;
    while (charsLeft) {     

        for (int charBit = 0; charBit < 8; charBit++)
        {
            nextPixel = &pixels[row][column];                   // grab pixel
            BYTE blue = nextPixel->getBlue();                   // grab pixel's blue value
            if (blue & 0b00000001) {                            // check if there is a 1 in the 0-bit position
                charValue += pow(2,charBit);                    // if so, add the value of the bit to charValue (0-bit = 1, 1-bit = 2, etc..)
            }

            column++;                                           // look at next pixel

            if (column == width) {                              // go down to start of next row of pixels if bitmap width reached
                row++;
                column = 0;
            }
            
        }

        if (charValue == 0) {                                   // if total charValue is 0 it means we hit the null terminator, exit loop
            charsLeft = false;
        }

        decodedMessage += charValue;                            // add character to decoded message string
        charValue = 0;                                          // reset charValue for next char
    }

    return decodedMessage;
}