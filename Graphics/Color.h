//
// Created by alex on 12/2/19.
//

#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <cstdint>

struct SDL_PixelFormat;

class Color
{
public:

    static const SDL_PixelFormat* mFormat;
    static void InitColorFormat(const SDL_PixelFormat* format);

    // Blending equation
    // SourceRGB * sourceAlpha + DestinationRGB * (1 - sourceAlpha)
    static Color EvaluateOneMinusSourceAlpha(const Color& source, const Color& destination);

    static Color Black() { return {0, 0, 0, 255}; }
    static Color White() { return {255, 255, 255, 255}; }
    static Color Blue() { return {0, 0, 255, 255}; }
    static Color Red() { return {255, 0, 0, 255}; }
    static Color Green() { return {0, 255, 0, 255}; }
    static Color Yellow() { return {255, 255, 0, 255}; }
    static Color Magenta() { return {255, 0, 255, 255}; }
    static Color Cyan() { return {37, 240, 217, 255}; }
    static Color Pink() { return {252, 197, 224, 255}; }
    static Color Orange() { return {245, 190, 100, 255}; }

    Color(): Color(0){}
    explicit Color(uint32_t color): mColor(color){}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    inline bool operator==(const Color& c) const { return mColor == c.mColor; }
    inline bool operator!=(const Color& c) const { return mColor != c.mColor; }
    inline uint32_t GetPixelColor() const { return mColor; }

    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void SetRed(uint8_t red);
    void SetGreen(uint8_t green);
    void SetBlue(uint8_t blue);
    void SetAlpha(uint8_t alpha);

    uint8_t GetRed() const;
    uint8_t GetGreen() const;
    uint8_t GetBlue() const;
    uint8_t GetAlpha() const;

private:
    uint32_t mColor;
};

#endif //GRAPHICS_COLOR_H
