
//
// Created by Connor  Patchen  on 10/27/24.
//

#ifndef INC_10_FUNCTIONS_H
#define INC_10_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include "header.h"
using namespace std;

Processing rotate(Processing& top_layer) {
    for(int i = 0; i < top_layer.pixel.size(); i ++) {
        Processing::Pixel this_pixel;
        this_pixel.color = top_layer.pixel.at(i).color;
        Processing::Pixel temp_color;
        if(i % 3 == 0) {
            temp_color.color = top_layer.pixel.at(i+2).color;
            top_layer.pixel.at(i+2).color = this_pixel.color;
            top_layer.pixel.at(i).color = temp_color.color;
        }
    }
    reverse(top_layer.pixel.begin(), top_layer.pixel.end());
    return top_layer;
}

Processing combine_channels(Processing& top_layer, Processing& middle_layer, Processing& bottom_layer) {
    Processing combined_layer = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel this_pixel;
        if(i % 3 == 0) {
            this_pixel.color = bottom_layer.pixel.at(i).color;
        } else if(i % 3 == 1) {
            this_pixel.color = middle_layer.pixel.at(i).color;
        } else if(i % 3 == 2) {
            this_pixel.color = top_layer.pixel.at(i).color;
        }
        if (this_pixel.color > 255) {
            this_pixel.color = 255;
        } else if (this_pixel.color < 0) {
            this_pixel.color = 0;
        }
        combined_layer.pixel.push_back(this_pixel);
    }
    return combined_layer;
}

Processing separate_channels(Processing& top_layer, int x) {
    Processing red_layer = top_layer.getHeader();
    Processing blue_layer = top_layer.getHeader();
    Processing green_layer = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel red_pixel;
        Processing::Pixel green_pixel;
        Processing::Pixel blue_pixel;

        if(i % 3 == 0) {
            blue_pixel.color = top_pixel.color;
            blue_layer.pixel.push_back(blue_pixel);
            blue_layer.pixel.push_back(blue_pixel);
            blue_layer.pixel.push_back(blue_pixel);
        } else if (i % 3 == 1) {
            green_pixel.color = top_pixel.color;
            green_layer.pixel.push_back(green_pixel);
            green_layer.pixel.push_back(green_pixel);
            green_layer.pixel.push_back(green_pixel);

        }else if (i % 3 == 2) {
            red_pixel.color = top_pixel.color;
            red_layer.pixel.push_back(red_pixel);
            red_layer.pixel.push_back(red_pixel);
            red_layer.pixel.push_back(red_pixel);

        }
    }
    if(x==1) {
        return blue_layer;
    } else if (x == 2) {
        return green_layer;
    } else if (x == 3) {
        return red_layer;
    } else {
        return Processing();
    }
}

Processing scaleGreen(Processing& top_layer, int x) {
    Processing scale_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_pixel;
        int pixelToScale;
        if(i % 3 == 1) {
            pixelToScale = top_pixel.color * x;
        } else {
            pixelToScale = top_pixel.color;
        }
        if (pixelToScale >255) {
            pixelToScale = 255;
        } else if (pixelToScale < 0) {
            pixelToScale = 0;
        }
        actual_pixel.color = pixelToScale;
        scale_added.pixel.push_back(actual_pixel);
    }
    return scale_added;
}

Processing scaleRed(Processing& top_layer, int x) {
    Processing scale_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_pixel;
        int pixelToScale;
        if(i % 3 == 2) {
            pixelToScale = top_pixel.color * x;
        } else {
            pixelToScale = top_pixel.color;
        }
        if (pixelToScale >255) {
            pixelToScale = 255;
        } else if (pixelToScale < 0) {
            pixelToScale = 0;
        }
        actual_pixel.color = pixelToScale;
        scale_added.pixel.push_back(actual_pixel);
    }
    return scale_added;
}

