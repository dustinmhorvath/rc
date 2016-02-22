#include <libmap.h>

void read_image (char *filename);
void write_image (uint8_t *X, char *name);
void cpu_compute (char *name);
void subr ();

#define REF(_A,_i,_j) ((_A)[(_i)*n_cols+(_j)])

uint n_cols, n_rows, n_bytes;
uint8_t *A=NULL, *B=NULL;

int main (int argc, char *argv[]) {
    int64_t time;

    if (argc < 2) {
        fprintf (stderr, "need image file source as arg\n");
		exit (1);
	}

	/*** Insert Your Code Here ***/



	/*****************************/

	printf ("%lld clocks\n", time);

    exit (0);
}

void read_image (char *filename) {
    FILE *fp;
    char str[1024];
    int mx;

    if ((fp = fopen (filename, "r")) == NULL) {
        fprintf (stderr, "couldn't open image file\n");
        exit (1);
    }
    fscanf (fp, "%s", str);
    if (strcmp ("P2", str) != 0) {
        fprintf (stderr, "image format error; must be a 'P2' pgm file\n");
        exit (1);
    }
    fscanf (fp, "%d %d", &n_cols, &n_rows);
    fscanf (fp, "%d", &mx);
    printf ("image size is %dx%d\n", n_rows, n_cols);

	/*** Insert Your Code Here ***/



	/*****************************/

}

void cpu_compute (char *name) {

	/*** Insert Your Code Here ***/



	/*****************************/
}

void write_image (uint8_t *X, char *name) {
    FILE *fp;
    uint8_t v0;
    int i, j;

    if ((fp = fopen (name, "w")) == NULL) {
        fprintf (stderr, "couldn't open file '%s'\n", name);
        exit (1);
    }
    fprintf (fp, "P2\n");
    fprintf (fp, "%d %d\n", n_cols, n_rows);
    fprintf (fp, "255\n");

	/*** Insert Your Code Here ***/



	/*****************************/
}
