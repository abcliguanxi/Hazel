#pragma once
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;//���������Ϳ��ԣ����ӵ�ʱ���������cpp�ļ�����

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


