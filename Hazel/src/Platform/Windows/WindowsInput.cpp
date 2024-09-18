#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel/Application.h"
#include <GLFW/glfw3.h>


namespace Hazel {

	Input* Input::s_Instance = new WindowsInput();//通常这里初始化为nullptr 然后在Init函数中初始化,但是由于Input是完全静态的,只有一堆函数 这里可以直接初始化为new WindowsInput()

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//获取窗口指针 获取按键状态 返回判断结果
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);



		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos,(float)ypos};
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto v = GetMousePositionImpl();//C++17语法
		return std::get<0>(v);
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();//C++17语法
		return y;
	}

}

