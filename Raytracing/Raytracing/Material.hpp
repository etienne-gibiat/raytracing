#pragma once
#include "Color.hpp"

class Material
{
public:
	Color ambiant, diffuse, specular;
	float shininess;
	Material();
	Material(Color ambiant, Color diffuse, Color specular, float shininess);

private:

};


