#include "ObjectComponent.h"
#include <math.h>

ObjectComponent::ObjectComponent() {
	scale = glm::vec3(1.f), position = glm::vec3(1.f);
	alt_rotation = glm::vec3(0.f);
	rotation = glm::mat4(1.f);
}

glm::mat4 ObjectComponent::getModelMatrix() {
	glm::mat4 m = glm::mat4(1);
	m = glm::translate(m, position);
	m = glm::scale(m * rotation, scale);
	return m;
}

void ObjectComponent::lookAt(glm::vec3 target) {
	if (target - position != glm::vec3(0)) {
		alt_rotation.x = 0;
		alt_rotation.z = 0;
		glm::vec3 direction = glm::normalize(target - position);

		rotation = glm::rotate(glm::mat4(1.f), alt_rotation.x, glm::vec3(1, 0, 0));

		alt_rotation.y = M_PI / 2 - atan2f(direction.z, direction.x);
		rotation *= glm::rotate(glm::mat4(1.f), alt_rotation.y, glm::vec3(0, 1, 0));
	}
}

void ObjectComponent::target() {

}

ObjectComponent::~ObjectComponent() {

}