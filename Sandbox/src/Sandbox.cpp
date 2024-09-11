#include <Hazel.h>


class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}
};

//定义一个函数
Hazel::Application* Hazel::CreateApplication() 
{
	return new Sandbox();
}