#pragma once
#include <memory>

#include "Drawable.h"
#include "Material.h"
#include "glm/glm.hpp"
#include "SimpleModel.h"
#include "Mesh.h"


class Block : public Drawable
{
public:
    Block();
    Block(glm::vec3 pos);

    virtual void Bind() override;
    virtual unsigned int GetSize() override;
    std::shared_ptr<Material> GetMaterial();

protected:
    glm::vec3 position;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<SimpleModel> m_model;
    std::shared_ptr<Mesh> m_mesh;
    std::string cubeModelFile = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\Cube.smodel";
    std::string vertexShader = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\VertexShader.glsl";
    std::string fragmentShader = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FragmentShader.glsl";
};

