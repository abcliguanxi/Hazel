#pragma once

#include "Entity.h"
namespace Hazel {
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() = default;
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;//哪个实体挂载脚本 该变量就存哪个
		friend class Scene;
	};
}
