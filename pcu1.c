#include <PCU.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  int i;
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  if (PCU_Comm_Self()==0)
    printf("There are %d total processes:\n", PCU_Comm_Peers());
  printf("Greetings from process %d\n", PCU_Comm_Self());
  i = PCU_Comm_Self() + 1;
  PCU_Add_Ints(&i, 1);
  if (PCU_Comm_Self()==0)
    printf("The sum of the integers from 1 to %d is %d\n", PCU_Comm_Peers(), i);
  PCU_Comm_Free();
  MPI_Finalize();
  return 0;
}
