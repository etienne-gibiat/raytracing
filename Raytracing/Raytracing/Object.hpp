#pragma once
#include "Ray.hpp"
#include "Material.hpp"
#include "Entity.hpp"

class Object : public Entity
{
public:

	Material material;
	cv::Mat Texture;
	Point position;
	Object();

	//Point getTextureCoordinates(const Point& p)const;
	Material getMaterial()const;
	virtual Point getTextureCoordinates(const Point& p) {
		return Point(0, 0, 0);

	}
	virtual Ray getNormal(const Point& p, const Point& o) {
		return Ray();
	}
	virtual bool intersect(const Ray& ray, Point& impact, float& t0, float& t1) {
		return false;
	}

private:

};

