#pragma once

#include "Entity.h"
namespace Hazel {
	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	private:
		Entity m_Entity;//�ĸ�ʵ����ڽű� �ñ����ʹ��ĸ�
		friend class Scene;
	};
}