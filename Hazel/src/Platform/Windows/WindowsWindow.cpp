
#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Log.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	//����Window�����Create
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		//��shutdown����ر�
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
		SetVSync(true);//��ֱͬ������Ϊ��

	}

	

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();//��ȡ�¼�
		glfwSwapBuffers(m_Window);//����������
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);//���������1 1ֻ����ζ��ÿ����Ⱦ��һ֡ǰ����ȴ�һ��ͬ��
		else
			glfwSwapInterval(0);//0��ζ�Ų��ȴ�

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