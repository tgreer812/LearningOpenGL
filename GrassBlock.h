#pragma once
#include <string>
#include "Block.h"

class GrassBlock : public Block
{
public:
    GrassBlock();
    GrassBlock(glm::vec3 pos);

private:
    std::string grassBlockSideImage = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\GrassBlockSide.png";
};

