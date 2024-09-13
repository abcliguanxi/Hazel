#pragma once
#include "Core.h"
#include "Window.h"
#include "Hazel/Events/AplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		~Application();
		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in Client
	Application* CreateApplication();
}


