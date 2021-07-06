#pragma once
#include "Entity.hpp"
#include "Ray.hpp"

class Camera : public Entity
{
public:

	float focal;

	Camera();
	Camera(float focal);

	Ray getRay(float x, float y);

private:

};

