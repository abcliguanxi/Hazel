
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

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);//���ڵ��û�����Ϊ WindowData ���͵�ָ��
		SetVSync(true);//��ֱͬ������Ϊ��

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//�ص������л�ȡ�� WindowData ��������ã��������˴��ڵĿ�Ⱥ͸߶ȡ�
				//������һ�� WindowResizeEvent ���󣬲�ͨ�� EventCallback ������������¼���
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);// void*ָ��ǿ��ת��Ϊ WindowData ���͵�ָ�룬��������������ȡ�� WindowData ���������
				data.Width = width;
				data.Height = height;

				//���������ڴ�С�ı��¼����¼��ᱻ��һ����������֪ͨ�¼���������
				WindowResizeEvent event(width, height);
				data.EventCallback(event);//�����¼�����ص�����
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//�ص������л�ȡ�� WindowData ��������ã��������˴��ڵĿ�Ⱥ͸߶ȡ�
				//������һ�� WindowResizeEvent ���󣬲�ͨ�� EventCallback ������������¼���
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);// void*ָ��ǿ��ת��Ϊ WindowData ���͵�ָ�룬��������������ȡ�� WindowData ���������
				data.Width = width;
				data.Height = height;

				//���������ڴ�С�ı��¼����¼��ᱻ��һ����������֪ͨ�¼���������
				WindowResizeEvent event(width, height);
				data.EventCallback(event);//�����¼�����ص�����
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
				//ת����������
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
				//ת����������
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