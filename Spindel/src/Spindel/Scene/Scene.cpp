#include "sppch.h"
#include "Scene.h"

#include "Components.h"

#include "Entity.h"
#include "Spindel/Renderer/Renderer.h"

namespace Spindel
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(), this };
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateRuntime()
	{
		//Renderer::BeginScene(*mainCamera, cameraTransform);

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

			if (mesh.visible)
			{
				Renderer::DrawMesh(mesh.GetMesh(), transform.GetTransform());
			}
		}

		//Renderer::EndScene();
	}

	void Scene::OnUpdateEditor(EditorCamera& camera)
	{
		Renderer::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

			if (mesh.visible)
			{
				Renderer::DrawMesh(mesh.GetMesh(), transform.GetTransform());
			}
		}

		Renderer::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
	{

	}
}