Processing scaleBlue(Processing& top_layer, int x) {
    Processing scale_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_pixel;
        int pixelToScale;
        if(i % 3 == 0) {
            pixelToScale = top_pixel.color * x;
        } else {
            pixelToScale = top_pixel.color;
        }
        if (pixelToScale >255) {
            pixelToScale = 255;
        } else if (pixelToScale < 0) {
            pixelToScale = 0;
        }
        actual_pixel.color = pixelToScale;
        scale_added.pixel.push_back(actual_pixel);
    }
    return scale_added;
}

Processing addGreen(Processing& top_layer, int x) {
    Processing green_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_green;
        int greened_up;
        if (i % 3 == 1) {
            greened_up = top_pixel.color + x;
        } else {
            greened_up = top_pixel.color;
        }
        if(greened_up > 255) {
            greened_up = 255;
        } else if(greened_up < 0) {
            greened_up = 0;
        }
        actual_green.color = greened_up;
        green_added.pixel.push_back(actual_green);
    }
    return green_added;
}

Processing addBlue(Processing& top_layer, int x) {
    Processing green_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_green;
        int greened_up;
        if (i % 3 == 0) {
            greened_up = top_pixel.color + x;
        } else {
            greened_up = top_pixel.color;
        }
        if(greened_up > 255) {
            greened_up = 255;
        } else if(greened_up < 0) {
            greened_up = 0;
        }
        actual_green.color = greened_up;
        green_added.pixel.push_back(actual_green);
    }
    return green_added;
}

Processing addRed(Processing& top_layer, int x) {
    Processing green_added = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel actual_green;
        int greened_up;
        if (i % 3 == 2) {
            greened_up = top_pixel.color + x;
        } else {
            greened_up = top_pixel.color;
        }
        if(greened_up > 255) {
            greened_up = 255;
        } else if(greened_up < 0) {
            greened_up = 0;
        }
        actual_green.color = greened_up;
        green_added.pixel.push_back(actual_green);
    }
    return green_added;
}

Processing overlay(Processing& top_layer, Processing& bottom_layer) {
    Processing overlayed = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel bottom_pixel = bottom_layer.pixel.at(i);

        Processing::Pixel overlayed_pixel;
        float check = ((float)bottom_pixel.color / 255.0f);
        float top = (float)top_pixel.color / 255.0f;
        float bottom = (float)bottom_pixel.color / 255.0f;
        if (bottom <= 0.5f) {
           overlayed_pixel.color = 2 * top * bottom * 255.0f + 0.5f;
        } else if(bottom > 0.5f){
           overlayed_pixel.color = (1 - 2 * (1 - top) * (1 - bottom)) * 255.0f + 0.5f;
        }
        if (overlayed_pixel.color > 255.0f) {
            overlayed_pixel.color = 255;
        } else if (overlayed_pixel.color < 0.0f) {
            overlayed_pixel.color = 0;
        }
        overlayed.pixel.push_back(overlayed_pixel);
    }
    return overlayed;
}

Processing screen(Processing& top_layer, Processing& bottom_layer) {
    Processing screened = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel bottom_pixel = bottom_layer.pixel.at(i);

        Processing::Pixel screened_pixel;
        float temp;
        temp = (1-((1-((float)top_pixel.color/255.0f))*(1-((float)bottom_pixel.color/255.0f))))*255.0f+0.5f;
        screened_pixel.color = temp;

        if (screened_pixel.color > 255) {
            screened_pixel.color = 255;
        } else if (screened_pixel.color < 0) {
            screened_pixel.color = 0;
        }
        screened.pixel.push_back(screened_pixel);
    }
    return screened;
}

Processing subtract(Processing& top_layer, Processing& bottom_layer) {
    Processing subtracted = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel bottom_pixel = bottom_layer.pixel.at(i);

        Processing::Pixel subtracted_pixel;
        int temp;
        temp = (float)top_pixel.color - (float)bottom_pixel.color;
        if (temp < 0) {
            temp = 0;
        }
        subtracted_pixel.color = temp;
        subtracted.pixel.push_back(subtracted_pixel);
    }
    return subtracted;
}

