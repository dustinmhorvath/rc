#include <libmap.h>
#include <stdlib.h>

#define MAX_OBM_SIZE 1048576

void subr (int64_t input_data[], int64_t output_data[], int num,
	       int64_t *dt1, int64_t *dt2, int64_t *dt3, int64_t *dt4,
	       int64_t *dt5, int64_t *dt6, int64_t *dt7, int mapnum);

int main (int argc, char *argv[]) {
	FILE *res_map, *res_cpu;
	int i, num;
	int64_t *A, *B;
	int64_t dt1, dt2, dt3, dt4, dt5, dt6, dt7;
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
	B = (int64_t*) Cache_Aligned_Allocate (num * sizeof (int64_t));

	srandom (99);
	for (i=0; i<num; i++) {
		A[i] = random ();
	}

	map_allocate (1);

	subr (A, B, num, &dt1, &dt2, &dt3, &dt4, &dt5, &dt6, &dt7, mapnum);

	printf ("   \n");

	printf ("   Start of Input (CPU-to-MAP)  Stamp:	%8lld clocks\n", dt1);
	printf ("   End   of Input (CPU-to-MAP)  Stamp:	%8lld clocks\n\n", dt2);

	printf ("   Start of Compute             Stamp:	%8lld clocks\n", dt3);
	printf ("   End   of Compute             Stamp:	%8lld clocks\n\n", dt4);

	printf ("   Start of Output (MAP-to-CPU) Stamp:	%8lld clocks\n", dt5);
	printf ("   End   of Output (MAP-to-CPU) Stamp:	%8lld clocks\n\n", dt6);

	printf ("   End                          Stamp:	%8lld clocks\n\n", dt7);

	printf ("   Input (CPU-to-MAP)            Time:	%8lld clocks\n", dt2-dt1);
	printf ("   Compute                       Time:	%8lld clocks\n", dt4-dt3);
	printf ("   Output (MAP-to-CPU)           Time:	%8lld clocks\n", dt6-dt5);
	printf ("   Total                         Time:	%8lld clocks\n\n", dt7);

	for (i=0; i<num; i++) {
		fprintf (res_map, "%lld\n", B[i]);
		fprintf (res_cpu, "%lld\n", ~A[i]);
	}

	map_free (1);

	exit(0);
}
