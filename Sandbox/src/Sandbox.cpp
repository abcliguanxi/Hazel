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

//����һ������
Hazel::Application* Hazel::CreateApplication() 
{
	return new Sandbox();
}