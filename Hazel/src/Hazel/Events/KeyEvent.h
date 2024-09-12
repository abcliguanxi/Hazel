#pragma once

#include <sstream>
#include "Event.h"

namespace Hazel {
	//�����¼�(���£�����)�й�ͬ�İ����� ����һ��KeyEvent����
	class HAZEL_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		
		//�����¼��������¼������ڼ����¼�
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//����㲻����������û�ֱ�ӹ���һ��KeyEvent�Ķ���
		//ϣ���û�ֻ�ܹ���KeyEvent�����࣬����Ϳ��Խ�KeyEvent�Ĺ��캯�� / ������������Ϊprotected
		//����KeyEvent������Ĺ��캯�� / ������������Ϊpublic
		KeyEvent(int keycode) : m_KeyCode(m_KeyCode){}
		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode,int repeatCount): KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats";
			return ss.str();
		}

		/*static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }*/
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}