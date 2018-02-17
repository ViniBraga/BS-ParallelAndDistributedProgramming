#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main()
{


  struct timeval ti, tf;
  long i,j;

  gettimeofday(&ti, NULL);

  /* Faz algo aqui */
  for (i = 0L; i < 1000000000L; i++) { }
  /* Aqui termina o que estava sendo feito */

  gettimeofday(&tf, NULL);

  printf("%ds%dms%dus\n", (int) (tf.tv_sec - ti.tv_sec), (int) (tf.tv_usec-ti.tv_usec)/1000, (int) (tf.tv_usec-ti.tv_usec)%1000 );

  return 0;
}