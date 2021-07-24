#include "Object.hpp"



Object::Object() : Entity::Entity()
{
	this->material = Material();
}

//Point getTextureCoordinates(const Point& p)const {

//}

Material Object::getMaterial()const {
	return this->material;
}

