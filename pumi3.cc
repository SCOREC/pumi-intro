#include <mpi.h>
#include "PCU.h"
#include "pumi.h"

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  pumi_start();

  pGeom g = pumi_geom_load("cube.dmg", "mesh");
  pMesh mesh = pumi_mesh_load(g, "parallelMesh.smb", pumi_size());

  pMeshEnt vertex;
  pMeshIter it;
  int numOwned = 0;
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (pumi_ment_isOwned(vertex))
      ++numOwned;
  mesh->end(it);
  int offset = numOwned;
  PCU_Exscan_Ints(&offset, 1);
  pNumbering numbers = pumi_numbering_create(
      mesh, "my_numbers", pumi_mesh_getShape(mesh), 1);
  int i = offset;
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (pumi_ment_isOwned(vertex))
      pumi_node_setNumber(numbers, vertex, 0, 0, i++);
  mesh->end(it);
  PCU_Comm_Begin();
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (pumi_ment_isOwned(vertex)) {
      Copies remotes;
      pumi_ment_getAllRmt(vertex, remotes);
      int number = pumi_node_getNumber(numbers, vertex, 0, 0);
      for (pCopyIter it = remotes.begin();
           it != remotes.end(); ++it) {
        PCU_COMM_PACK(it->first, it->second);
        PCU_COMM_PACK(it->first, number);
      }
    }
  mesh->end(it);
  PCU_Comm_Send();
  while (PCU_Comm_Receive()) {
    int number;
    PCU_COMM_UNPACK(vertex);
    PCU_COMM_UNPACK(number);
    pumi_node_setNumber(numbers, vertex, 0, 0, number);
  }
  pumi_mesh_write(mesh, "numbered", "vtk");
  pumi_mesh_delete(mesh);
  pumi_finalize();
  MPI_Finalize();
}


