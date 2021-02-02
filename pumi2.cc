#include <mpi.h>
#include "pumi.h"

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  pumi_start();

  pGeom g = pumi_geom_load("", "null");
  pMesh mesh = pumi_mesh_create(g, 3, false);
  double points[4][3] = {{0,0,0},{1,0,0},{0,1,0},{0,0,1}};
  pMeshEnt vertices[4];

  for (int i = 0; i < 4; ++i) 
    vertices[i] = pumi_mesh_createVtx(mesh, NULL, points[i]);
  pumi_mesh_createElem(mesh, NULL, PUMI_TET, vertices);

  pumi_mesh_freeze(mesh);
  pumi_mesh_verify(mesh);
  pumi_mesh_write(mesh, "onetet", "vtk");
  pumi_mesh_delete(mesh);

  pumi_finalize();
  MPI_Finalize();
}
