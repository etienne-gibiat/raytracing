#include "Object.hpp"



Object::Object() : Entity::Entity()
{
	this->material = Material();
}

//Point getTextureCoordinates(const Point& p)const {

//}

Material Object::getMaterial(const Point& p)const {
	return this->material;
}

