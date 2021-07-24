#pragma once
#include "Color.hpp"

class Material
{
public:
	Color ambiant, diffuse, specular;
	float shininess, transparency, reflection;

	Material();
	Material(Color ambiant, Color diffuse, Color specular, float shininess, float reflection, float transparency);

private:

};


