
#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Log.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	//定义Window里面的Create
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		//在shutdown里面关闭
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Create window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width,(int) props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);//垂直同步设置为真

	}

	

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();//拉取事件
		glfwSwapBuffers(m_Window);//交换缓冲区
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);//这里必须是1 1只是意味着每次渲染下一帧前都会等待一次同步
		else
			glfwSwapInterval(0);//0意味着不等待

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}