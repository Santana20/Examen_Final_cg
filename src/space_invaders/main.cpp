#include "Game.h"

const u32 SCR_WIDTH  = 1280;
const u32 SCR_HEIGHT = 720;


f32  deltaTime  = 0.0f;
f32  lastFrame  = 0.0f;
Game game(SCR_WIDTH, SCR_HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.Keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            game.Keys[key] = false;
        }
    }
}

void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		cam->movePov(xpos, ypos);
	} else {
		cam->stopPov();
	}
}

i32 main() {
	GLFWwindow* window = glutilInit(3, 3, SCR_WIDTH, SCR_HEIGHT, "Space Invaders 3D with OpenGL");
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

    game.Init();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		f32 currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		game.ProcessInput(deltaTime);

        game.Update(deltaTime);

		game.Render(currentFrame);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
