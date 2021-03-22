#pragma once

#include "Spindel/Core/Core.h"
#include "Spindel/Scene/Scene.h"
#include "Spindel/Scene/Entity.h"


#include "Spindel/Assets/AssetManager.h"

namespace Spindel
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawContentBrowser();
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

		AssetManager m_AssetManager;
	};
}