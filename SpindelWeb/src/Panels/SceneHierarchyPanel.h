#pragma once

#include "Spindel/Core/Core.h"
#include "Spindel/Scene/Scene.h"
#include "Spindel/Scene/Entity.h"

#include "Spindel/Assets/Cache.h"

namespace Spindel
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene, Ref<Cache> cache);

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
		Ref<Cache> m_Cache;
	};
}