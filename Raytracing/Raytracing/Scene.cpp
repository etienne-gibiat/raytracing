#include "Scene.hpp"

Scene::Scene()
{
	background = Color(0, 0, 0);
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
std::vector<Object*> Scene::getObjects() {
	return objects;
}

Object* Scene::closer_intersected(Ray& ray, Point& impact) {
	float tnear = INFINITY;
	Object* obj = NULL;
	for (int i = 0; i < objects.size(); i ++) {
		float t0 = INFINITY, t1 = INFINITY;
		if (objects[i]->intersect(ray, impact, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				//Vector phit = ray.origin + ray.vector * tnear;
				//impact[0] = phit[0];
				//impact[1] = phit[1];
				//impact[2] = phit[2];
				obj = objects[i];
				return obj;
			}
			
		}
	}
	return obj;
}
