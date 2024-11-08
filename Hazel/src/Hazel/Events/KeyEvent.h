#pragma once

#include "Hazel/Events/Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {

	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//如果你不想让外面的用户直接构造一个KeyEvent的对象，
		//希望用户只能构造KeyEvent的子类，那你就可以将KeyEvent的构造函数 / 析构函数声明为protected
		//而将KeyEvent的子类的构造函数 / 析构函数声明为public
		KeyEvent(const KeyCode keycode) 
			: m_KeyCode(keycode){}
		KeyCode m_KeyCode;
	};

	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		uint16_t GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		/*static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }*/
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		uint16_t m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}