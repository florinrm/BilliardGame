#pragma once

#pragma once
#include "ObjectComponent.h"

class Ball {
private:
	glm::vec3 ballColor;
	glm::vec3 ballPosition;
	bool hasEntered = false;
	float ballRadius = 0.15f / 2;
	float ballMass = 5;
	ObjectComponent ballComponents;
	glm::vec2 ballSpeed;
	glm::vec2 ballAcceleration;

public:
	Ball(glm::vec3 color, glm::vec3 position);
	~Ball();

	glm::vec3 getBallColor() {
		return ballColor;
	}

	void enterBall() {
		hasEntered = true;
	}

	void initEnter() {
		hasEntered = false;
	}

	float getBallRadius() {
		return ballRadius;
	}

	float getBallMass() {
		return ballMass;
	}

	glm::vec2 getBallSpeed() {
		return ballSpeed;
	}

	glm::vec2 getBallAcceleration() {
		return ballAcceleration;
	}

	void setBallSpeed(glm::vec2 speed) {
		ballSpeed = speed;
	}

	void setBallAcceleration(glm::vec2 acceleration) {
		ballAcceleration = acceleration;
	}

};
