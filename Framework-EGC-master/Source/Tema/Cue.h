#pragma once
#include "ObjectComponent.h"
#include <Core/Engine.h>
#include <include\glm.h>

class Cue {
public:
	glm::vec3 cuePosition;
	Mesh* cueMesh;
	ObjectComponent component = ObjectComponent();
	Cue(glm::vec3 pos) {
		cuePosition = pos;
		component.setPosition(pos);
		cueMesh = new Mesh("cue");
		cueMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	}
	~Cue() {

	}
};