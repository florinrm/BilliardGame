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
	camera->Set(glm::vec3(9.5, 3.6, whiteBallZ / 2 + 0.4), glm::vec3(0.2f, 0.f, 0.0f), glm::vec3(0, 1, 0), distanceToTarget);

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

	{
		Shader *shader2 = new Shader("ShaderLab9");
		shader2->AddShader("Source/Tema/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader2->AddShader("Source/Tema/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader2->CreateAndLink();
		shaders[shader2->GetName()] = shader2;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// holes
	holesPositions.push_back(glm::vec3(7.4f, 1.2f, 2.4f));
	holesPositions.push_back(glm::vec3(7.4f, 1.2f, -0.4f));
	holesPositions.push_back(glm::vec3(1.6f, 1.2f, -0.4f));
	holesPositions.push_back(glm::vec3(1.6f, 1.2f, 2.4f));
	holesPositions.push_back(glm::vec3(4.5f, 1.2f, -0.4f));
	holesPositions.push_back(glm::vec3(4.5f, 1.2f, 2.4f));

	for (int i = 0; i < holesPositions.size(); ++i) {
		tableHoles.push_back(new Hole(holesPositions[i]));
	}

	// game ballz
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(2.5f, 1.3f, whiteBallZ)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(2.37f, 1.3f, whiteBallZ - 0.075f)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(2.37f, 1.3f, whiteBallZ + 0.075f)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(2.24f, 1.3f, whiteBallZ - 0.15f)));
	gameBalls.push_back(new Ball(glm::vec3(0, 0, 0), glm::vec3(2.24f, 1.3f, whiteBallZ)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(2.24f, 1.3f, whiteBallZ + 0.15f)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(2.11f, 1.3f, whiteBallZ + 0.075f)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(2.11f, 1.3f, whiteBallZ - 0.075f)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(2.11f, 1.3f, whiteBallZ - 0.2275f)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(2.11f, 1.3f, whiteBallZ + 0.2275f)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(1.98f, 1.3f, whiteBallZ - 0.15f)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(1.98f, 1.3f, whiteBallZ)));
	gameBalls.push_back(new Ball(glm::vec3(1.6f, 1.6f, 0), glm::vec3(1.98f, 1.3f, whiteBallZ + 0.15f)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(1.98f, 1.3f, whiteBallZ - 0.30f)));
	gameBalls.push_back(new Ball(glm::vec3(1, 0, 0), glm::vec3(1.98f, 1.3f, whiteBallZ + 0.30f)));
	gameBalls.push_back(whiteBall);
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
	// game table
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

	// holes

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

	for (int i = 0; i < gameBalls.size(); ++i) {
		if (!gameBalls[i]->hasBallEntered()) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, gameBalls[i]->getBallPosition());
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, gameBalls[i]->getBallColor());
		}
	}
	/*
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(7.6f, 1.3f, whiteBallZ));
		modelMatrix = glm::rotate(modelMatrix, glm::pi<float>() / 2, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 10) * 0.2f);
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	} */

	bool check = all_of(gameBalls.begin(), gameBalls.end(), [](Ball* ball) {return ball->hasBallEntered() ? true : glm::distance(ball->ballSpeed, glm::vec2(0, 0)) < 0.01; });

	for (int i = 0; i < gameBalls.size(); ++i) {
		gameBalls[i]->modifySpeed(-0.4f * gameBalls[i]->getBallSpeed() * deltaTimeSeconds);
		gameBalls[i]->setPosition(gameBalls[i]->getPosition() + glm::vec3(gameBalls[i]->getBallSpeed().x, 0, 
									gameBalls[i]->getBallSpeed().y) * deltaTimeSeconds);
	}

	if (currentGameState == gameState::GAME_WAIT_FOR_BALLS_TO_STOP && check) {

		if (collisionColor != playersColors[player] && !allOfBalls) {
			faulted_player = true;
			++playersFaults[player];
		}

		currentGameState = gameState::GAME_CAMERA_SWITCH;
		hasBallHitHole = false;
	}

	// collisions between wall and game balls
	for (int i = 0; i < gameBalls.size(); ++i) {
		if ((gameBalls[i]->getBallY() - gameBalls[i]->getBallRadius() <= -0.4f) ||
			(gameBalls[i]->getBallY() + gameBalls[i]->getBallRadius() >= 2.4f)) {
			gameBalls[i]->ballPosition.z += gameBalls[i]->ballSpeed.y * deltaTimeSeconds;
			gameBalls[i]->ballSpeed.y *= -1;
		}

		if ((gameBalls[i]->getBallX() - gameBalls[i]->getBallRadius() <= 1.6f) ||
			(gameBalls[i]->getBallX() + gameBalls[i]->getBallRadius() >= 7.4f)) {
			gameBalls[i]->ballPosition.x += gameBalls[i]->ballSpeed.x * deltaTimeSeconds;
			gameBalls[i]->ballSpeed.x *= -1;
		}
	}

	// "collision" between dem ballz and these holes (ballz in holez, get it?)
	for (int i = 0; i < holesPositions.size(); ++i) {
		for (int j = 0; j < gameBalls.size(); ++j) {
			float distanceToHole = glm::distance(tableHoles[i]->holePosition, gameBalls[j]->getBallPosition());
			if (distanceToHole < tableHoles[i]->holeRadius + gameBalls[j]->ballRadius) {
				if (gameBalls[j] != whiteBall) {
					if (allOfBalls) {
						hasBallHitHole = true;
						allOfBalls = false;
						playersScores[player]++;
						playersColors[player] = gameBalls[j]->getBallColor();
						if (gameBalls[j]->getBallColor() == glm::vec3(1, 0, 0)) {
							playersColors[1 - player] = glm::vec3(1, 1, 0);
						}
						else {
							playersColors[1 - player] = glm::vec3(1, 0, 0);
						}	
					} else if (playersColors[player] == gameBalls[j]->getBallColor()) {
						hasBallHitHole = true;
						playersScores[player]++;
					}

					gameBalls[j]->setPosition(glm::vec3(999, -999, 999));
					gameBalls[j]->enterBall();
				}
				else { 
					// for white ball
					gameBalls[j]->ballPosition = glm::vec3(6.5f, 1.3f, 1.f);
					gameBalls[j]->ballSpeed = glm::vec2(0, 0);
					++playersFaults[player];
					player = 1 - player;
					currentGameState = gameState::GAME_DEFAULT;
				}
			}
		}
	}

	for (int i = 0; i < gameBalls.size(); ++i) {
		for (int j = 0; j < gameBalls.size(); ++j) {
			if (i == j)
				continue;
			else {
				glm::vec2 dist = getClosestPointOnLine(gameBalls[i]->getBallX(), gameBalls[i]->getBallY(),
					gameBalls[i]->getBallX() + gameBalls[i]->ballSpeed.x, gameBalls[j]->getBallY() + gameBalls[i]->ballSpeed.y,
					gameBalls[i]->getBallX(), gameBalls[j]->getBallY());

				double closestDistance = pow(gameBalls[j]->getBallX() - dist.x, 2)
						+ pow(gameBalls[j]->getBallY() - dist.y, 2);

				if (closestDistance <= pow(gameBalls[i]->ballRadius + gameBalls[j]->ballRadius, 2)) {
					// a collision has occurred
					float distance = glm::distance(gameBalls[i]->ballPosition, gameBalls[j]->ballPosition);
					if (distance < gameBalls[i]->ballRadius + gameBalls[j]->ballRadius) {
						if (gameBalls[i] == whiteBall) {
							if (!first_collision) {
								first_collision = true;
								collisionColor = gameBalls[j]->getBallColor();
							}
						} else if (gameBalls[j] == whiteBall) {
							if (!first_collision) {
								first_collision = true;
								collisionColor = gameBalls[i]->getBallColor();
							}
						}

						double x = (gameBalls[j]->getBallX() - gameBalls[i]->getBallX()) / distance;
						double y = (gameBalls[j]->getBallY() - gameBalls[i]->getBallY()) / distance;

						double someDistance = 2 * (gameBalls[i]->ballSpeed.x * x + gameBalls[i]->ballSpeed.y * y -
							gameBalls[j]->ballSpeed.x * x - gameBalls[j]->ballSpeed.y * y) /
							(gameBalls[i]->ballMass + gameBalls[j]->ballMass);

						float acc = 1.3f;

						gameBalls[i]->ballSpeed.x = gameBalls[i]->ballSpeed.x - someDistance * gameBalls[i]->ballMass * x;
						gameBalls[i]->ballSpeed.y = gameBalls[i]->ballSpeed.y - someDistance * gameBalls[i]->ballMass * y;
						gameBalls[j]->ballSpeed.x = gameBalls[j]->ballSpeed.x + someDistance * gameBalls[j]->ballMass * x;
						gameBalls[j]->ballSpeed.y = gameBalls[j]->ballSpeed.y + someDistance * gameBalls[j]->ballMass * y;

						gameBalls[i]->ballPosition.x = gameBalls[i]->getBallX() + acc * gameBalls[i]->ballSpeed.x  * deltaTimeSeconds;
						gameBalls[i]->ballPosition.z = gameBalls[i]->getBallY() + acc * gameBalls[i]->ballSpeed.y * deltaTimeSeconds;
						gameBalls[j]->ballPosition.x = gameBalls[j]->getBallX() + acc * gameBalls[j]->ballSpeed.x * deltaTimeSeconds;
						gameBalls[j]->ballPosition.z = gameBalls[j]->getBallY() + acc * gameBalls[j]->ballSpeed.y * deltaTimeSeconds;

					}
				}
			}
		}
	}

	switch (currentGameState) {
		case gameState::GAME_CAMERA_SWITCH:
			camera->Set(glm::vec3(9.5, 3.6, whiteBallZ / 2 + 0.4), glm::vec3(0.2f, 0.f, 0.0f), glm::vec3(0, 1, 0), distanceToTarget);
			first_collision = false;
			if (faulted_player)
				currentGameState = GAME_DEFAULT;
			else
				currentGameState = GAME_CUE_SHOT;
			faulted_player = false;
			break;
		case gameState::GAME_CUE_SHOT:
			distanceToTarget = 0.4;
			camera->setCameraDistanceToTarget(distanceToTarget);
			camera->setPosition(whiteBall->ballPosition - glm::normalize(camera->getForward()) * distanceToTarget);
			break;
		case gameState::GAME_DEFAULT:
		case gameState::GAME_WAIT_FOR_BALLS_TO_STOP:
			camera->Set(glm::vec3(9.0f, 6.5, 1.f), glm::vec3(0.9f, 0.4f, 0.9f), glm::vec3(1, 1, 1), distanceToTarget);
			break;
		default:
			break;
	}
	
	std::cout << "Score" << std::endl;
	std::cout << "YELLOW" << std::endl;
	std::cout << "BALLS: " << " " << playersScores[players::YELLOW] << std::endl;
	std::cout << "FAULTS: " << " " << playersFaults[players::YELLOW] << std::endl;
	std::cout << "RED" << std::endl;
	std::cout << "BALLS: " << " " << playersScores[players::RED] << std::endl;
	std::cout << "FAULTS: " << " " << playersFaults[players::RED] << "\n\n\n";

	if (currentGameState == gameState::GAME_CUE_SHOT) {
		glm::vec3 cuePosition = camera->getPosition();
		cuePosition.y = 1.3f;
		cue->cuePosition = cuePosition;
		cue->component.setPosition(cuePosition);
		cue->component.lookAt(whiteBall->ballPosition);
		cue_direction = glm::normalize(cue->cuePosition - whiteBall->ballPosition);
		cue->cuePosition = whiteBall->getBallPosition() + cue_direction * 0.2f;

		shaders["ShaderLab9"]->Use();

		GLuint animate_direction = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "animate_direction");
		GLuint cue_shader = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "cue_shader");
		GLuint colorLoc = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "color");
		GLuint conditionLoc = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "cue_cond");

		glUniform3fv(animate_direction, 1, glm::value_ptr(cue_direction));
		glUniform1i(cue_shader, 1);
		glUniform1i(conditionLoc, 1);
		glUniform3fv(colorLoc, 1, glm::value_ptr(playersColors[player]));
		RenderMesh(cue->cueMesh, shaders["ShaderLab9"], cue->component.getModelMatrix());
		glUniform1i(cue_shader, 0);
		glUniform1i(conditionLoc, 0);
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
	float speed = 4.0f, positionSpeed = 0.8f;

	float cameraSpeed = 0.1f;
	switch (currentGameState) {
		case gameState::GAME_DEFAULT:
		{
			if (window->KeyHold(GLFW_KEY_D)) {
				whiteBall->ballPosition.z += positionSpeed * deltaTime;
			}
			if (window->KeyHold(GLFW_KEY_W)) {
				whiteBall->ballPosition.x += positionSpeed * deltaTime;
			}

			if (window->KeyHold(GLFW_KEY_A)) {
				whiteBall->ballPosition.z -= positionSpeed * deltaTime;
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				whiteBall->ballPosition.x -= positionSpeed * deltaTime;
			}

			// Constrain whit ball position to the table 
			whiteBall->ballPosition.z = limit(whiteBall->ballPosition.z, -0.3f, 2.3f);
			whiteBall->ballPosition.x = limit(whiteBall->ballPosition.x, 1.5f, 7.2f);
		}
		break;
		case gameState::GAME_STARTING:
		{
			if (window->KeyHold(GLFW_KEY_A)) {
				whiteBall->ballPosition.z += positionSpeed * deltaTime;
			}
			if (window->KeyHold(GLFW_KEY_W)) {
				whiteBall->ballPosition.x -= positionSpeed * deltaTime;
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				whiteBall->ballPosition.z -= positionSpeed * deltaTime;
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				whiteBall->ballPosition.x += positionSpeed * deltaTime;
			}

			// Constrain white ball position to first third of the table
			whiteBall->ballPosition.z = limit(whiteBall->ballPosition.z, -0.3f, 2.3f);
			whiteBall->ballPosition.x = limit(whiteBall->ballPosition.x, 5.6f, 7.2f);
		}
		break;

		case gameState::GAME_CUE_SHOT:
		{
			if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
				shaders["ShaderLab9"]->Use();

				// Notify vertex shade that we are drawing the rod
				GLuint en_animation = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "en_animation");
				GLuint time = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "time");
				
				animation += deltaTime;
				moving = fabs(0.15f * sin(2 * animation));
				glUniform1i(en_animation, 1);
				glUniform1f(time, animation);
			}
			else {
				shaders["ShaderLab9"]->Use();
				GLuint en_animation = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "en_animation");
				GLuint time = glGetUniformLocation(shaders["ShaderLab9"]->GetProgramID(), "time");
				glUniform1i(en_animation, 0);
				animation = 0;
				glUniform1f(time, animation);

			}
		}
			break;
	}

}

