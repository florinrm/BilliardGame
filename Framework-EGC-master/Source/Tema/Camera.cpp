#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0, 2, 5);
	forward = glm::vec3(0, 0, 1);
	distance = 0.5f;
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);
}

Camera::~Camera() {

}