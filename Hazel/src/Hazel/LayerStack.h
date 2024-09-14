#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;//需要正向和反向遍历，插入，因此用vector
		std::vector<Layer*>::iterator m_LayerInsert;

	};
}


