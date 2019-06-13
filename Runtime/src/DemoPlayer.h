#pragma once
#include <stdio.h>
#include "Demo.h"
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

class DemoPlayer
{
public:
	DemoPlayer(unsigned int width, unsigned int height);
	virtual ~DemoPlayer();

	void Start();
	unsigned int GetWidth();
	unsigned int GetHeight();

	Demo *GetDemo();

	void Play();
	void Stop();
	double GetMusicSecondsNow();
	void SetMusicSeconds(double time);
	double GetMusicSecondsTotal();

	Entity* GetEntityByName(std::string name);

private:
	GLFWwindow* m_window;
	Demo *m_demo;

	unsigned int m_width;
	unsigned int m_height;
	GLfloat m_backgroundColor[3] = { .02f, .02f, 0.05f };

	static void glfw_error_callback(int error, const char* description);
	static void glfw_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void glfw_char_callback(GLFWwindow * window, unsigned int codepoint);
	static void glfw_mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
	static void glfw_mousepos_callback(GLFWwindow* window, double xpos, double ypos);
	static void glfw_mousewheel_callback(GLFWwindow* window, double xoffset, double yoffset);
};

