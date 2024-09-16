#pragma once
#include <memory>
#include "Material.h"

class Drawable
{
public:
    
    virtual void Bind() = 0;
    virtual unsigned int GetSize() = 0;
    virtual std::shared_ptr<Material> GetMaterial() = 0;

    // maybe do something like GetMaterial for batch rendering in the future?
};

