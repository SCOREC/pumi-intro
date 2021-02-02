#include <mpi.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "pumi.h"

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  pumi_start(); // equivalent to PCU_Comm_Init()
  pGeom g = pumi_geom_load("cube.dmg", "mesh");
  pMesh mesh = pumi_mesh_load(g, "tet-mesh-1.smb", pumi_size());
  pMeshIter it = mesh->begin(pumi_mesh_getDim(mesh));
  pMeshEnt e;
  int elm=0;
  std::cout <<"element_index (x0,y0,z0) (x1,y1,z1) ... (x3,y3,z3)\n";
  while ((e = mesh->iterate(it))) {
    std::vector<pMeshEnt> vertices;
    pumi_ment_getAdj(e, 0, vertices);
    size_t numVertices = vertices.size();
    std::cout << elm << " ";
    for (size_t i = 0; i < numVertices; ++i) {
      Vector3 pt;
      pumi_node_getCoordVector(vertices[i], 0, pt);
      std::cout << std::setprecision(3) << pt << " ";
    }
    std::cout<<"\n";
    elm++;
  }
  mesh->end(it);
  pumi_mesh_delete(mesh);
  pumi_finalize(); // equivalent to PCU_Comm_Free()
  MPI_Finalize();
}
