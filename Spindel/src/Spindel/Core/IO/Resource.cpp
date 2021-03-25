#include "sppch.h"

#include "Spindel/Core/IO/Resource.h"
#include "Spindel/Core/Core.h"

#include <stdio.h>

namespace Spindel
{
	Resource::Resource()
	{
	}

	Resource::~Resource() {
		if (m_Path_Name != "") {
		}
		/*if (owners.size()) {
			WARN_PRINT("Resource is still owned.");
		}*/
	}

	const std::string& Resource::GetPath() const {
		return m_Path_Name;
	}

	void Resource::SetPath(const std::string& p_path) {
		m_Path_Name = p_path;
	}

	void Resource::SetSubindex(int p_sub_index) {
		subindex = p_sub_index;
	}

	int Resource::GetSubindex() const {
		return subindex;
	}

	void Resource::SetName(const std::string& p_name) {
		m_Name = p_name;
	}

	const std::string& Resource::GetName() const {
		return m_Name;
	}

}