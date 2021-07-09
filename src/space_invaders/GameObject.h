#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <model.hpp>


class GameObject
{
public:
    glm::vec2 Position, Size, Velocity;
    bool Destroyed;
    
    Model* model;

    GameObject() : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Destroyed(false), model() { }
    GameObject(glm::vec2 pos, glm::vec2 size, Model* model, glm::vec2 velocity = glm::vec2(0.0f, 0.0f)) : Position(pos), Size(size), Velocity(velocity), Destroyed(false), model(model) { }
    
    virtual ~GameObject()
    {
        if (model != nullptr) delete model;
    }
    virtual void Draw(Shader* shader)
    {
        model->Draw(shader);
    }
};

#endif