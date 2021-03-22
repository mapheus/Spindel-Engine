#pragma once

#include <string>

#include <random>

namespace Spindel
{
	class Asset
	{
	public:
		Asset(const std::string& name, const std::string& dir)
			: m_Name(name), m_Directory(dir) {
			m_Id = rand();
		}

		const std::string& GetName() const { return m_Name; }
		const std::string& GetDirectory() const { return m_Directory; }
	private:
		std::string m_Name;
		std::string m_Directory;
		unsigned int m_Id;
	};
}