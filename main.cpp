/* 
 * File:   main.cpp
 * Author: Daniela
 *
 * Created on March 4, 2013, 11:23 AM
 */

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h> 
typedef FILE* PFILE;
const char* fileName = "Test.zip";

void navigateLocalHeaderToGetNames() {
    PFILE file = fopen(fileName, "r+b");

    short flag;
    short compressionMethod;
    short fileNameLength;
    short extraFieldLength;
    int compressedSize;
    int uncompressedSize;
    
    while (!feof(file)) { // This condition needs to be changed to find the archive decryption header.
        fseek(file, 6, SEEK_CUR); 
        fread(&flag, sizeof (flag), 1, file);
        if (flag != 3) { // if is equal to three there is a data descriptor.

            fread(&compressionMethod, sizeof (compressionMethod), 1, file);

            if (compressionMethod == 0 || (compressionMethod > 6 && compressionMethod < 11)) { // doesn't use compression at all.
                fseek(file, 8, SEEK_CUR);
                fread(&compressedSize, sizeof (compressedSize), 1, file);
                fread(&uncompressedSize, sizeof (uncompressedSize), 1, file);
                fread(&fileNameLength, sizeof (fileNameLength), 1, file);
                fread(&extraFieldLength, sizeof (extraFieldLength), 1, file);

                //Reading the name
                char name[fileNameLength + 1];
                fread(&name, sizeof (char), fileNameLength, file);
                name[fileNameLength] = '\0';
                printf("File name : %s\n", name);

                if (extraFieldLength != 0) {
                    char extraField[extraFieldLength];
                    fread(&extraField, sizeof (extraField), 1, file);
                    printf("Extra field: %s\n", extraField);
                }

                // Reading the file content.
                char fileContent[uncompressedSize + 1];
                fread(&fileContent, sizeof (char), uncompressedSize, file);
                fileContent[uncompressedSize] = '\0';
                printf("File content: %s\n", fileContent);
            }
        }
    }
}

/*
 * 
 */
int main() {
    navigateLocalHeaderToGetNames();
    return 0;
}

