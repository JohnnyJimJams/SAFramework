#include "DemoPlayer.h"
#include "Texture2D.h"
#include "ShaderProgram.h"

DemoPlayer::DemoPlayer(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
}

DemoPlayer::~DemoPlayer()
{
}

void DemoPlayer::Start()
{
	// Editor Init
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "SAInvite", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// OpenGL loader
	gl3wInit();

	m_demo = new Demo(m_width, m_height, L"..\\resources\\TDIME.mp3");

	glfwSetKeyCallback(m_window, glfw_key_callback);
	glfwSetCharCallback(m_window, glfw_char_callback);
	glfwSetMouseButtonCallback(m_window, glfw_mousebutton_callback);
	glfwSetCursorPosCallback(m_window, glfw_mousepos_callback);
	glfwSetScrollCallback(m_window, glfw_mousewheel_callback);

	// Benny Init Shit *****
	Texture2D *texture = new Texture2D("..\\resources\\smiley.jpg");
	ShaderProgram *shaderFullScreenQuad = new ShaderProgram();
	shaderFullScreenQuad->CompileFromFile(GL_VERTEX_SHADER, "..\\resources\\layer.vert");
	shaderFullScreenQuad->CompileFromFile(GL_FRAGMENT_SHADER, "..\\resources\\layer.frag");
	shaderFullScreenQuad->LinkProgram();
	unsigned int uniFullScreenQuadTime = shaderFullScreenQuad->GetUniform("time");
	unsigned int uniFullScreenQuadResolution = shaderFullScreenQuad->GetUniform("resolution");
	unsigned int uniFullScreenQuadTex0 = shaderFullScreenQuad->GetUniform("tex0");
	// End Benny *****

	// Main loop!
	Play(); // audio
	bool show_demo_window = true;
	while (!glfwWindowShouldClose(m_window))
	{
		m_demo->Tick(m_demo->GetMusicSecondsNow());

		// Rendering
		int display_w, display_h;
		glfwMakeContextCurrent(m_window);
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_demo->Tick(m_demo->GetMusicSecondsNow()); // run keyframe animations if any

		// Benny Render Shit *****
		shaderFullScreenQuad->Bind();
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();
		glUniform1f(uniFullScreenQuadTime, (float)m_demo->GetMusicSecondsNow());
		glUniform2f(uniFullScreenQuadResolution, (float)m_demo->GetWidth(), (float)m_demo->GetHeight());
		glUniform1i(uniFullScreenQuadTex0, 0); // Tex1 in slot 0
		m_demo->DrawFullScreenQuad();
		texture->Unbind();
		shaderFullScreenQuad->Unbind();
		// End Benny *****

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	// Cleanup
	glfwDestroyWindow(m_window);
}

unsigned int DemoPlayer::GetWidth()
{
	return m_width;
}

unsigned int DemoPlayer::GetHeight()
{
	return m_height;
}

void DemoPlayer::Play()
{
	m_demo->GetAudio()->Play();
}

double DemoPlayer::GetMusicSecondsNow()
{
	return m_demo->GetMusicSecondsNow();
}

void DemoPlayer::SetMusicSeconds(double time)
{
	__int64 start =(__int64) (time * 10000000.0);
	__int64 end = m_demo->GetAudio()->GetDuration();

	m_demo->GetAudio()->SetPositions(&start, &end, true);
}

double DemoPlayer::GetMusicSecondsTotal()
{
	return m_demo->GetMusicSecondsTotal();
}

Entity* DemoPlayer::GetEntityByName(std::string name)
{
	Entity* entity = nullptr;
	for (auto layer : m_demo->GetLayers())
	{
		for (auto entity : *layer->GetEntities())
		{
			entity = layer->FindEntityByNameRecursively(name, entity);
			if (entity != nullptr)
			{
				break;
			}
		}
	}
	return entity;
}

Demo * DemoPlayer::GetDemo()
{
	return m_demo;
}


void DemoPlayer::glfw_error_callback(int error, const char * description)
{
}

void DemoPlayer::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void DemoPlayer::glfw_char_callback(GLFWwindow * window, unsigned int codepoint)
{
}

void DemoPlayer::glfw_mousebutton_callback(GLFWwindow * window, int button, int action, int mods)
{
}

void DemoPlayer::glfw_mousepos_callback(GLFWwindow * window, double xpos, double ypos)
{
}

void DemoPlayer::glfw_mousewheel_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
