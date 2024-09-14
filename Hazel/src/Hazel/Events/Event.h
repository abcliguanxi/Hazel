#pragma once
#include "Hazel/Core.h"
#include "spdlog/fmt/ostr.h"


namespace Hazel {
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// ö���� ����ʱ�������
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//������Ҫ����ĳЩ�¼� ������λ����������һ���¼����ڶ��category
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
		//friend class EventDispatcher;//��Ԫ�࣬���Է��ʵ�ǰEvent�µ�protected����
		
	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// ��ѯ��ǰ�¼��Ƿ����ڸ���������
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	//protected:
	//	bool m_Handled = false;//�鿴�¼��Ƿ񱻴���
	};

	//�¼�������
	/*
	* ��δ������Ҫ�������ṩһ��ͨ�õ��¼��ַ����ƣ������Ը����¼����͵�����Ӧ���¼���������
	����¼���������������� T ƥ�䣬��ô�ͽ��¼�ת��Ϊ T ���Ͳ������¼������� func��
	����¼�����������һ��ֵ����ô���ֵ�������浽�¼������ m_Handled �ֶ��У���ʾ�¼��Ƿ񱻴���
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
				m_Event.Handled = func(*(T*)&m_Event); //����� *(T*)&m_Event ��һ������ת������ m_Event ת��Ϊ T ���͵�����
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;//�����ڶ���ʱ�����ʼ�� ��˹��캯�������ʼ����ֵ(��ʼ�������ڳ�Ա��ʼ�����������)
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
