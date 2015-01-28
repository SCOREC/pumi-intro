#include <apf.h>
#include <gmi_null.h>
#include <apfMDS.h>
#include <apfMesh2.h>
#include <PCU.h>

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  gmi_register_null();
  gmi_model* g = gmi_load(".null");
  apf::Mesh2* mesh = apf::makeEmptyMdsMesh(g, 3, false);
  apf::Vector3 points[4] =
  {apf::Vector3(0,0,0),
   apf::Vector3(1,0,0),
   apf::Vector3(0,1,0),
   apf::Vector3(0,0,1)};
  apf::MeshEntity* vertices[4];
  for (int i = 0; i < 4; ++i) {
    vertices[i] = mesh->createVert(0);
    mesh->setPoint(vertices[i], 0, points[i]);
  }
  apf::buildElement(mesh, 0, apf::Mesh::TET, vertices);
  apf::deriveMdsModel(mesh);
  mesh->acceptChanges();
  mesh->verify();
  apf::writeVtkFiles("onetet", mesh);
  mesh->destroyNative();
  apf::destroyMesh(mesh);
  PCU_Comm_Free();
  MPI_Finalize();
}
