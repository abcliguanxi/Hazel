#include "hzpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "mono/metadata/object.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/Input.h"

namespace Hazel {

#define HZ_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Hazel.InternalCalls::" #Name, Name)

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << ", " << parameter << std::endl;
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		//HZ_CORE_WARN("Value: {0}", *parameter);
		*outResult = glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		//HZ_CORE_WARN("Value: {0}", *parameter);
		return glm::dot(*parameter, *parameter);
	}

	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		HZ_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		HZ_CORE_ASSERT(entity);

		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		HZ_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		HZ_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	//static float NativeLog_VectorDot(glm::vec3* parameter)
	//{
	//	//HZ_CORE_WARN("Value: {0}", *parameter);
	//	return glm::dot(*parameter, *parameter);
	//}

	void ScriptGlue::RegisterFunctions()
	{
		HZ_ADD_INTERNAL_CALL(NativeLog);//将函数注册为C#可调用的函数
		//HZ_ADD_INTERNAL_CALL(NativeLog_Vector);
		//HZ_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		HZ_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		HZ_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
		HZ_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}
