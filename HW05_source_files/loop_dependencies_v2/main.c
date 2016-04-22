#include <libmap.h>
#include <stdlib.h>

#define MAX_OBM_SIZE 512000

void subr (int64_t I0[], int n0, int n1, int64_t *res, int64_t *time, int mapnum);

int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, n0, n1, num;
    int64_t *A, *B, *MB;
    int64_t tm, res, accum=0;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
    }
    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
    }
    if (argc < 3) {
		fprintf (stderr, "need two dimensions as arg\n");
		exit (1);
	}
    if (sscanf (argv[1], "%d", &n0) < 1) {
		fprintf (stderr, "need two dimensions as arg\n");
		exit (1);
	}
    if (sscanf (argv[2], "%d", &n1) < 1) {
		fprintf (stderr, "need two dimensions as arg\n");
		exit (1);
	}
    if ((n0 < 1) || (n1 < 1) || (n0*n1 > MAX_OBM_SIZE)) {
        fprintf (stderr, " n0 %i n1 %i product of elements must be in the range 1 through %d\n", n0,n1,MAX_OBM_SIZE);
		exit (1);
	}

    num = n0 * n1;

    A = (int64_t*) Cache_Aligned_Allocate (num * sizeof (int64_t));

    srandom (99);

    for (i=0; i<num; i++) {
        A[i] = random () & 0xff;
		if (A[i] < 128)
			accum += A[i];
	}

    map_allocate (1);

    subr (A, n0, n1, &res, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    fprintf (res_map, "%lld\n", res);
    fprintf (res_cpu, "%lld\n", accum);

    map_free (1);

    exit(0);
}
