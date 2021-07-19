#pragma once
#include "Light.hpp"
#include "Object.hpp"
#include <vector>

class Scene
{
public:
    cv::Mat image;

    Scene();
    void addObject(Object* object);
    void addLight(Light light);
    void setAmbiant(const Color& c);
    Color getBackground();
    Color getBackGroundImage(int,int);
    Color getAmbiant();
    int nbLights();
    Light getLight(int index);
    std::vector<Object*> getObjects();
    Object* closer_intersected(Ray& ray, Point& impact);
protected:
    Color background;
    Color ambiant;
    std::vector<Object*> objects;
    std::vector<Light> lights;

};

