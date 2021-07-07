#pragma once
#include "Ray.hpp"
#include "Material.hpp"
#include "Entity.hpp"

class Object : public Entity
{
public:

	Material material;

	Object();

	//Point getTextureCoordinates(const Point& p)const;
	Material getMaterial(const Point& p)const;
	virtual Ray getNormal(const Point& p, const Point& o) {
		return Ray();
	}
	virtual bool intersect(const Ray& ray, Point& impact) {
		return false;
	}

private:

};

