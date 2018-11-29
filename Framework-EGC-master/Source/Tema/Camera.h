#pragma once

#include <include\glm.h>

class Camera {
private:
	glm::vec3 position, forward, up, right;
	float distance;
public:

	Camera();
	~Camera();

	glm::vec3 getPosition() {
		return position;
	}

	glm::vec3 getForward() {
		return forward;
	}

	glm::vec3 getUp() {
		return up;
	}

	glm::vec3 getRight() {
		return right;
	}
};