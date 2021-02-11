#include <PCU.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  int message;
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  message = PCU_Comm_Self() + 1;
  PCU_Comm_Begin();
  if (PCU_Comm_Self() == 0)
    PCU_COMM_PACK(1, message);
  else
    PCU_COMM_PACK(0, message);
  PCU_Comm_Send();
  while (PCU_Comm_Receive()) {
    PCU_COMM_UNPACK(message);
    printf("%d received \"%d\" from %d\n",
        PCU_Comm_Self(), message, PCU_Comm_Sender());
  }
  PCU_Comm_Free();
  MPI_Finalize();
  return 0;
}
