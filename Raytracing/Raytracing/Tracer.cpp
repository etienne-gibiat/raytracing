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
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"



Tracer::Tracer()
{
}
unsigned x, y;
void Tracer::render(Scene scene, int w, int h, std::string imageName, bool ombre) {

    

    const float gamma = 1.f / 2.2f;

    //unsigned width = 850, height = 480;
    unsigned width = w*2, height = h*2;
    cv::Mat mat = cv::Mat::ones(height, width, CV_8UC3);
    Color pixelColor;
    Color* image = new Color[width * height], * pixel = image;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 60, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);

    // Trace rays
    for (y = 0; y < height; ++y) {
        
        for (x = 0; x < width; ++x, ++pixel) {


            if (y / (height * 0.25) == 1 && x == 0) {
                std::cout << "25% termine" << std::endl;
            }
            if (y / (height * 0.5) == 1 && x == 0) {
                std::cout << "50% termine" << std::endl;
            }
            if (y / (height * 0.75) == 1 && x == 0) {
                std::cout << "75% termine" << std::endl;
            }
            if ((y + 1) / (height) == 1 && x == 0) {
                std::cout << "100% termine" << std::endl;
            }
            Camera camera(5, aspectratio);
            camera.translate(0, 0, -10);

            float xprim = (float)x / (float)width;
            float yprim = (float)y / (float)height;
            Ray ray = camera.getRay(xprim, yprim);
            
            *pixel = trace(ray, scene, 5, ombre);
            mat.at<cv::Vec3b>(y, x) = cv::Vec3b(pixel->tabColor[2]*255, pixel->tabColor[1]*255, pixel->tabColor[0]*255);
            
        }
    }

    cv::Mat res = cv::Mat::ones(h, w, CV_8UC3);
    for (y = 0; y < h; ++y) {

        for (x = 0; x < w; ++x) {
            cv::Vec3b coin1 = mat.at<cv::Vec3b>(y*2, x*2);
            cv::Vec3b coin2 = mat.at<cv::Vec3b>(y*2, x*2+1);
            cv::Vec3b coin3 = mat.at<cv::Vec3b>(y*2+1, x*2);
            cv::Vec3b coin4 = mat.at<cv::Vec3b>(y*2+1, x*2+1);
            
            float sumR = (float)coin1.val[2] + (float)coin2.val[2] + (float)coin3.val[2] + (float)coin4.val[2];
            float sumG = (float)coin1.val[1] + (float)coin2.val[1] + (float)coin3.val[1] + (float)coin4.val[1];
            float sumB = (float)coin1.val[0] + (float)coin2.val[0] + (float)coin3.val[0] + (float)coin4.val[0];
            sumR /= 4;
            sumG /= 4;
            sumB /= 4;
            cv::Vec3b average = cv::Vec3b(sumB, sumG, sumR);
            res.at<cv::Vec3b>(y, x) = average;
        }
    }
    cv::imshow("Raytracing", res);
    cv::waitKey(0);
    cv::imwrite(imageName, res);
    delete[] image;

}

Color Tracer::getImpactColor(Ray& ray, Object* obj, Point& impact, Scene& scene) {

   Material m = obj->getMaterial(impact);
    Ray normal = obj->getNormal(impact, ray.origin);
    //Color res(normal.vector[0], normal.vector[1], normal.vector[2]);
    //return res;
    Color c = m.ambiant.mul(scene.getAmbiant());
    for (int l = 0; l < scene.nbLights(); l++) {
        Light light = scene.getLight(l);
        Vector lv = light.getVectorToLight(impact);
        float alpha = lv.dot(normal.vector);
        if (alpha > 0)
            c += (light.id).mul(m.diffuse) * alpha;

        Vector rm = (2 * lv.dot(normal.vector) * normal.vector) - lv;
        Vector rm2 = -rm;
        float beta = -rm.dot(ray.vector);
        if (beta > 0)
            c += (light.is).mul(m.specular) * pow(beta, m.shininess);
    }

    return c;

}

Color Tracer::trace(Ray ray, Scene scene, int depth, bool ombre)
{
    
    Point impact = Point();
    Object* object = scene.closer_intersected(ray, impact);
    
    Color res;
    if (!object) {
        res = scene.getBackGroundImage(x,y);
    }
    else {
        res = getImpactColor(ray, object, impact, scene);
        if (object->Texture.data != NULL) {
            Point p = object->getTextureCoordinates(impact);
            int xt = p[0] * object->Texture.cols;
            int yt = p[1] * object->Texture.rows;
            if (xt < 0) {
                xt = -xt;
            }
            if (yt < 0) {
                yt = -yt;
            }
            xt = xt % object->Texture.cols;
            yt = yt % object->Texture.rows;
            cv::Vec3b tmp = object->Texture.at<cv::Vec3b>(yt, xt);
            float max = 255;
            float r = tmp[2] / max;
            float g = tmp[1] / max;
            float b = tmp[0] / max;
            res = res * Color(r, g, b);
        }
        if (ombre) {
            Light l = scene.getLight(0);
            Ray lv = l.getRayToLight(impact);
            lv.origin = lv.origin + Point(lv.vector[0], lv.vector[1], lv.vector[2]);
            Color transmission(1, 1, 1);
            Vector lightDirection = lv.vector;
            lightDirection.normalized();

            std::vector<Object*> obj = scene.getObjects();
            Point impact2 = Point();
            for (unsigned j = 0; j < obj.size(); ++j) {
                float t0, t1;
                if (obj[j]->intersect(lv, impact2, t0, t1)) {
                    if (obj[j] == object) {
                        transmission = Color(0.7, 0.7, 0.7);
                    }
                    else {
                        transmission = Color(0.3, 0.3, 0.3);
                    }
                    break;
                }

            }
            res = res * transmission;
        }
        
    }
    Color res2(res[0], res[1], res[2]);
    return res2;
}