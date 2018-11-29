#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>
#include "Laboratoare/Laborator5/LabCamera.h"
#include <vector>
#include <utility>

using namespace std;

class Tema2 : public SimpleScene {
public:
	Tema2();
	~Tema2();

	bool isOrtho = false;
	float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;

	void Init() override;

private:
	enum gameState{GAME_NOT_STARTED, GAME_CUE_SHOT};

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color);

	float whiteBallX = 6.5f;
	float whiteBallZ = 1.0f;
	float cueMoveY = 0;
	float cueMoveZ = 0;
	bool gameStarted = false;
	bool firstPlayer = true; // red
	bool secondPlayer = false; // yellow
	
	vector<glm::vec3> holesPositions;

protected:
	Laborator::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
};