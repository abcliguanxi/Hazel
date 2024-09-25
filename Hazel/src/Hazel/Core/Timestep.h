#pragma once

namespace Hazel
{
	class Timestep
	{
	public:
		Timestep(float time)
			: m_Time(time)
		{

		}

		operator float() { return m_Time; }//ÖØÔØÔËËã·û

		float GetSeconds() const { return m_Time; }
		float GetMulliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}
