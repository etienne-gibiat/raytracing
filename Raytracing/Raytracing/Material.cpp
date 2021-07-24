#include "Material.hpp"

Material::Material()
{
	this->ambiant = Color();
	this->diffuse = Color();
	this->specular = Color();
	this->shininess = 0.;
	this->reflection = 0.;
	this->transparency = 0.;

}

Material::Material(Color ambiant, Color diffuse, Color specular, float shininess, float reflection, float transparency)
{
	this->ambiant = ambiant;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflection = reflection;
	this->transparency = transparency;
}