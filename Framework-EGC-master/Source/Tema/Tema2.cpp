#include "Tema2.h"

#include <Core/Engine.h>
#include "Laboratoare/Laborator3/Transform2D.h"
#include "Laboratoare/Laborator3/Object2D.h"
#include <iostream>

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;

	window->CenterPointer();
	window->DisablePointer();

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(9.5, 3.6, whiteBallZ / 2 + 0.4), glm::vec3(0.2f, 0.f, 0.0f), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("oilTank");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Props", "oildrum.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("cue");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Props", "10522_Pool_Cue_v1_L3.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader *shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7, 0.6f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7, 0.6f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7, 0.6f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 2.3f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, -0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, -0.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 0.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 0.6f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 0.8f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 1.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 1.6f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 1.8f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 2.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 2.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, -0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, -0.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 0.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 0.6f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 0.8f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 1.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 1.6f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 1.8f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 2.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 2.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.5f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.7f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.9f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.1f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.3f, 1.3f, -0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.5f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.7f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.9f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.1f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.3f, 1.3f, 2.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.3f, 0.1f));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.4f, 1.2f, 2.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.4f, 1.2f, -0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.6f, 1.2f, -0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.6f, 1.2f, 2.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5f, 1.2f, -0.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5f, 1.2f, 2.4f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	if (!gameStarted) {
		firstPlayer = true;
		secondPlayer = false;
		whiteBallX = 6.5f;
		whiteBallZ = 1;
	}

	// white ball
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(whiteBallX, 1.3f, whiteBallZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(3, 3, 3));
	}

	// the rest of ballz (ayy ballz)

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 1.3f, whiteBallZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.37f, 1.3f, whiteBallZ - 0.075f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.37f, 1.3f, whiteBallZ + 0.075f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.24f, 1.3f, whiteBallZ - 0.15f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.24f, 1.3f, whiteBallZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.24f, 1.3f, whiteBallZ + 0.15f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.11f, 1.3f, whiteBallZ + 0.075f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.11f, 1.3f, whiteBallZ - 0.075f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.11f, 1.3f, whiteBallZ - 0.2275f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.11f, 1.3f, whiteBallZ + 0.2275f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.98f, 1.3f, whiteBallZ - 0.15f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.98f, 1.3f, whiteBallZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.98f, 1.3f, whiteBallZ + 0.15f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1.6f, 1.6f, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.98f, 1.3f, whiteBallZ - 0.30f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.98f, 1.3f, whiteBallZ + 0.30f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.6f, 1.3f, whiteBallZ));
		modelMatrix = glm::rotate(modelMatrix, 3 * glm::pi<float>() / 2, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 10) * 0.2f);
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}
}

void Tema2::FrameEnd()
{
	// do nothing
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint loc = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc, 1, glm::value_ptr(color));

	int location_model = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	int location_view = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location_projection = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrixSet = projectionMatrix;
	glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrixSet));


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_O)) {
			orthoLeft = -8.0f;
			orthoRight = 8.0f;
			orthoUp = 4.5f;
			orthoDown = -4.5;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
			isOrtho = true;
		}

		// increase height
		if (window->KeyHold(GLFW_KEY_UP) && isOrtho) {
			orthoUp += deltaTime;
			orthoDown -= deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// increase height
		if (window->KeyHold(GLFW_KEY_DOWN) && isOrtho) {
			orthoUp -= deltaTime;
			orthoDown += deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// increase length
		if (window->KeyHold(GLFW_KEY_RIGHT) && isOrtho) {
			orthoRight += deltaTime;
			orthoLeft -= deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// decrease length
		if (window->KeyHold(GLFW_KEY_LEFT) && isOrtho) {
			orthoRight -= deltaTime;
			orthoLeft += deltaTime;
			projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
		}

		// inversare FOV
		if (window->KeyHold(GLFW_KEY_K)) {
			projectionMatrix = glm::perspective(-90.f, -2.f, 2.f, -200.0f);
			isOrtho = false;
		}
		// FOV normal
		if (window->KeyHold(GLFW_KEY_P))
		{
			projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
			isOrtho = false;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		camera->RotateThirdPerson_OX(glm::radians(30.0f));
	}
	// add key press event
	if (key == GLFW_KEY_T) {
		renderCameraTarget = !renderCameraTarget;
	}

}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
		}
	}
	else {
		//cueMoveY += deltaY;
		//cueMoveZ += deltaX;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}


