#include <libmap.h>

#define REF(_A,_i,_j) (_A[(_i)*n_cols+(_j)])

void subr (uint input_image[], uint output_image[], int n_rows, int n_cols, int n_bytes, int64_t *time, uint mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)


    int64_t t0, t1;
    int i,j;

    //printf("%d\n", n_bytes);     //prints correct value
    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), input_image, 1, n_bytes*sizeof(int));
    

    read_timer (&t0);

    /*** Insert Your Code Here ***/
    

        
    for(i = 0; i < n_rows; i++){
        for(j = 0; j < n_cols; j++){
            BL[i+j] = (255 - AL[i+j]);
        //    printf("%d ", BL[i+j]);      // Values look good on print
        }
        //printf("\n");
    }
    


    /*****************************/
    
    *time = t1 - t0;

    buffered_dma_cpu (OBM2CM, PATH_0, BL, MAP_OBM_stripe (1,"B"), output_image, 1, n_bytes*sizeof(int));
}


