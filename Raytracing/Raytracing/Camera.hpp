#pragma once
#include "Entity.hpp"
#include "Ray.hpp"

class Camera : public Entity
{
public:

	float focal;
	float aspectratio;

	Camera();
	Camera(float focal, float aspectratio);

	Ray getRay(float x, float y);

private:

};

