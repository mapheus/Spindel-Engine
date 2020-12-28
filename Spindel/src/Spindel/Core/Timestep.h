#pragma once

namespace Spindel {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}

		double GetSeconds() const { return m_Time; }
		double GetMilliseconds() const { return m_Time * 1000.f; }
	private:
		double m_Time;
	};
}