void Tema2::OnKeyPress(int key, int mods)
{
	if ((currentGameState == gameState::GAME_STARTING || currentGameState == gameState::GAME_DEFAULT)
				&& key == GLFW_KEY_SPACE) {
		camera->RotateThirdPerson_OX(glm::radians(10.0f));
		currentGameState = gameState::GAME_CUE_SHOT;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	// add mouse move event
	float sensivityOX = 0.001f, sensivityOY = 0.001f;

	switch (currentGameState) {
		case gameState::GAME_CUE_SHOT:
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
			break;
		case gameState::GAME_STARTING:
		case gameState::GAME_WAIT_FOR_BALLS_TO_STOP:
			camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
			break;
		default:
			break;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

float scaleObject(float inValue, float minInRange, float maxInRange, float minOutRange, float maxOutRange) {
	return minOutRange + (maxOutRange - minOutRange) * (inValue / (maxInRange - minInRange));
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == GLFW_MOUSE_BUTTON_2 && currentGameState == gameState::GAME_CUE_SHOT) {
		currentGameState = gameState::GAME_WAIT_FOR_BALLS_TO_STOP;
		whiteBall->ballSpeed = (-1) * scaleObject(moving, 0, 0.15, 0.1, 2)  * glm::vec2(cue_direction.x, cue_direction.z);
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}


