#pragma once

#ifdef HZ_PALTFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();//��ĳ���ط�����ĺ����᷵��ʵ�ʵ�Ӧ�ó���
int main(int argc,char** argv) {

	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	HZ_INFO("Hello! var={0}",5);


	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Hazel only supports Windows!
#endif // HZ_PLATFORM_WINDOWS

