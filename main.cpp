/* 
 * File:   main.cpp
 * Author: Daniela
 *
 * Created on March 4, 2013, 11:23 AM
 */

#include <stdio.h>
#include <string.h> 
typedef FILE* PFILE;
const char* fileName = "Test.zip";

void navigateLocalHeader() {
    PFILE file = fopen(fileName, "r+b");
    
    if (file != NULL) {
        int a;
        fread(&a, sizeof (a), 1, file);
        printf("Signature: %d\n", a);
        short b;
        fread(&b, sizeof(b), 1, file);
        printf("Version needed to extract : %d\n", b);
        fread(&b, sizeof(b), 1, file);
        printf("General purpose bit flag: %d\n", b);;
        fread(&b, sizeof(b), 1, file);
        printf("Compression method: %d\n", b);
        fread(&b, sizeof(b), 1, file);
        printf("File last modification time: %d\n", b);
        fread(&b, sizeof(b), 1, file);
        printf("File last modification date: %d\n", b);
        fread(&a, sizeof (a), 1, file);
        printf("CRC-32 : %d\n", a);
        fread(&a, sizeof (a), 1, file);
        printf("Compressed size: %d\n", a);
        fread(&a, sizeof (a), 1, file);
        printf("Uncompressed size: %d\n", a);
        short c;
        fread(&c, sizeof(c), 1, file);
        printf("File name length (n): %d\n", c);
        fread(&b, sizeof(b), 1, file);
        printf("Extra field length (m): %d\n", b);
        char name[c+1];
        fread(&name, sizeof(char), c, file);
        name[c]='\0';
        printf("File name : %s\n", name);       
    }

    fclose(file);
    file = 0;
}

/*
 * 
 */
int main() {
    navigateLocalHeader();
    return 0;
}

