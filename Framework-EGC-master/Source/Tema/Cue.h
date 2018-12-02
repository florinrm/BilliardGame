#pragma once
#include "ObjectComponent.h"
#include <Core/Engine.h>
#include <include\glm.h>

class Cue {
public:
	glm::vec3 cuePosition, cueScale;
	Mesh* cueMesh;
	ObjectComponent component = ObjectComponent();
	Cue(glm::vec3 pos, glm::vec3 scale) {
		cuePosition = pos;
		cueScale = scale;
		component.setPosition(pos);
		component.setScale(scale);
		cueMesh = new Mesh("cue");
		cueMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	}
	~Cue() {

	}
};