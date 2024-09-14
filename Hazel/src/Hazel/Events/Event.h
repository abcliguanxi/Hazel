#pragma once
#include "Hazel/Core.h"
#include "spdlog/fmt/ostr.h"


namespace Hazel {
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// 枚举类 描述时间的类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//可能想要过滤某些事件 利用移位操作可以让一个事件属于多个category
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		//friend class EventDispatcher;//友元类，可以访问当前Event下的protected对象
		
	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// 查询当前事件是否属于给定的类型
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	//protected:
	//	bool m_Handled = false;//查看事件是否被处理
	};

	//事件调度器
	/*
	* 这段代码的主要作用是提供一个通用的事件分发机制，它可以根据事件类型调用相应的事件处理函数。
	如果事件类型与给定的类型 T 匹配，那么就将事件转换为 T 类型并调用事件处理函数 func。
	如果事件处理函数返回一个值，那么这个值将被保存到事件对象的 m_Handled 字段中，表示事件是否被处理。
	*/
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event); //这里的 *(T*)&m_Event 是一个类型转换，将 m_Event 转换为 T 类型的引用
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;//引用在定义时必须初始化 因此构造函数必须初始化该值(初始化必须在成员初始化链表内完成)
	};

	template <typename T>
	struct fmt::formatter<T, std::enable_if_t<std::is_base_of<Hazel::Event, T>::value, char>> :
		fmt::formatter<std::string> {
		template <typename FormatCtx>
		auto format(const Hazel::Event& a, FormatCtx& ctx) const {
			return fmt::formatter<std::string>::format(a.ToString(), ctx);
		}
	};

}


//template <typename T>
//struct fmt::formatter<T, std::enable_if_t<std::is_base_of<Hazel::Event, T>::value, char>> :
//	fmt::formatter<std::string> {
//	template <typename FormatCtx>
//	auto format(const Hazel::Event& a, FormatCtx& ctx) const {
//		return fmt::formatter<std::string>::format(a.ToString(), ctx);
//	}
//};
