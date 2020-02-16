//
// Created by alex on 2/12/20.
//
#include "BMPImage.h"
#include <SDL2/SDL.h>
#include <iostream>

BMPImage::BMPImage() : mWidth(0), mHeight(0)
{

}

bool BMPImage::Load(const std::string& path)
{
    SDL_Surface* bmpSurface = SDL_LoadBMP(path.c_str());

    if(bmpSurface == nullptr)
    {
        std::cout << "Image not found: " << path << std::endl;
        return false;
    }

    mWidth = bmpSurface->w;
    mHeight = bmpSurface->h;

    size_t numPixels = mWidth * mHeight;

    mPixels.reserve(numPixels);

    SDL_LockSurface(bmpSurface);

    auto* pixels = static_cast<uint32_t *>(bmpSurface->pixels);

    for(uint32_t i = 0; i < numPixels; ++i)
    {
        mPixels.emplace_back(Color(pixels[i]));
    }

    SDL_UnlockSurface(bmpSurface);
    SDL_FreeSurface(bmpSurface);

    return true;
}


