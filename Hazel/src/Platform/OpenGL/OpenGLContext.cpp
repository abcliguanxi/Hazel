#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Hazel
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		//成功后想要获取显卡信息
		
		HZ_CORE_INFO("OpengGL Info:");

		HZ_CORE_INFO("    Vendor: {0}", (char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("    Version: {0}", (char*)glGetString(GL_VERSION));
		

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);//交换缓冲区
	}

}
