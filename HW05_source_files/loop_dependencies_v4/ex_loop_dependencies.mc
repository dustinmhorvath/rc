#include <libmap.h>

void subr (int64_t I0[], int64_t Out[], int num, int64_t *nvals, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)

    int64_t t0, t1, v;
    int i, idx = 0;

    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), I0, 1, num*8);

    read_timer (&t0);

    for (i=0; i<num; i++)
	    //if (AL[i] < 128)
		//BL[idx++] = AL[i];

        // All those conditions can be packed inside the cg_accum function
        cg_accum_add_64 (AL[i], AL[i]<128, 0, i==0, &BL[idx++]);

    *nvals = idx;

    read_timer (&t1);

    buffered_dma_cpu (OBM2CM, PATH_0, BL, MAP_OBM_stripe (1,"B"), Out, 1, idx*8);
    
    *time = t1 - t0;
}
