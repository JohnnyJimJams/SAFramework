#include "Entity.h"
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <string>

Entity::Entity()
{
	Position = glm::vec3();
	Rotation = glm::quat();
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	static int entityID = 1;
	Name = "Entity" + std::to_string(entityID++);
	Active = true;
	ScreenSpace = false;
	parent = nullptr;
}

Entity::~Entity()
{
}

glm::mat4 Entity::GetModelMatrix()
{
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::scale(ModelMatrix, Scale);
	ModelMatrix *= toMat4(Rotation);

	return ModelMatrix;
}

glm::vec3 Entity::GetEulerAngles()
{
	return glm::eulerAngles(Rotation);
}

void Entity::SetEulerAngles(glm::vec3 euler)
{
	Rotation = glm::quat(euler);
}

std::vector<Entity *> *Entity::GetChildren()
{
	return &children;
}

Entity* Entity::GetParent()
{
	return this->GetParent();
}

void Entity::SetParent(Entity* newParent)
{
	if (this->GetParent() != nullptr)
	{
		// cleanup previous parent/children
		std::vector<Entity *> *kids = &(parent->children);
		auto thisChild = std::find(kids->begin(), kids->end(), this);
		kids->erase(thisChild);
	}

	parent = newParent;

	if (newParent != nullptr)
	{
		newParent->GetChildren()->push_back(this);
		//parent->children.push_back(*this);
	}

}

bool Entity::operator==(Entity const& b)
{
	return this == &b;
}
