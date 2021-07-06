#pragma once
#include "Ray.hpp"
#include "Entity.hpp"
#include "Color.hpp"

class Light : public Entity
{
public:
	Light();
		
	Color id, is;

	Ray getRayToLight(Point& p);
	Ray getRayFromLight(Point& p);
	Vector getVectorToLight(Point& p);
	Vector getVectorFromLight(Point& p);

private:

};


