#include "GrassBlock.h"

GrassBlock::GrassBlock() : GrassBlock(glm::vec3(0.0f, 0.0f, 0.0f)) {}

GrassBlock::GrassBlock(glm::vec3 pos) : Block(pos) {
    this->m_material->SetTexture(this->grassBlockSideImage);
    this->m_material->SetBlend(1.0f);
}