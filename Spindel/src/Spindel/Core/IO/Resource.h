#pragma once

#include <string>
#include <unordered_map>
#include <List>

namespace Spindel
{
	class Resource {
	public:
		Resource();
		~Resource();


		void SetName(const std::string& p_name);
		const std::string& GetName() const;

		virtual void SetPath(const std::string& p_path);
		const std::string& GetPath() const;

		void SetSubindex(int p_sub_index);
		int GetSubindex() const;

	private:
		std::string m_Name;
		std::string m_Path_Name;
		int subindex = 0;

	};


}