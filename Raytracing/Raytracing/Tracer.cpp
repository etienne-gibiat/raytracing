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
    Bitmap bmp(width, height);
    Color pixelColor;
    /*Color* image = new Color[width * height], * pixel = image;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);*/
    // Trace rays
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            /*float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vector raydir(xx, yy, -1);
            raydir.normalized();
            *pixel = trace(Vector(), raydir, spheres, 0);*/

            Camera camera(30);
            Ray ray = camera.getRay(x, y);

            pixelColor = trace(ray, scene, 5);

            int r = int(std::min(powf(pixelColor[0], gamma) * 255.99f, 255.f));
            int g = int(std::min(powf(pixelColor[1], gamma) * 255.99f, 255.f));
            int b = int(std::min(powf(pixelColor[2], gamma) * 255.99f, 255.f));

            bmp.SetPixel(x, y, Bitmap::Pixel(r, g, b));

            //*pixel = trace(ray, scene, 5);
        }
    }
    bmp.WriteToDisk();
    // Save result to a PPM image (keep these flags if you compile under Windows)
    /*std::ofstream ofs("./raytracingx.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << (unsigned char)(std::min(float(1), image[i][0]) * 255) <<
            (unsigned char)(std::min(float(1), image[i][1]) * 255) <<
            (unsigned char)(std::min(float(1), image[i][2]) * 255);
    }
    ofs.close();
    delete[] image;*/

}

Color Tracer::getImpactColor(Ray& ray, Object* obj, Point& impact, Scene& scene) {

    Material m = obj->getMaterial(impact);
    Color amb = m.ambiant.mul(scene.getAmbiant());

    Color diff = Color();
    Color spec = Color();

    float angle, angle2;
    int nbLights = scene.nbLights();
    Ray normale = obj->getNormal(impact, ray.origin);

    for (int i = 0; i < nbLights; i++) {
        Ray l = scene.getLight(i).getRayToLight(impact);
        angle = (l.vector.dot(normale.vector) / (l.vector.norm() * normale.vector.norm()));//
        Vector v = l.vector - 2 * (l.vector.dot(normale.vector) * normale.vector);
        angle2 = (v.dot(ray.vector)) / (v.norm() * ray.vector.norm());
        if (angle > 0) {
            diff += m.diffuse.mul(scene.getLight(i).id) * angle;
        }
        if (angle2 > 0) {
            spec += m.specular.mul(scene.getLight(i).id) * pow(angle2, m.shininess);
        }
    }
    Color Phong = diff + amb + spec;
    return Phong;

}

Color Tracer::trace(Ray ray, Scene scene, int depth)
{
    float tnear = INFINITY;
    Point impact = Point();
    Object* object = scene.closer_intersected(ray, impact);
    
    Color res;
    if (!object)
        res = scene.getBackground();
    else
        res = getImpactColor(ray, object, impact, scene);

    return res;
}