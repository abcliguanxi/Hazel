#pragma once
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;//这里声明就可以，链接的时候会在其他cpp文件中找

namespace Hazel {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}


