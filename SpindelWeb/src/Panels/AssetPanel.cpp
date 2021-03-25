#include "sppch.h"
#include "AssetPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>

namespace Spindel
{
	AssetPanel::AssetPanel()
	{
	}

	AssetPanel::~AssetPanel()
	{
	}

	void AssetPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.1f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.2f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.1f, 0.8f, 1.0f });
		if (ImGui::Button("+", buttonSize))
		{

		}

		ImGui::PopStyleColor(3);

		ImGui::Separator();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 200);
		/*
		std::map<std::filesystem::path, std::filesystem::path> assets;
		static int selection_mask = (1 << 2);
		int node_clicked = -1;
		static std::filesystem::path currentfolder;
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());
		std::function<void(const std::filesystem::path&, unsigned int, unsigned int&)> functor = [&](
			const std::filesystem::path& path,
			unsigned int depth, unsigned int& idx) {
				for (auto&& p : std::filesystem::directory_iterator(path)) {
					ImGuiTreeNodeFlags node_flags =
						ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
						((selection_mask & (1 << idx)) ? ImGuiTreeNodeFlags_Selected : 0);
					if (std::filesystem::is_directory(p.path())) {
						using namespace std::string_literals;
						std::string s = p.path().filename().string();
						if (ImGui::TreeNodeEx((void*)(intptr_t)idx, node_flags, "%s", s.c_str())) {
							if (ImGui::IsItemClicked())
							{
								node_clicked = idx;
								currentfolder = p.path();
							}
							functor(p, depth + 1, ++idx);
							ImGui::TreePop();
						}
					}
					else {
						SP_WARN("{0}", p.path().parent_path().string());
						assets.insert({ currentfolder, p.path() });
					}
					++idx;
				}
				depth -= 1;
		};
		unsigned int dir_idx = 0u;
		functor(std::filesystem::current_path(), 0u, dir_idx);
		if (node_clicked != -1) {
			selection_mask = (1 << node_clicked);
		}
		ImGui::PopStyleVar();
		ImGui::NextColumn();
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		unsigned int idx = 0u;
		for (std::map<std::filesystem::path, std::filesystem::path>::iterator iter = assets.begin(); iter != assets.end(); ++iter)
		{
			std::filesystem::path k = iter->first;
			std::filesystem::path p = iter->second;
			if (k.filename() == currentfolder.filename())
			{
				ImGui::TreeNodeEx((void*)(intptr_t)idx, node_flags, "%s",
					p.filename().string().c_str());
			}
		}

		static std::string currentfolder;
		static int selection_mask = (1 << 2);
		int node_clicked = -1;
		unsigned int idx = 0u;

		for (auto& asset : m_AssetManager.GetAssets())
		{
			ImGuiTreeNodeFlags node_flags =
				ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
				((selection_mask & (1 << idx)) ? ImGuiTreeNodeFlags_Selected : 0);
			if (ImGui::TreeNodeEx((void*)(intptr_t)idx, node_flags, "%s", asset->GetDirectory().c_str())) {
				if (ImGui::IsItemClicked())
				{
					node_clicked = idx;
					currentfolder = asset->GetDirectory();
				}
				ImGui::TreePop();
			}
			if (asset->GetDirectory() == currentfolder)
			{
				ImGui::NextColumn();
				ImGui::TreeNodeEx((void*)(intptr_t)idx, node_flags, "%s",
					asset->GetName());
				ImGui::NextColumn();
			}
		}

		if (node_clicked != -1) {
			selection_mask = (1 << node_clicked);
		}

		ImGui::End();
	*/
	}
}