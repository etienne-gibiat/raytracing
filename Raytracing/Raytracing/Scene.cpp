#include "Scene.hpp"
#include <math.h> 

Scene::Scene()
{
	background = Color(0, 0, 0);
	ambiant = Color(1, 1, 1);
	image = cv::imread("2K_ice-fire-ac.jpg");
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

Color Scene::getBackGroundImage(int x, int y)
{

	cv::Vec3b tmp = image.at<cv::Vec3b>(y % image.rows, x % image.cols);
	float max = 255;
	float r = tmp[2] / max;
	float g = tmp[1] / max;
	float b = tmp[0] / max;
	Color c(r, g, b);

	return c;
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
	float t0 = INFINITY, t1 = INFINITY, t = INFINITY;
	float d;
	Point p;


	

	for (int i = 0; i < objects.size(); i++) {

		if (objects[i]->intersect(ray, impact, t0, t1)) {

			d = sqrt(pow((impact[0] - ray.origin[0]), 2) + pow((impact[1]) - ray.origin[1], 2) + pow((impact[2] - ray.origin[2]), 2));

			if (t > d)
			{
				obj = objects[i];
				p[0] = impact[0];
				p[1] = impact[1];
				p[2] = impact[2];
				t = d;
			}

			//if (t0 < 0) t0 = t1;
			//if (t0 < tnear) {
			//tnear = t0;
			//Vector phit = ray.origin + ray.vector * tnear;
			//impact[0] = phit[0];
			//impact[1] = phit[1];
			//impact[2] = phit[2];
			//obj = objects[i];

			//}

		//}
		}
		
	}
	
	impact = p;
	return obj;
}
