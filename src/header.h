//
// Created by Connor  Patchen  on 10/27/24.
//

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Processing {
public:
    struct Header {
        char idlength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;;
        char imageDescriptor;
    };

    const Header getHeader() const{
        return header;
    }

    Header getHeader() {
        return header;
    }

    Processing(){
        header.idlength = 0;
        width = 0;
        height = 0;
    }

    Processing(Header h) {
        header = h;
        width = h.width;
        height = h.height;
    }

    struct Pixel {
        unsigned char color;
        Pixel() {
            color = 0;
        }
        Pixel(unsigned char color) {
            color = color;
        }
    private:
        //unsigned char c;
    };
    vector<Pixel> pixel;

    int const getSize() const{
        return pixel.size();
    }

    int getSize() {
        return pixel.size();
    }

    Pixel getI(int i) {
        return pixel.at(i);
    }

    const Pixel getI(int i) const{
        return pixel.at(i);
    }
private:
    Header header;
    short width;
    short height;

};

#endif //HEADER_H
