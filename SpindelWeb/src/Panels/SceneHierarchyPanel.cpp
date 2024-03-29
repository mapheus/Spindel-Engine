#include "SceneHierarchyPanel.h"

#include "Spindel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>

#include "Spindel/Scene/Components.h"
#include "Spindel/Renderer/MeshManager.h"
#include "Spindel/Assets/Asset.h"
#include <cstring>
#include <filesystem>
#include <vector>

namespace Spindel
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
		m_SelectionContext = {};
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.1f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.2f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.1f, 0.8f, 1.0f });
		if (ImGui::Button("+", buttonSize))
			m_Context->CreateEntity("Empty Entity");
		ImGui::PopStyleColor(3);

		ImGui::Separator();


		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 20, 200 });
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});
		ImGui::PopStyleVar();

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}

		ImGui::End();


		ImGui::Begin("Content Browser");
		DrawContentBrowser();

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawContentBrowser()
	{
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
		}*/
		
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
		
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{

		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}

	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar(
			);
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 2.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		ImGui::Text("Name: ");
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
			{
				DrawVec3Control("Translation", component.Translation);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale, 1.0f);
			});

		ImGui::Separator();

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Mesh"))
			{
				if (!m_SelectionContext.HasComponent<MeshComponent>())
					m_SelectionContext.AddComponent<MeshComponent>();
				else
					SP_CORE_WARN("This entity already has the Mesh Component!");
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		DrawComponent<MeshComponent>("Mesh", entity, [](auto& component)
			{
				ImGui::Checkbox("Visible", &component.visible);
				
				{
					std::vector<Ref<Model>> m = MeshManager::GetAllModels();
						
					std::vector<std::string> names;
					for (auto& a : m)
					{
						names.push_back(a->GetName());
					}
					ImGui::Text("Mesh: ");
					ImGui::ListBox("", &component.index, vector_getter, static_cast<void*>(&names), names.size());
					if (m.size() > 0 && component.index < m.size() && component.prev_index != component.index)
					{
						component.model = m[component.index];
						component.prev_index = component.index;
					}
				}
			});
	}
}