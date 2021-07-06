#include "Material.hpp"

Material::Material()
{
	this->ambiant = Color();
	this->diffuse = Color();
	this->specular = Color();
	this->shininess = 0.;

}

Material::Material(Color ambiant, Color diffuse, Color specular, float shininess)
{
	this->ambiant = ambiant;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}