#include <libmap.h>

void read_image (char *filename);
void write_image (int *X, char *name);
void cpu_compute (char *name);
void subr ();

#define REF(_A,_i,_j) ((_A)[(_i)*n_cols+(_j)])

int n_cols, n_rows, n_bytes;
int *A=NULL, *B=NULL;
int nmaps = 1;
int status;

int **image;

void subr(int*, int*, int, int, int, int64_t*, int);
//void subr (uint8_t input_image[], uint8_t output_image[], uint n_rows, uint n_cols, uint n_bytes, int64_t *time,  uint mapnum);


int main (int argc, char *argv[]) {
    int i = 0;
    int j = 0;
    int64_t* time;

    if (argc < 2) {
        fprintf (stderr, "need image file source as arg\n");
        exit (1);
    }

    /*** Insert Your Code Here ***/

    read_image( argv[1] );

    int64_t *a;
    A = (int*) Cache_Aligned_Allocate(n_bytes * sizeof(int));
    B = (int*) Cache_Aligned_Allocate(n_bytes * sizeof(int));

    // Move image from 2d array into 1d int array (easier to pass to map)
    int index = 0;
    for(i = 0; i < n_rows; i++){
        for(j = 0; j < n_cols; j++){
            A[index] = image[i][j];
            index++;
        }
    }

    // prints 289722, which is n_cols*n_rows, and all the values of A, which shows it storing correctly
    /*
       int count = 0;
       for(i = 0; i < n_bytes; i++){
       count++;
       printf("%d\n ", A[i]);
       }
       printf("%d\n", count);
       */

    status = map_allocate(nmaps);
    if(status != 0  ){
        fprintf (stderr, "Could not allocate nmaps\n");
        exit(2);
    }


    int mapnum = nmaps - 1;

    printf("Calling map subroutine.\n");
    subr(A, B, n_rows, n_cols, n_bytes, &time, mapnum);
    printf("Completed map subroutine.\n");

    // Producing the wrong output for some reason. Lot of 0's.
    /*
    int count = 0;
    for(i = 0; i < n_bytes; i++){
        count++;
        printf("%d\n ", B[i]);
    }
    printf("%d\n", count);
    */


    // Move from 1d array (B) back to 2d array so it can be printed to file
    index = 0;
    for(i = 0; i < n_rows; i++){
        for(j = 0; j < n_cols; j++){
            image[i][j] = B[index];
            index++;
        }
    }

    map_free(nmaps);

    /*****************************/

    //printf ("%lld clocks\n", &time);
    printf ("ll%d clocks\n", time);

    write_image( 0, "output.pgm" );

    exit (0);
}

void read_image (char *filename) {
    FILE *fp;
    char str[1024];
    int mx;
    int i = 0;
    int j = 0;
    int tempint;

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
    n_bytes = n_rows * n_cols;

    image = malloc(sizeof (int *) * n_rows);
    for (i = 0; i < n_rows; i++){
        image[i] = malloc(sizeof(int) * n_cols);
    }


    printf("Storing image data in pointer array.\n");
    for(i = 0; i < n_rows; i++){
        for(j = 0; j < n_cols; j++){
            fscanf (fp, "%d", &tempint);
            image[i][j] = tempint;
        }

    }

    /*****************************/

}

void cpu_compute (char *name) {

    /*** Insert Your Code Here ***/



    /*****************************/
}

void write_image (int *X, char *name) {
    FILE *fp;
    int v0;
    int i, j;

    if ((fp = fopen (name, "w")) == NULL) {
        fprintf (stderr, "couldn't open file '%s'\n", name);
        exit (1);
    }
    fprintf (fp, "P2\n");
    fprintf (fp, "%d %d\n", n_cols, n_rows);
    fprintf (fp, "255\n");

    /*** Insert Your Code Here ***/

    for(i = 0; i < n_rows; i++){
        for(j = 0; j < n_cols; j++){
            fprintf (fp, "%d ", image[i][j]);
        }
        fprintf (fp, "\n");

    }



    /*****************************/
}
