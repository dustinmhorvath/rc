#include <libmap.h>
#include <stdlib.h>

#define MAX_OBM_SIZE 512000

void subr (int64_t I0[], int64_t Out0[], int num, int64_t *time, int mapnum);

int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    int64_t *A, *B, *ResB;
    int64_t tm0, tm1;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
    }
    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
    }
    if (argc < 2) {
		fprintf (stderr, "need number of elements as arg\n");
		exit (1);
	}
    if (sscanf (argv[1], "%d", &num) < 1) {
		fprintf (stderr, "need number of elements as arg\n");
		exit (1);
	}
    if (num > MAX_OBM_SIZE) {
        fprintf (stderr, "number of elements must be no more than %d\n", MAX_OBM_SIZE);
		exit (1);
	}

    A = (int64_t*) Cache_Aligned_Allocate (num * sizeof (int64_t));
    B = (int64_t*) Cache_Aligned_Allocate ((num-2) * sizeof (int64_t));
    ResB = (int64_t*) Cache_Aligned_Allocate ((num-2) * sizeof (int64_t));

    srandom (99);

    for (i=0; i<num; i++)
        A[i] = random ();

    for (i=0; i<num-2; i++)
        ResB[i] = A[i] + A[i+1] + A[i+2];

    map_allocate (1);

    subr (A, B, num, &tm0, mapnum);

    printf ("%lld clocks\n", tm0);

    for (i=0; i<num-2; i++) {
        fprintf (res_map, "%lld\n", B[i]);
        fprintf (res_cpu, "%lld\n", ResB[i]);
	}

    map_free (1);

    exit(0);
}
