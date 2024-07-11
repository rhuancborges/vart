#include <iostream>
#include <vector>
#include <vart/meshobject.h>
#include <vart/point4d.h>
#include <vart/contrib/viewerglutogl.h>

using namespace std;
using VART::Point4D;

int main(int argc, char* argv[]){
    VART::MeshObject piramide;
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::Scene scene; 
    static VART::ViewerGlutOGL viewer; 
    VART::Camera camera(VART::Point4D(2,-10,0), Point4D::ORIGIN(), Point4D::Z());

    vector<VART::Point4D> vertices; 
    vertices.push_back(VART::Point4D(-2,-2,-2));
    vertices.push_back(VART::Point4D(2,-2,-2));
    vertices.push_back(VART::Point4D(2,2,-2));
    vertices.push_back(VART::Point4D(-2,2,-2));
    vertices.push_back(VART::Point4D(0,0,0));
    vertices.push_back(VART::Point4D(-2,-2,2));
    vertices.push_back(VART::Point4D(2,-2,2));
    vertices.push_back(VART::Point4D(2,2,2));
    vertices.push_back(VART::Point4D(-2,2,2));
    piramide.SetVertices(vertices);
    piramide.AddFace("3 2 1 0");
    piramide.AddFace("4 1 0");
    piramide.AddFace("4 2 1");
    piramide.AddFace("4 3 2");
    piramide.AddFace("4 0 3");
    piramide.AddFace("8 7 6 5");
    piramide.AddFace("5 6 4");
    piramide.AddFace("6 7 4");
    piramide.AddFace("7 8 4");
    piramide.AddFace("8 5 4");
    piramide.SetMaterial(VART::Material::PLASTIC_GREEN());

    VART::Light luz(VART::Light::SUN());
    luz.SetLocation(VART::Point4D(2, 0, 10));
    scene.AddLight(luz);
    scene.AddCamera(&camera);
    scene.AddObject(&piramide);

    viewer.SetScene(scene);
    viewer.SetTitle("Piramide");

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}