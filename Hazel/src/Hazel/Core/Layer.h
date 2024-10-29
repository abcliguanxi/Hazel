#pragma once
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		//当层推入层堆 成为程序一部分时 被Attached
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}


