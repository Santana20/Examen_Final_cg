#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <files.hpp>
#include <model.hpp>
#include <cam.hpp>

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_OVER
};



Cam* cam;
Files* files;
Shader* shader;
class Model* playerNave;


class Game
{
public:
    // game state
    GameState State;	
    bool Keys[1024];
    unsigned int Width, Height;
    // constructor/destructor
    Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}
    ~Game()
    {
        delete cam;
	    delete shader;
	    delete playerNave;
        delete files;
    }
    // initialize game state (load all shaders/textures/levels)
    void Init()
    {
        cam = new Cam(glm::vec3(0.0f, 0.0f, 5.0f));

        files = new Files("bin", "resources/textures", "resources/objects");

        shader = new Shader(files, "shader.vert", "shader.frag");
        playerNave = new class Model(files, "nave/nave.obj");
    }
    // game loop
    void ProcessInput(float currentFrame)
    {
        
    }
    void Update(float currentFrame)
    {
        glm::vec3 lightPos   = glm::vec3(1.0f);
	    glm::vec3 lightColor = glm::vec3(1.0f);

        shader->use();
		lightPos.x = 2.0f*(cos(currentFrame) - sin(currentFrame));
		lightPos.z = 2.0f*(cos(currentFrame) + sin(currentFrame));
		shader->setVec3("xyz", lightPos);
		shader->setVec3("xyzColor", lightColor);
		shader->setVec3("xyzView", cam->pos);
		glm::mat4 proj = glm::perspective(cam->zoom, (f32)Width / (f32)Height, 0.1f, 100.0f);
		shader->setMat4("proj", proj);
		shader->setMat4("view", cam->getViewM4());
    }
    void Render()
    {
        glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
        //rotate y
		model = glm::rotate(model, (float)M_PI, {0.0f, 1.0f, 0.0f});
        //rotate x
		model = glm::rotate(model, (float)M_PI / 2, {-1.0f, 0.0f, 0.0f});
		model = glm::scale(model, glm::vec3(0.2f));

		shader->setMat4("model", model);

		playerNave->Draw(shader);
    }
};

#endif