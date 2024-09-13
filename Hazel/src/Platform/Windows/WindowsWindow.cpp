
#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Log.h"

#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/AplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description) {
		HZ_CORE_ERROR("GLFW Error ({0}: {1})", error, description);
	}

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

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);//窗口的用户数据为 WindowData 类型的指针
		SetVSync(true);//垂直同步设置为真

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//回调函数中获取了 WindowData 对象的引用，并更新了窗口的宽度和高度。
				//创建了一个 WindowResizeEvent 对象，并通过 EventCallback 方法处理这个事件。
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);// void*指针强制转换为 WindowData 类型的指针，并解引用它，获取到 WindowData 对象的引用
				data.Width = width;
				data.Height = height;

				//并触发窗口大小改变事件。事件会被进一步处理，例如通知事件监听器。
				WindowResizeEvent event(width, height);
				data.EventCallback(event);//调用事件处理回调函数
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//回调函数中获取了 WindowData 对象的引用，并更新了窗口的宽度和高度。
				//创建了一个 WindowResizeEvent 对象，并通过 EventCallback 方法处理这个事件。
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);// void*指针强制转换为 WindowData 类型的指针，并解引用它，获取到 WindowData 对象的引用
				data.Width = width;
				data.Height = height;

				//并触发窗口大小改变事件。事件会被进一步处理，例如通知事件监听器。
				WindowResizeEvent event(width, height);
				data.EventCallback(event);//调用事件处理回调函数
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//转换按键编码
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//转换按键编码
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});


		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});
		

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMoveEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

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