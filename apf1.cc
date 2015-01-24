#include <apf.h>
#include <gmi_mesh.h>
#include <apfMDS.h>
#include <apfMesh2.h>
#include <PCU.h>

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  gmi_register_mesh();
  apf::Mesh2* mesh = apf::loadMdsMesh("cube.dmg", "tet-mesh-1.smb");
  apf::MeshIterator* it = mesh->begin(mesh->getDimension());
  apf::MeshEntity* e;
  while ((e = mesh->iterate(it))) {
    apf::Downward vertices;
    int numVertices;
    numVertices = mesh->getDownward(e, 0, vertices);
    for (int i = 0; i < numVertices; ++i) {
      apf::Vector3 point;
      mesh->getPoint(vertices[i], 0, point);
      std::cout << point << ' ';
    }
    std::cout << '\n';
  }
  mesh->end(it);
  mesh->destroyNative();
  apf::destroyMesh(mesh);
  PCU_Comm_Free();
  MPI_Finalize();
}

