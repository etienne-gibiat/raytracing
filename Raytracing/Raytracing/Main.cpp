#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "opencv2/highgui/highgui.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "CylindreInfini.hpp"
#include "Triangle.hpp"
#include "Tracer.hpp"
#include "Plan.hpp"
#define M_PI 3.141592653589793
#define INFINITY 1e8

template<typename T>
class Vec3
{
public:
    T x, y, z;
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(T xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    Vec3& normalize()
    {
        T nor2 = length2();
        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }
    Vec3<T> operator * (const T& f) const { return Vec3<T>(x * f, y * f, z * f); }
    Vec3<T> operator * (const Vec3<T>& v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
    T dot(const Vec3<T>& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3<T> operator - (const Vec3<T>& v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T> operator + (const Vec3<T>& v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator += (const Vec3<T>& v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3<T>& operator *= (const Vec3<T>& v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }
    T length2() const { return x * x + y * y + z * z; }
    T length() const { return sqrt(length2()); }
    friend std::ostream& operator << (std::ostream& os, const Vec3<T>& v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec3<float> Vec3f;

class Spheres
{
public:
    Vec3f center;                           /// position of the sphere
    float radius, radius2;                  /// sphere radius and radius^2
    Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
    float transparency, reflection;         /// surface transparency and reflectivity
    Spheres(
        const Vec3f& c,
        const float& r,
        const Vec3f& sc,
        const float& refl = 0,
        const float& transp = 0,
        const Vec3f& ec = 0) :
        center(c), radius(r), radius2(r* r), surfaceColor(sc), emissionColor(ec),
        transparency(transp), reflection(refl)
    { /* empty */
    }
    //[comment]
    // Compute a ray-sphere intersection using the geometric solution
    //[/comment]
    bool intersect(const Vec3f& rayorig, const Vec3f& raydir, float& t0, float& t1) const
    {
        Vec3f l = center - rayorig;
        float tca = l.dot(raydir);
        if (tca < 0) return false;
        float d2 = l.dot(l) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;

        return true;
    }
};

//[comment]
// This variable controls the maximum recursion depth
//[/comment]
#define MAX_RAY_DEPTH 5

float mix(const float& a, const float& b, const float& mix)
{
    return b * mix + a * (1 - mix);
}

//[comment]
// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object that
// is the color of the object at the intersection point, otherwise it returns
// the background color.
//[/comment]
Vec3f trace(
    const Vec3f& rayorig,
    const Vec3f& raydir,
    const std::vector<Spheres>& spheres,
    const int& depth)
{
    //if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
    float tnear = INFINITY;
    const Spheres* sphere = NULL;
    // find intersection of this ray with the sphere in the scene
    for (unsigned i = 0; i < spheres.size(); ++i) {
        float t0 = INFINITY, t1 = INFINITY;
        if (spheres[i].intersect(rayorig, raydir, t0, t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < tnear) {
                tnear = t0;
                sphere = &spheres[i];
            }
        }
    }
    // if there's no intersection return black or background color
    if (!sphere) return Vec3f(2);
    Vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
    Vec3f phit = rayorig + raydir * tnear; // point of intersection
    Vec3f nhit = phit - sphere->center; // normal at the intersection point
    nhit.normalize(); // normalize normal direction
    // If the normal and the view direction are not opposite to each other
    // reverse the normal direction. That also means we are inside the sphere so set
    // the inside bool to true. Finally reverse the sign of IdotN which we want
    // positive.
    float bias = 1e-4; // add some bias to the point from which we will be tracing
    bool inside = false;
    if (raydir.dot(nhit) > 0) nhit = -nhit, inside = true;
    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) {
        float facingratio = -raydir.dot(nhit);
        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
        refldir.normalize();
        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
        Vec3f refraction = 0;
        // if the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) {
            float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
            float cosi = -nhit.dot(raydir);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (
            reflection * fresneleffect +
            refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
    }
    else {
        // it's a diffuse object, no need to raytrace any further
        for (unsigned i = 0; i < spheres.size(); ++i) {
            if (spheres[i].emissionColor.x > 0) {
                // this is a light
                Vec3f transmission = 1;
                Vec3f lightDirection = spheres[i].center - phit;
                lightDirection.normalize();
                for (unsigned j = 0; j < spheres.size(); ++j) {
                    if (i != j) {
                        float t0, t1;
                        if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1)) {
                            transmission = 0;
                            break;
                        }
                    }
                }
                surfaceColor += sphere->surfaceColor * transmission *
                    std::max(float(0), nhit.dot(lightDirection)) * spheres[i].emissionColor;
            }
        }
    }

    return surfaceColor + sphere->emissionColor;
}

//[comment]
// Main rendering function. We compute a camera ray for each pixel of the image
// trace it and return a color. If the ray hits a sphere, we return the color of the
// sphere at the intersection point, else we return the background color.
//[/comment]
void render(const std::vector<Spheres>& spheres)
{
    unsigned width = 640, height = 480;
    Vec3f* image = new Vec3f[width * height], * pixel = image;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);
    // Trace rays
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x, ++pixel) {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vec3f raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(Vec3f(0), raydir, spheres, 0);
            
        }
    }
    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./untitled2.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
            (unsigned char)(std::min(float(1), image[i].y) * 255) <<
            (unsigned char)(std::min(float(1), image[i].z) * 255);
    }
    ofs.close();
    delete[] image;
}

//[comment]
// In the main function, we will create the scene which is composed of 5 spheres
// and 1 light (which is also a sphere). Then, once the scene description is complete
// we render that scene, by calling the render() function.
//[/comment]
int main(int argc, char** argv)
{
    //srand48(13);
    /*std::vector<Spheres> spheres;
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(Spheres(Vec3f(0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0.0));
    spheres.push_back(Spheres(Vec3f(0.0, 0, -20), 4, Vec3f(1.00, 0.32, 0.36), 1, 0.5));
    spheres.push_back(Spheres(Vec3f(5.0, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.0));
    spheres.push_back(Spheres(Vec3f(5.0, 0, -25), 3, Vec3f(0.65, 0.77, 0.97), 1, 0.0));
    spheres.push_back(Spheres(Vec3f(-5.5, 0, -15), 3, Vec3f(0.90, 0.90, 0.90), 1, 0.0));
    // light
    spheres.push_back(Spheres(Vec3f(0.0, 20, -30), 3, Vec3f(0.00, 0.00, 0.00), 0, 0.0, Vec3f(3)));
    render(spheres);*/
   
    Color color(1.00, 0.32, 0.36);
    Color color2(0.90, 0.76, 0.46);
    Color color3(0.65, 0.77, 0.97);
    Color color4(0.90,0.90,0.90);
    Scene scene = Scene();
    //Sphere sphere(color, Point(1200, 1200, 7800), 1);
    Sphere sphere(color); //Une sphere
    Sphere sphere2(color2); //Une sphere
    Sphere sphere3(color3); //Une sphere
    Sphere sphere4(color4); //Une sphere
    Sphere Globe(Color(0.20, 0.20, 0.20)); //sert de sol

    sphere.translate(0, 0, 30);
    sphere.scale(0.4);
    sphere.rotateX(-1);
    
    sphere.material.diffuse = Color(0.25, 0.25, 0.25);
    sphere.material.specular = Color(0.75, 0.75, 0.75);
    sphere.material.shininess = 3;
    sphere.Texture = cv::imread("damier.jpg");

    sphere2.translate(-3.5, -1, 27);
    sphere2.scale(0.8);
    sphere2.material.diffuse = Color(0.25, 0.25, 0.25);
    sphere2.material.specular = Color(0.75, 0.75, 0.75);
    sphere2.material.shininess = 3;

    sphere3.translate(-3.5, 0, 33);
    sphere3.material.diffuse = Color(0.25, 0.25, 0.25);
    sphere3.material.specular = Color(0.75, 0.75, 0.75);
    sphere3.material.shininess = 3;

    sphere4.translate(4.5, 0, 27);
    sphere4.scale(0.6);
    sphere4.material.diffuse = Color(0.25, 0.25, 0.25);
    sphere4.material.specular = Color(0.75, 0.75, 0.75);
    sphere4.material.shininess = 3;


    Triangle triangle(color3, Vector(-1, 1, 0), Vector(1, -1, 0));
    triangle.material.diffuse = Color(0.25, 0.25, 0.25);
    triangle.material.specular = Color(0.75, 0.75, 0.75);
    triangle.material.shininess = 3;
    triangle.translate(2, 0, 10);
    


    Cube cube(Color(0,1,0));
    cube.translate(-10, 0, 10);
    cube.Texture = cv::imread("damier.jpg");
    cube.rotateX(0.3);
    //cube.rotateY(30);
    //cube.rotateZ(40);

    cube.material.diffuse = Color(0.25, 0.25, 0.25);
    cube.material.specular = Color(0.75, 0.75, 0.75);
    cube.material.shininess = 3;

    CylindreInfini cylindre(Color(1, 0, 0));
    cylindre.translate(-15, 5, 30);
    cylindre.rotateX(1.57);
    cylindre.material.diffuse = Color(0.25, 0.25, 0.25);
    cylindre.material.specular = Color(0.75, 0.75, 0.75);
    cylindre.material.shininess = 3;

    Light light = Light();
    light.translate(0, -20, -30); // La lumiére est située au dessus de la sphere rouge
    light.id = Color(0.8,0.8,0.8);
    light.is = Color(0.5,0.5,0.5);

    Plan plan(Color(0.20,0.20,0.20));
    //Plan plan(Color(1,1,1));
    plan.translate(0, -3, 0);
    plan.normale = Vector(0, 1, 0);
    plan.material.diffuse = Color(0, 0, 0);
    plan.material.specular = Color(0, 0, 0);
    plan.Texture = cv::imread("damier.jpg");
    scene.addObject(&triangle);
    scene.addObject(&sphere);
    scene.addObject(&sphere2);
    scene.addObject(&sphere3);
    scene.addObject(&sphere4);
    scene.addObject(&cylindre);
    scene.addObject(&cube);
    scene.addObject(&plan);
   
    //scene.addObject(&Globe);

    
    scene.addLight(light);

    
    int n = -1;
    int count = 0;
    //while (true) {

        //cv::waitKey(1);

        Tracer tracer = Tracer();
        tracer.render(scene);

        /*sphere.translate(n, 0, 0);

        count++;

        if (count == 10) {
            n *= -1;
            count = 0;
        }

    }*/
    
    

    return 0;
}