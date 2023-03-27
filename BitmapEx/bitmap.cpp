// --------------------------------------------------------
//    File: bitmap.cpp
//  Author: COP 3003 Programming II, Mohammed Azam Siddiqui
// Purpose: main application file for bitmap program that
//          currently opens a bitmap and allows the user to 
//          encrypt the bitmap image with a message and write it out to a new bitmap file
//          or decode the current bitmap image's encrypted message
// --------------------------------------------------------
#include <iostream>
#include <fstream>

#include "BMFile.h"             // bitmap file class
#include "EncryptedBMFile.h"    // encrypted bitmap file class

int main() {

    std::string inFileName, outFileName;
    outFileName = "dummy.bmp";

    std::cout << "\nEnter bitmap file name to read: ";
    std::cin >> inFileName;

    // Make sure the file names were entered
    if (inFileName.length() && outFileName.length()) {

        std::ifstream inFile;
        inFile.open(inFileName, std::ios::binary);

        std::ofstream outFile;
        outFile.open(outFileName, std::ios::out|std::ios::trunc|std::ios::binary);

        if (inFile.is_open() && outFile.is_open()) {

            BMFile bmFile = BMFile(&inFile, &outFile);

            int bytes = bmFile.load();

            std::cout << "Loaded Bitmap \"" << inFileName << "\" (" << std::to_string(bytes) << " bytes)\n";
            std::cout << bmFile.toString();

            // Menu Choice
            char choice;
            std::cout << "\nWould you like to: ";
            std::cout << "\nEncrypt a message into a bitmap file [E]";
            std::cout << "\nDecode a message from this bitmap file [D]";
            std::cout << "\n>";
            std::cin >> choice;

            if (std::tolower(choice) == 'e') {              // Encrypt

                EncryptedBMFile* encryptedBMFile = reinterpret_cast<EncryptedBMFile*>(&bmFile);

                std::string encryptedFileName;
                std::cout << "\nEnter new encrypted bitmap filename to write to: ";
                std::cin >> encryptedFileName;

                std::string messageToEncrypt;
                std::cout << "\nEnter message to encrypt into " << encryptedFileName << ".\n" << ">";
                std::cin >> messageToEncrypt;

                encryptedBMFile->encrypt(messageToEncrypt);

                std::ofstream encryptFile;
                encryptFile.open(encryptedFileName, std::ios::out | std::ios::trunc | std::ios::binary);

                encryptedBMFile->setWriter(&encryptFile);
                encryptedBMFile->store();

                std::cout << "\nBitmap file successfully encrypted and written out to " << encryptedFileName;

            }
            else if (std::tolower(choice) == 'd'){          // Decode

                EncryptedBMFile* decodedBMFile = reinterpret_cast<EncryptedBMFile*>(&bmFile);

                std::string decodedMessage = decodedBMFile->decode();
                std::cout << "\nDecoded message from " << inFileName << ": " << decodedMessage << '\n';
            }
            else {
                std::cout << "\nInvalid option.\n";
            }
        }
        else {
            std::cout << "Could not open input file: " << inFileName << std::endl;
        }


    } // filename lengths > 0
    else {
        std::cout << "File names must be > 0 length!\n";
    }

    return 0;
}
