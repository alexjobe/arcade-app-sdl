//
// Created by alex on 1/25/20.
//

#include "BreakOutGameLevel.h"
#include "Ball.h"
#include "App.h"
#include "FileCommandLoader.h"

BreakOutGameLevel::BreakOutGameLevel()
{

}

void BreakOutGameLevel::Init(const AARectangle& boundary)
{
    CreateDefaultLevel(boundary);
}

void BreakOutGameLevel::Load(const std::vector<Block>& blocks)
{
    mBlocks.clear();
    mBlocks = blocks;
}

void BreakOutGameLevel::Update(uint32_t dt, Ball& ball)
{
    std::vector<Block> collidedBlocks;

    BoundaryEdge edgeToBounceOff;
    Block* noptrBlockToBounceOff = nullptr;

    float largestMag = -1.0f;

    for(auto& block : mBlocks)
    {
        BoundaryEdge edge;
        if(!block.IsDestroyed() && block.HasCollided(ball.GetBoundingRect(), edge))
        {
            collidedBlocks.push_back(block);

            float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();

            // The ball should bounce off the block it collides with the most
            if(mag > largestMag)
            {
                edgeToBounceOff = edge;
                noptrBlockToBounceOff = &block;
            }
        }
    }

    if(noptrBlockToBounceOff != nullptr)
    {
        noptrBlockToBounceOff->Bounce(ball, edgeToBounceOff);
        noptrBlockToBounceOff->ReduceHP();
    }

    for(const auto& block : collidedBlocks)
    {
        BoundaryEdge edge;
        if(block.HasCollided(ball.GetBoundingRect(), edge))
        {
            Vec2D pointOnEdge;
            // If ball is still colliding with any blocks, make flush with blocks
            ball.MakeFlushWithEdge(edge, pointOnEdge, true);
        }
    }

}

void BreakOutGameLevel::Draw(Screen& screen)
{
    for(auto& block : mBlocks)
    {
        if(!block.IsDestroyed())
        {
            block.Draw(screen);
        }
    }
}

void BreakOutGameLevel::CreateDefaultLevel(const AARectangle& boundary)
{
    mBlocks.clear();

    const int NUM_BLOCKS_ACROSS = ((int)boundary.GetWidth() - (2 * (BLOCK_WIDTH)) / BLOCK_WIDTH);
    const int NUM_BLOCK_ROWS = 5;

    float startX = ((int)boundary.GetWidth() - (NUM_BLOCKS_ACROSS * (BLOCK_WIDTH + 1))) / 2;

    Color colors[NUM_BLOCK_ROWS];
    colors[0] = Color::Cyan();
    colors[1] = Color::Yellow();
    colors[2] = Color::Green();
    colors[3] = Color::Magenta();
    colors[4] = Color::Red();

    for(int r = 0; r < NUM_BLOCK_ROWS; ++r)
    {
        AARectangle blockRect = { Vec2D(startX, BLOCK_HEIGHT * (r + 1)), BLOCK_WIDTH, BLOCK_HEIGHT};

        for(int c = 0; c < NUM_BLOCKS_ACROSS; ++c)
        {
            Block block;
            block.Init(blockRect, 1, Color::Black(), colors[r]);
            mBlocks.push_back(block);
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    }
}

struct LayoutBlock
{
    char symbol = '-';
    int hp = 0;
    Color color = Color::Black();
};

LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol)
{
    for(auto block : blocks)
    {
        if(block.symbol == symbol)
        {
            return block;
        }
    }

    return {};
}

std::vector<BreakOutGameLevel> BreakOutGameLevel::LoadLevelsFromFile(const std::string& filePath)
{
    std::vector<BreakOutGameLevel> levels;

    std::vector<LayoutBlock> layoutBlocks;
    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader fileLoader;
    Command levelCommand;
    levelCommand.command = "level";
    levelCommand.parseFunc = [&](ParseFuncParams params)
    {
        if(levels.size() > 0)
        {
            levels.back().Load(levelBlocks);
        }
        layoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;

        BreakOutGameLevel level;
        level.Init(AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()));

        levels.push_back(level);
    };

    fileLoader.AddCommand(levelCommand);

    Command blockCommand;
    blockCommand.command = "block";
    blockCommand.parseFunc = [&](ParseFuncParams params)
    {
        LayoutBlock layoutBlock;
        layoutBlocks.push_back(layoutBlock);
    };

    fileLoader.AddCommand(blockCommand);

    Command symbolCommand;
    symbolCommand.command = "symbol";
    symbolCommand.parseFunc = [&](ParseFuncParams params)
    {
        layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
    };

    fileLoader.AddCommand(symbolCommand);

    Command fillColorCommand;
    fillColorCommand.command = "fillcolor";
    fillColorCommand.parseFunc = [&](ParseFuncParams params)
    {
        layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
    };

    fileLoader.AddCommand(fillColorCommand);

    Command hpCommand;
    hpCommand.command = "hp";
    hpCommand.parseFunc = [&](ParseFuncParams params)
    {
        layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(hpCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseFuncParams params)
    {
        width = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseFuncParams params)
    {
        height = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(heightCommand);

    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.command = "layout";
    layoutCommand.parseFunc = [&](ParseFuncParams params)
    {
        int blockWidth = BLOCK_WIDTH;
        int screenWidth = App::Singleton().Width();

        float startingX = 0;
        AARectangle blockRect(Vec2D(startingX, (params.lineNum + 1) * BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);

        for(int c = 0; c < params.line.length(); ++c)
        {
            if(params.line[c] != '-')
            {
                LayoutBlock layoutBlock = FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);

                Block block;
                block.Init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
                levelBlocks.push_back(block);
            }

            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    };

    fileLoader.AddCommand(layoutCommand);

    fileLoader.LoadFile(filePath);

    if(!levels.empty())
    {
        levels.back().Load(levelBlocks);
    }

    return levels;
}

bool BreakOutGameLevel::IsLevelComplete() const
{
    for(const auto& mBlock : mBlocks)
    {
        if(!mBlock.IsDestroyed() && mBlock.GetHP() != Block::UNBREAKABLE)
        {
            return false;
        }
    }

    return true;
}