Processing multiply(Processing& top_layer, Processing& bottom_layer) {
    Processing multiplied = top_layer.getHeader();
    for(int i = 0; i < top_layer.pixel.size(); i++) {
        Processing::Pixel top_pixel = top_layer.pixel.at(i);
        Processing::Pixel bottom_pixel = bottom_layer.pixel.at(i);

        Processing::Pixel multiplied_pixel;
        float temp;
        temp = (((float)top_pixel.color / 255.0f) *((float)bottom_pixel.color / 255.0f)*255.0f+0.5f);
        if(temp > 255) {
            temp = 255;
        }
        multiplied_pixel.color = temp;
        multiplied.pixel.push_back(multiplied_pixel);
    }
    return multiplied;
}

Processing ReadHeader(const string& TGA_file) {
    ifstream read_header(TGA_file, ios::binary);
    if (read_header.is_open()) {
        Processing::Header this_header;

        read_header.read(&this_header.idlength, sizeof(this_header.idlength));
        read_header.read(&this_header.colorMapType, sizeof(this_header.colorMapType));
        read_header.read(&this_header.dataTypeCode, sizeof(this_header.dataTypeCode));
        read_header.read((char*)&this_header.colorMapOrigin, sizeof(this_header.colorMapOrigin));
        read_header.read((char*)&this_header.colorMapLength, sizeof(this_header.colorMapLength));
        read_header.read(&this_header.colorMapDepth, sizeof(this_header.colorMapDepth));
        read_header.read((char*)&this_header.xOrigin, sizeof(this_header.xOrigin));
        read_header.read((char*)&this_header.yOrigin, sizeof(this_header.yOrigin));
        read_header.read((char*)&this_header.width, sizeof(this_header.width));
        read_header.read((char*)&this_header.height, sizeof(this_header.height));
        read_header.read(&this_header.bitsPerPixel, sizeof(this_header.bitsPerPixel));
        read_header.read(&this_header.imageDescriptor, sizeof(this_header.imageDescriptor));

        Processing tga = Processing(this_header);
        vector<Processing::Pixel> list;
        for(int i = 0; i < (this_header.width * this_header.height * 3); i++) {
            Processing::Pixel this_pixel;
            read_header.read((char*)&this_pixel.color, sizeof(this_pixel.color));
            list.push_back(this_pixel);
        }
        tga.pixel = list;
        read_header.close();
        return tga;
    } else {
        cout << "header not read or opened properly" << endl;
        return Processing();
    }
}

bool write_File(string file_name, Processing& tga) {
    ofstream write_file(file_name, ios::binary);
    if (write_file.is_open()) {
        Processing::Header this_header = tga.getHeader();
        write_file.write(&this_header.idlength, sizeof(this_header.idlength));
        write_file.write(&this_header.colorMapType, sizeof(this_header.colorMapType));
        write_file.write(&this_header.dataTypeCode, sizeof(this_header.dataTypeCode));
        write_file.write((char*)&this_header.colorMapOrigin, sizeof(this_header.colorMapOrigin));
        write_file.write((char*)&this_header.colorMapLength, sizeof(this_header.colorMapLength));
        write_file.write(&this_header.colorMapDepth, sizeof(this_header.colorMapDepth));
        write_file.write((char*)&this_header.xOrigin, sizeof(this_header.xOrigin));
        write_file.write((char*)&this_header.yOrigin, sizeof(this_header.yOrigin));
        write_file.write((char*)&this_header.width, sizeof(this_header.width));
        write_file.write((char*)&this_header.height, sizeof(this_header.height));
        write_file.write(&this_header.bitsPerPixel, sizeof(this_header.bitsPerPixel));
        write_file.write(&this_header.imageDescriptor, sizeof(this_header.imageDescriptor));

        for(int x = 0; x < tga.pixel.size(); x++) {
            Processing::Pixel this_pixel = tga.pixel.at(x);
            unsigned char temp = this_pixel.color;
            write_file.write((char*)&temp, sizeof(temp));
        }
        write_file.close();
        return true;
    } else {
        cout << "write file is not open" << endl;
        return false;
    }
}

#endif //INC_10_FUNCTIONS_H
