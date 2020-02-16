//
// Created by alex on 2/12/20.
//

#ifndef GRAPHICS_BMPIMAGE_H
#define GRAPHICS_BMPIMAGE_H

#include "Color.h"
#include <vector>
#include <stdint.h>
#include <string>

class BMPImage {
public:
    BMPImage();
    bool Load(const std::string& path);
    inline const std::vector<Color>& GetPixels() const { return mPixels; }
    inline uint32_t GetWidth() const { return mWidth; }
    inline uint32_t GetHeight() const {return mHeight; }
private:
    std::vector<Color> mPixels;
    uint32_t mWidth;
    uint32_t mHeight;
};

#endif //GRAPHICS_BMPIMAGE_H
