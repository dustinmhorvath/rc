#include <libmap.h>
#include <stdlib.h>

#define SZ 65536

void subr (int64_t*, int64_t*, int64_t*, int64_t*, int, int64_t*, int);

int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    int64_t *A, *B, *C, *D;
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
		fprintf (stderr, "need number of elements (up to %d) as arg\n", SZ);
		exit (1);
	}

    if (sscanf (argv[1], "%d", &num) < 1) {
		fprintf (stderr, "need number of elements (up to %d) as arg\n", SZ);
		exit (1);
	}

    if (num > SZ) {
		fprintf (stderr, "need number of elements (up to %d) as arg\n", SZ);
		exit (1);
	}

    A = (int64_t*) Cache_Aligned_Allocate (SZ * sizeof (int64_t));
    B = (int64_t*) Cache_Aligned_Allocate (SZ * sizeof (int64_t));
    C = (int64_t*) Cache_Aligned_Allocate (SZ * sizeof (int64_t));
    D = (int64_t*) Cache_Aligned_Allocate (SZ * sizeof (int64_t));

    srandom (99);

    for (i=0; i<SZ; i++) {
        A[i] = random ();
        B[i] = random ();
        C[i] = random ();
	}

    map_allocate (1);

    // call the MAP routine
    subr (A, B, C, D, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<num; i++) {
	int64_t vx, vy, res;
        fprintf (res_map, "%lld\n", D[i]);

        vx = C[i] * (A[i]>B[i] ? A[i]-B[i] : A[i]+B[i]);
        vy = vx + A[i];
        vy = vy / 42;
        res = vy + C[i];

        fprintf (res_cpu, "%lld\n", res);
	}

    map_free (1);

    exit(0);
}
