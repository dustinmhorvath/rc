#include <libmap.h>

#define REF(_A,_i,_j) (_A[(_i)*n_cols+(_j)])

void subr (uint8_t input_image[], uint8_t output_image[], uint n_rows, uint n_cols, uint n_bytes, int64_t *time, uint mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)

    int64_t t0, t1;
    int i,j;

    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), input_image, 1, n_bytes);

    read_timer (&t0);

    /*** Insert Your Code Here ***/



    /*****************************/
    
    *time = t1 - t0;

    buffered_dma_cpu (OBM2CM, PATH_0, BL, MAP_OBM_stripe (1,"B"), output_image, 1, n_bytes);
}
