#include <mpi.h>
#include <vector>
#include "pumi.h"

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  pumi_start(); // equivalent to PCU_Comm_Init()
  pGeom g = pumi_geom_load("cube.dmg", "mesh");
  pMesh mesh = pumi_mesh_load(g, "tet-mesh-1.smb", pumi_size());
  pMeshIter it = mesh->begin(pumi_mesh_getDim(mesh));
  pMeshEnt e;
  while ((e = mesh->iterate(it))) {
    std::vector<pMeshEnt> vertices;
    pumi_ment_getAdj(e, 0, vertices);
    size_t numVertices = vertices.size();
    for (size_t i = 0; i < numVertices; ++i) {
      double point[3];
      pumi_node_getCoord(vertices[i], 0, point);
      std::cout <<"point "<<i<<": "<<point[0]<<' '<<point[1]<<' '<<point[2]<<' ';
    }
    std::cout<<"\n";
  }
  mesh->end(it);
  pumi_mesh_delete(mesh);
  pumi_finalize(); // equivalent to PCU_Comm_Free()
  MPI_Finalize();
}
