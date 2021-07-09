#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <files.hpp>
#include <model.hpp>
#include <cam.hpp>
#include "GameObject.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_OVER
};



Cam* cam;
Files* files;
Shader* shader;
GameObject* playerNave;

const float width_game = 7.0f;

// Initial velocity of the player
const float PLAYER_VELOCITY(2.0f);

const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);

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
        cam = new Cam(glm::vec3(0.0f, 3.5f, 10.0f));

        files = new Files("bin", "resources/textures", "resources/objects");

        shader = new Shader(files, "shader.vert", "shader.frag");

        glm::vec2 playerPos = glm::vec2(0.0f, 0.0f);
        Model* playerModel = new class Model(files, "nave/nave.obj");
        playerNave = new GameObject(playerPos, PLAYER_SIZE, playerModel);
                
    }
    // game loop
    void ProcessInput(float dt)
    {
        if (this->State == GAME_ACTIVE)
        {
            float velocity = PLAYER_VELOCITY * dt;
            // move playerboard
            if (this->Keys[GLFW_KEY_A])
            {
                if (playerNave->Position.x >= -width_game)
                {
                    playerNave->Position.x -= velocity;
                    
                }
            }
            if (this->Keys[GLFW_KEY_D])
            {
                if (playerNave->Position.x <= width_game)
                {
                    playerNave->Position.x += velocity;
                }
            }
        }
    }
    void Update(float dt)
    {
        
    }
    void Render(float currentFrame)
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

        glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(playerNave->Position, 0.0f));
        //rotate y
		model = glm::rotate(model, (float)M_PI, {0.0f, 1.0f, 0.0f});
        //rotate x
		model = glm::rotate(model, (float)M_PI / 2, {-1.0f, 0.0f, 0.0f});
		model = glm::scale(model, glm::vec3(0.1f));

		shader->setMat4("model", model);

		playerNave->Draw(shader);
    }
};

#endif