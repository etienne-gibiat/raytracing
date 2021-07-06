#include "Scene.hpp"

Scene::Scene()
{
	background = Color(1, 0, 0);
	ambiant = Color(1, 1, 1);
}

void Scene::addObject(Object* object) {
	this->objects.push_back(object);
}

void Scene::addLight(Light light) {
	this->lights.push_back(light);
}

void Scene::setAmbiant(const Color& c) {
	this->ambiant = c;
}

Color Scene::getBackground() {
	return this->background;
}

Color Scene::getAmbiant() {
	return this->ambiant;
}

int Scene::nbLights() {
	return this->lights.size();
}

Light Scene::getLight(int index) {
	return this->lights[index];
}

Object* Scene::closer_intersected(Ray& ray, Point& impact) {
	for (int i = 0; i < objects.size(); i ++) {
		if (objects[i]->intersect(ray, impact)) {
			return objects[i];
		}
	}

	return NULL;
}