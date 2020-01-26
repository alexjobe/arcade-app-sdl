//
// Created by alex on 1/25/20.
//

#ifndef GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H
#define GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H

#include "Block.h"
#include <vector>
#include <cstdint>

class Screen;
class Ball;
class AARectangle;

class BreakOutGameLevel
{
public:
    BreakOutGameLevel();
    void Init(const AARectangle& boundary);
    void Load(const std::vector<Block>& blocks);
    void Update(uint32_t dt, Ball& ball);
    void Draw(Screen& screen);
    bool IsLevelComplete() const;

    static std::vector<BreakOutGameLevel> LoadLevelsFromFile(const std::string& filePath);
private:
    static const int BLOCK_WIDTH = 16;
    static const int BLOCK_HEIGHT = 8;
    std::vector<Block> mBlocks;
    void CreateDefaultLevel(const AARectangle& boundary);
};

#endif //GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H
