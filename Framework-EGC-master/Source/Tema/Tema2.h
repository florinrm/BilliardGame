#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>
#include "Laboratoare/Laborator5/LabCamera.h"
#include <vector>
#include <utility>
#include "Ball.h"
#include "Hole.h"
#include "Cue.h"

using namespace std;

class Tema2 : public SimpleScene {
public:
	Tema2();
	~Tema2();

	bool isOrtho = false;
	float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;

	void Init() override;

private:
	enum gameState {GAME_STARTING, GAME_CUE_SHOT, GAME_CAMERA_SWITCH, GAME_WAIT_FOR_BALLS_TO_STOP, GAME_DEFAULT};
	enum players {YELLOW, RED, NO_PLAYER};

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

	glm::vec2 getClosestPointOnLine (double x1, double y1, double x2, double y2, double x0, double y0) {
		double a = (y2 - y1), b = (x1 - x2);
		double c = (y2 - y1) * x1 + (x1 - x2) * y1, d = -b * x0 + a * y0;
		double point = (a * a + b * b), x = 0, y = 0;
		if (point != 0) {
			x = (double)(a * c - b * d) / (double) point;
			y = (double)(a * d + b * c) / (double) point;
		}
		else {
			x = x0, y = y0;
		}
		return  glm::vec2(x, y);
	}

	template <typename T>
	T clip(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	float whiteBallX = 6.5f;
	float whiteBallZ = 1.0f;
	float cueMoveY = 0;
	float cueMoveZ = 0;
	bool gameStarted = false;
	bool firstPlayer = true; // red
	bool secondPlayer = false; // yellow
	
	vector<glm::vec3> holesPositions; // holes from table
	vector<Ball*> gameBalls; // all balls from game
	vector<Hole*> tableHoles; // holes from game table
	Ball* whiteBall = new Ball(glm::vec3(3, 3, 3), glm::vec3(whiteBallX, 1.3f, whiteBallZ));
	glm::vec3 collisionColor;
	Cue* cue = new Cue(glm::vec3(7.6f, 1.3f, whiteBallZ));
	glm::vec3 cue_direction;

	int currentGameState = gameState::GAME_STARTING; // default state
	bool hasBallHitHole = false;
	bool allOfBalls = true;
	bool first_collision = false, faulted_player = false;
	int player = players::NO_PLAYER;
	int playersScores[2], playersFaults[2];
	glm::vec3 playersColors[2];
	float moving = 0, animation = 0;
	float distanceToTarget = 1.7f;

protected:
	Laborator::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
};