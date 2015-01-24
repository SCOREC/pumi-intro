#include <apf.h>
#include <gmi_mesh.h>
#include <apfMDS.h>
#include <apfMesh2.h>
#include <apfNumbering.h>
#include <PCU.h>

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  PCU_Protect();
  gmi_register_mesh();
  apf::Mesh2* mesh = apf::loadMdsMesh(
      "cube.dmg", "parallelMesh.smb");
  apf::MeshEntity* vertex;
  apf::MeshIterator* it;
  int numOwned = 0;
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (mesh->isOwned(vertex))
      ++numOwned;
  mesh->end(it);
  int offset = numOwned;
  PCU_Exscan_Ints(&offset, 1);
  apf::Numbering* numbers = apf::createNumbering(
      mesh, "my_numbers", mesh->getShape(), 1);
  int i = offset;
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (mesh->isOwned(vertex))
      apf::number(numbers, vertex, 0, 0, i++);
  mesh->end(it);
  PCU_Comm_Begin();
  it = mesh->begin(0);
  while ((vertex = mesh->iterate(it)))
    if (mesh->isOwned(vertex)) {
      apf::Copies remotes;
      mesh->getRemotes(vertex, remotes);
      int number = apf::getNumber(numbers, vertex, 0, 0);
      for (apf::Copies::iterator it = remotes.begin();
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
    apf::number(numbers, vertex, 0, 0, number);
  }
  apf::writeVtkFiles("numbered", mesh);
  mesh->destroyNative();
  apf::destroyMesh(mesh);
  PCU_Comm_Free();
  MPI_Finalize();
}


