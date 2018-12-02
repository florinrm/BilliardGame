#pragma once
#include <include\glm.h>
#include <include\gl.h>
#include <math.h>

#define _USE_MATH_DEFINES

class ObjectComponent {
private:
	glm::vec3 scale, position, alt_rotation;
	glm::mat4 rotation;
public:
	ObjectComponent();
	~ObjectComponent();

	glm::mat4 getRotation() {
		return rotation;
	}
	glm::vec3 getScale() {
		return scale;
	}
	glm::vec3 getPosition() {
		return position;
	}
	glm::vec3 getAltRotation() {
		return alt_rotation;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	void setAltRotation(glm::vec3 rotation) {
		this->alt_rotation = rotation;
	}

	void setRotation(glm::mat4 rotation) {
		this->rotation = rotation;
	}

	void setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	void lookAt(glm::vec3 target);

	glm::mat4 getModelMatrix();

	void target();

};