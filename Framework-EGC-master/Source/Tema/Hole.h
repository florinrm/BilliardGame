#pragma once
#include <include\glm.h>

class Hole {
public:
	glm::vec3 holePosition;
	float holeRadius;
	Hole(glm::vec3 position) {
		holePosition = position;
		holeRadius = 0.15f;
	}
	~Hole() {

	}
};