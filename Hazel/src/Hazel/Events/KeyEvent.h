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
		//����㲻����������û�ֱ�ӹ���һ��KeyEvent�Ķ���
		//ϣ���û�ֻ�ܹ���KeyEvent�����࣬����Ϳ��Խ�KeyEvent�Ĺ��캯�� / ������������Ϊprotected
		//����KeyEvent������Ĺ��캯�� / ������������Ϊpublic
		KeyEvent(const KeyCode keycode) 
			: m_KeyCode(keycode){}
		KeyCode m_KeyCode;
	};

	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		/*static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }*/
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		bool m_IsRepeat;
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