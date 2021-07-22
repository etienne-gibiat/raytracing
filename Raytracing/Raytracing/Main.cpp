#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <windows.h>
#include <list>
#include "opencv2/highgui/highgui.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "CylindreInfini.hpp"
#include "Triangle.hpp"
#include "Tracer.hpp"
#include "Plan.hpp"
#include "json.h"

#define M_PI 3.141592653589793
#define INFINITY 1e8

std::vector<std::string> FindFilesInDirectory() {
    std::string sT, sP;
    WIN32_FIND_DATAA FindFileData; // Pointeur pour les fichiers
    HANDLE hF;
    sP = sT;
    sP.append("\\");
    sT.append("*"); // complete le chemin pour tout recuperer
    std::list<std::string> lst;
    hF = FindFirstFileA(sT.data(), &FindFileData); // Trouve le premier fichier du repertoire
    do {
        lst.push_back(sP + FindFileData.cFileName);
    } while (FindNextFileA(hF, &FindFileData)); // Ajoute le nom des fichiers à la liste des fichiers
    FindClose(hF);
    lst.pop_front();
    lst.pop_front(); // Retire le dossier courant ainsi que le dossier parent (. et ..)
    std::vector<std::string> lstScenes;
    for (auto it = lst.begin(); it != lst.end(); it++) {
        std::string tmp = *it;
        if (tmp.substr(tmp.find_last_of(".") + 1) == "json") {
            tmp.erase(0, 1);
            lstScenes.push_back(tmp);
        }

    }
    return lstScenes; // Retourne la liste des fichiers
}

