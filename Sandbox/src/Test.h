#pragma once
#include "Spindel.h"

#include "imgui/imgui.h"

class TestLayer : public Spindel::Layer
{
public:
	TestLayer();
	
	void OnUpdate() override;

	void OnRender() override;


	void OnImGuiRender() override;

	void OnEvent(Spindel::Event& event) override;


private:
	Spindel::PerspectiveFPSCameraController m_Camera;
	Spindel::Ref<Spindel::VertexArray> vao;
	Spindel::Ref<Spindel::VertexBuffer> vbo;
	Spindel::Ref<Spindel::IndexBuffer> ibo;
	Spindel::Ref<Spindel::Shader> shader;
	Spindel::Ref<Spindel::Texture2D> tex;

	glm::vec3 squarepos = glm::vec3(20, 0, 0);
	glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), squarepos);
	glm::mat4 pos2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));
};