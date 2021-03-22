#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Spindel/Renderer/Mesh.h"
#include "Spindel/Renderer/MeshManager.h"

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

	struct MeshComponent
	{
		Ref<Model> model;
		bool visible = true;
		bool isModel = false;

		int index = 0;
		int prev_index = 0;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent()
		{
			Ref<Model> m = MeshManager::GetModel("box.fbx");
			if (m == nullptr)
				model = MeshManager::CreateModel("assets/models/box/box.fbx");
			else
				model = m;
				
		}
	};
}