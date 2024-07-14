#include <iostream>
#include <vector>
#include <vart/meshobject.h>
#include <vart/mesh.h>
#include <vart/point4d.h>
#include <vart/contrib/viewerglutogl.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using VART::Point4D;

int main(int argc, char* argv[]){
    VART::MeshObject terreno;
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::Scene scene; 
    static VART::ViewerGlutOGL viewer; 
    VART::Camera camera(Point4D(10,-10,12), Point4D(10,10,0), Point4D::Z());
    

    // Gerar matriz de pontos
    vector<Point4D> matrix;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int altura;
    srand(time(0));
    do{
        altura = rand()%2;
        matrix.push_back(Point4D(x,y,altura));
        if(x<19){
          x++;  
        }else{  
          y++;
          x=0;  
        }
        
    }while(y<20);

    terreno.SetVertices(matrix);

    // Gerar Meshes
    int ultimaLinha = 19;
    int linha = 0, coluna;
    while (linha < ultimaLinha){
        VART::Mesh m;
        m.type = VART::Mesh::TRIANGLE_STRIP;
        coluna = 0;
        m.indexVec.reserve(40*sizeof(unsigned int));
        while (coluna < 20){
            m.indexVec.push_back(linha*20+coluna);
            m.indexVec.push_back((linha+1)*20+coluna);
            coluna++;
        }
        terreno.AddMesh(m);
        linha++;
    }
    terreno.ComputeVertexNormals();
    terreno.SetMaterial(VART::Material::PLASTIC_GREEN());


    VART::Light luz(VART::Light::SUN());
    luz.SetLocation(VART::Point4D(2, 0, 10));
    scene.AddLight(luz);
    scene.AddCamera(&camera);
    scene.AddObject(&terreno);
    //scene.MakeCameraViewAll();

    viewer.SetScene(scene);
    viewer.SetTitle("Terreno");

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}