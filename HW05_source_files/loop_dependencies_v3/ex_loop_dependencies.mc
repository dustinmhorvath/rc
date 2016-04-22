#include <libmap.h>

void subr (int64_t I0[], int64_t Out[], int num, int64_t thr, int64_t *idx, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)

    int64_t t0, t1, v, accum = 0;
    int i;

    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), I0, 1, num*8);

    read_timer (&t0);

    for (i=0; (i<num) & (accum<thr); i++) {
        // np option means it doesn't need to preserve the accuracy of accum after the loop
	    cg_accum_add_64_np (AL[i], AL[i]<128, 0, i==0, &accum);
	    BL[i] = accum;
    }

    *idx = i;

    read_timer (&t1);

    buffered_dma_cpu (OBM2CM, PATH_0, BL, MAP_OBM_stripe (1,"B"), Out, 1, *idx*8);

    *time = t1 - t0;
}