int main(int argc, char** argv)
{
    
    std::cout << std::endl << "---------------------" << std::endl << "Initialisation du Programme" << std::endl << "---------------------" << std::endl;
    std::string saisieValid = "n";
    int x = 0;
    int y = 0;
    int sceneChosed;
    std::string imageName;
    std::string sceneName;
    bool ombre = false;
    while (saisieValid != "y") {
        std::cout << std::endl << "---------------------" << std::endl << std::endl <<"Choisir la taille en longueur : ";
        std::cin >> x;
        std::cout << "Choisir la taille en largeur : ";
        std::cin >> y;
        std::cout << "Choisir le nom de l'image : ";
        std::cin >> imageName;
        imageName += ".jpg";

        std::cout << "Voici la liste ci dessous des scenes : " << std::endl;
        std::vector<std::string> lstScenes = FindFilesInDirectory();
        int i = 1;
        for (auto it = lstScenes.begin(); it != lstScenes.end(); ++it, ++i) {
            std::cout << *it << " (" << i << ") "<< std::endl;
        }
        std::cout << "Inserer le numero de la scene a charger : ";
        std::cin >> sceneChosed;
        sceneChosed -= 1;
        sceneName = lstScenes.at(sceneChosed);

        std::cout << std::endl << "Voulez vous activer les ombres ? (y/n)";
        std::string ombreStr;
        std::cin >> ombreStr;
        if (ombreStr == "y") {
            ombre = true;
        }
        if (ombre) {
            std::cout << "Vous avez choisi une taille de " << x << " x " << y << " avec les ombres activees" << std::endl;
        }
        else {
            std::cout << "Vous avez choisi une taille de " << x << " x " << y << " avec les ombres desactivees" << std::endl;
        }
        std::cout << "Le fichier de scene est " << sceneName <<" et l'image sera enregistree sous le nom " << imageName << std::endl;
        
        std::cout << "Confirmez vous les parametres ? (y/n)";
        std::cin >> saisieValid;
    }
    std::cout << std::endl << "---------------------" << std::endl;
    std::cout << "Demarrage du programme de RayTracing" << std::endl;
    
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
    JSONValue myScene; 
    JSONValue SphereJson;
    JSONValue CubeJson;
    JSONValue TriangleJson;
    JSONValue CylindreJson;
    JSONValue LightJson;
    cv::Mat texture;
    myScene = JSON::load(sceneName);

    for (auto it = myScene.m_object.begin(); it != myScene.m_object.end(); ++it)
    {
        

        if (it->first == "Spheres") {
            JSONValue obj = myScene.m_object[it->first];
            for (int i = 0; i < obj.size(); ++i) {

                SphereJson = obj[i];


                float r = SphereJson["Color"]["r"].asDouble();
                float g = SphereJson["Color"]["g"].asDouble();
                float b = SphereJson["Color"]["b"].asDouble();
                Color c(r, g, b);
                Sphere* jsonSphere = new Sphere(c);
                jsonSphere->translate(SphereJson["Translate"]["x"].asDouble(), SphereJson["Translate"]["y"].asDouble(), SphereJson["Translate"]["z"].asDouble());
                jsonSphere->scale(SphereJson["Scale"].asDouble());
                jsonSphere->rotateX(SphereJson["RotateX"].asDouble());
                jsonSphere->rotateY(SphereJson["RotateY"].asDouble());
                jsonSphere->rotateZ(SphereJson["RotateZ"].asDouble());
                jsonSphere->material.diffuse = Color(0.25, 0.25, 0.25);
                jsonSphere->material.specular = Color(0.75, 0.75, 0.75);
                jsonSphere->material.shininess = 3;
                std::string textureName = SphereJson["TextureName"].asString();
                if (textureName != "") {
                    texture = cv::imread(textureName);
                    jsonSphere->Texture = &texture;
                }
                
                scene.addObject(jsonSphere);

            }
        }

        if (it->first == "Cubes") {

            JSONValue obj = myScene.m_object[it->first];
            for (int i = 0; i < obj.size(); ++i) {

                CubeJson = obj[i];


                float r = CubeJson["Color"]["r"].asDouble();
                float g = CubeJson["Color"]["g"].asDouble();
                float b = CubeJson["Color"]["b"].asDouble();
                Color c(r, g, b);
                Cube* jsonCube = new Cube(c);
                jsonCube->translate(CubeJson["Translate"]["x"].asDouble(), CubeJson["Translate"]["y"].asDouble(), CubeJson["Translate"]["z"].asDouble());
                jsonCube->scale(CubeJson["Scale"].asDouble());
                jsonCube->rotateX(CubeJson["RotateX"].asDouble());
                jsonCube->rotateY(CubeJson["RotateY"].asDouble());
                jsonCube->rotateZ(CubeJson["RotateZ"].asDouble());
                jsonCube->material.diffuse = Color(0.25, 0.25, 0.25);
                jsonCube->material.specular = Color(0.75, 0.75, 0.75);
                jsonCube->material.shininess = 3;
                std::string textureName = CubeJson["TextureName"].asString();
                if (textureName != "") {
                    texture = cv::imread(textureName);
                    jsonCube->Texture = &texture;
                }

                scene.addObject(jsonCube);

            }
        }


        if (it->first == "Triangles") {

            JSONValue obj = myScene.m_object[it->first];
            for (int i = 0; i < obj.size(); ++i) {

                TriangleJson = obj[i];


                float r = TriangleJson["Color"]["r"].asDouble();
                float g = TriangleJson["Color"]["g"].asDouble();
                float b = TriangleJson["Color"]["b"].asDouble();
                Color c(r, g, b);
                Triangle* jsonTriangle = new Triangle(c,Vector(-1,1,0),Vector(1,-1,0));
                jsonTriangle->translate(TriangleJson["Translate"]["x"].asDouble(), TriangleJson["Translate"]["y"].asDouble(), TriangleJson["Translate"]["z"].asDouble());
                jsonTriangle->scale(TriangleJson["Scale"].asDouble());
                jsonTriangle->rotateX(TriangleJson["RotateX"].asDouble());
                jsonTriangle->rotateY(TriangleJson["RotateY"].asDouble());
                jsonTriangle->rotateZ(TriangleJson["RotateZ"].asDouble());
                jsonTriangle->material.diffuse = Color(0.25, 0.25, 0.25);
                jsonTriangle->material.specular = Color(0.75, 0.75, 0.75);
                jsonTriangle->material.shininess = 3;
                std::string textureName = TriangleJson["TextureName"].asString();
                if (textureName != "") {
                    texture = cv::imread(textureName);
                    jsonTriangle->Texture = &texture;
                }

                scene.addObject(jsonTriangle);

            }
        }

        if (it->first == "Cylindres") {

            JSONValue obj = myScene.m_object[it->first];
            for (int i = 0; i < obj.size(); ++i) {

                CylindreJson = obj[i];


                float r = CylindreJson["Color"]["r"].asDouble();
                float g = CylindreJson["Color"]["g"].asDouble();
                float b = CylindreJson["Color"]["b"].asDouble();
                Color c(r, g, b);
                CylindreInfini* jsonCylindre = new CylindreInfini(c);
                jsonCylindre->translate(CylindreJson["Translate"]["x"].asDouble(), CylindreJson["Translate"]["y"].asDouble(), CylindreJson["Translate"]["z"].asDouble());
                jsonCylindre->scale(CylindreJson["Scale"].asDouble());
                jsonCylindre->rotateX(CylindreJson["RotateX"].asDouble());
                jsonCylindre->rotateY(CylindreJson["RotateY"].asDouble());
                jsonCylindre->rotateZ(CylindreJson["RotateZ"].asDouble());
                jsonCylindre->material.diffuse = Color(0.25, 0.25, 0.25);
                jsonCylindre->material.specular = Color(0.75, 0.75, 0.75);
                jsonCylindre->material.shininess = 3;
                std::string textureName = CylindreJson["TextureName"].asString();
                if (textureName != "") {
                    texture = cv::imread(textureName);
                    jsonCylindre->Texture = &texture;
                }

                scene.addObject(jsonCylindre);

            }
        }

        if (it->first == "Lights") {

            JSONValue obj = myScene.m_object[it->first];
            for (int i = 0; i < obj.size(); ++i) {

                LightJson = obj[i];


                float rId = LightJson["Id"]["r"].asDouble();
                float gId = LightJson["Id"]["g"].asDouble();
                float bId = LightJson["Id"]["b"].asDouble();

                float rIs = LightJson["Is"]["r"].asDouble();
                float gIs = LightJson["Is"]["g"].asDouble();
                float bIs = LightJson["Is"]["b"].asDouble();
                Color Id(rId, gId, bId);
                Color Is(rIs, gIs, bIs);
                Light* light = new Light();
                light->translate(LightJson["Translate"]["x"].asDouble(), LightJson["Translate"]["y"].asDouble(), LightJson["Translate"]["z"].asDouble());
                light->id = Id;
                light->is = Is;
                scene.addLight(*light);

            }
        }
    }
    
    Plan plan(Color(0.20,0.20,0.20));
    plan.translate(0, -3, 0);
    plan.normale = Vector(0, 1, 0);
    plan.material.diffuse = Color(0, 0, 0);
    plan.material.specular = Color(0, 0, 0);
    //plan.Texture = cv::imread("damier.jpg");
    scene.addObject(&plan);

    
    int n = -1;
    int count = 0;
    //while (true) {

        //cv::waitKey(1);

        Tracer tracer = Tracer();
        tracer.render(scene,x,y, imageName, ombre);

        /*sphere.translate(n, 0, 0);

        count++;

        if (count == 10) {
            n *= -1;
            count = 0;
        }

    }*/
    
    

    return 0;
}