#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Spindel/Renderer/Resources/Mesh.h"
#include "Spindel/Renderer/Material.h"

#include "ScriptableEntity.h"
#include "SceneCamera.h"

namespace Spindel {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 & translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct StaticMeshRendererComponent
	{
		StaticMeshRendererComponent() = default;
		StaticMeshRendererComponent(Ref<Mesh> mesh, Ref<Material> mat)
			: m_Mesh(mesh), m_Material(mat), temp_color(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)), temp_metallic(0), temp_roughness(0) {}

		void Draw(const glm::mat4& transform)
		{
			m_Mesh->Draw(m_Material, transform);
		}
		Ref<Mesh> m_Mesh;
		Ref<Material> m_Material;
		glm::vec4 temp_color;
		float temp_metallic;
		float temp_roughness;
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}