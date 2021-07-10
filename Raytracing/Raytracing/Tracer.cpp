#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "Tracer.hpp"
#include "Color.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Tracer.hpp"
#include "Camera.hpp"
#include "Bitmap.hpp"


Tracer::Tracer()
{
}

void Tracer::render(Scene scene) {

    const float gamma = 1.f / 2.2f;

    unsigned width = 640, height = 480;
    //Bitmap bmp(width, height);
    Color pixelColor;
    Color* image = new Color[width * height], * pixel = image;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);
    // Trace rays
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x, ++pixel) {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            /*Vector raydir(xx, yy, -1);
            raydir.normalized();
            *pixel = trace(Vector(), raydir, spheres, 0);*/
            Ray ray(0, 0, 0, xx, yy, -1);
            Camera camera(90);
            //Ray ray = camera.getRay(x, y);
            ray.normalized();
            *pixel = trace(ray, scene, 5);


            //*pixel = trace(ray, scene, 5);
        }
    }
    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./rendu.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << (unsigned char)(std::min(float(1), image[i][0]) * 255) <<
            (unsigned char)(std::min(float(1), image[i][1]) * 255) <<
            (unsigned char)(std::min(float(1), image[i][2]) * 255);
    }
    ofs.close();
    delete[] image;

}

Color Tracer::getImpactColor(Ray& ray, Object* obj, Point& impact, Scene& scene) {

   /* Material m = obj->getMaterial(impact);
    Color amb = m.ambiant.mul(scene.getAmbiant());

    Color diff = Color();
    Color spec = Color();

    float angle, angle2;
    int nbLights = scene.nbLights();
    Ray normale = obj->getNormal(impact, ray.origin);

    for (int i = 0; i < nbLights; i++) {
        Ray l = scene.getLight(i).getRayToLight(impact);
        angle = (l.vector.dot(normale.vector) / (l.vector.norm() * normale.vector.norm()));
        Vector v = l.vector - 2 * (l.vector.dot(normale.vector) * normale.vector);
        angle2 = (v.dot(ray.vector)) / (v.norm() * ray.vector.norm());
        if (angle > 0) {
            diff += m.diffuse.mul(scene.getLight(i).id) * angle;
        }
        if (angle2 > 0) {
            spec += m.specular.mul(scene.getLight(i).is) * pow(angle2, m.shininess);
        }
    }
    Color Phong = diff + amb + spec;
    return Phong;*/
    Material mat = obj->getMaterial(impact);
    Color Ka = mat.ambiant;
    Color Kd = mat.diffuse;
    Color Ks = mat.specular;
    Color Ia = scene.getAmbiant();
    //Ray normal = obj->getNormal(impact, ray.origin);
    Point tmp = impact - obj->position;// normal at the intersection point
    Ray normal(0,0,0, tmp[0],tmp[1],tmp[2]);
    normal.normalized();
    Color c = Ka.mul(scene.getAmbiant());
    for (int l = 0; l < scene.nbLights(); l++) {
        Light light = scene.getLight(l);
        Vector lv = light.getRayToLight(impact).vector;
        float alpha = lv.dot(normal.vector);
        if (alpha > 0)
            c += (light.id).mul(Kd) * alpha;

        Vector rm = (2 * lv.dot(normal.vector) * normal.vector) - lv;

        float beta = -rm.dot(ray.vector);
        if (beta > 0)
            c += (light.is).mul(Ks) * pow(beta, mat.shininess);
    }

    return c;

}

Color Tracer::trace(Ray ray, Scene scene, int depth)
{
    
    Point impact = Point();
    Object* object = scene.closer_intersected(ray, impact);
    
    Color res;
    if (!object)
        res = scene.getBackground();
    else
        res = getImpactColor(ray, object, impact, scene);

    return res;
}