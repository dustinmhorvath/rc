#include <libmap.h>
#include <stdlib.h>

#define MAX_OBM_SIZE 512000

void subr (int64_t I0[], int64_t Out[], int num, int64_t *time, int mapnum);

int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    int64_t *A, *B;
    int64_t tm;
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
    if ((num < 1) || (num > MAX_OBM_SIZE)) {
        fprintf (stderr, "number of elements must be in the range 1 through %d\n", MAX_OBM_SIZE);
		exit (1);
	}

    A = (int64_t*) Cache_Aligned_Allocate (num * sizeof (int64_t));
    B = (int64_t*) Cache_Aligned_Allocate (2 * num * sizeof (int64_t));

    srandom (99);

    for (i=0; i<num; i++) {
        A[i] = random ();
	}

    map_allocate (1);

    subr (A, B, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<num; i++) {
        fprintf (res_map, "%lld %lld\n", B[i], B[num+i]);
        fprintf (res_cpu, "%lld %lld\n", A[i]+9, A[i]*5);
	}

    map_free (1);

    exit(0);
}
