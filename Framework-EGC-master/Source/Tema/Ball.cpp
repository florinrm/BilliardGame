#include "Ball.h"

Ball::Ball(glm::vec3 color, glm::vec3 position) {
	ballColor = color;
	ballPosition = position;
	ballComponents.setPosition(position);
}

Ball::~Ball() {

}