#pragma once
#include "Color.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#define M_PI 3.141592653589793
#define INFINITY 1e8

class Tracer
{
public:

	Tracer();

	void render(Scene scene);
	Color getImpactColor(Ray& ray, Object* obj, Point& impact, Scene& scene);
	Color trace(Ray ray, Scene scene, int depth);

private:

};



