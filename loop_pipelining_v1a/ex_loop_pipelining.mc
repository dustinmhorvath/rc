#include <libmap.h>

void subr (int64_t X[], int64_t Y[], int64_t Z[], int64_t Q[], int num, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_C (CL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_D (DL, int64_t, MAX_OBM_SIZE)
    
    int64_t t0, t1;
    int i;

    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), X, 1, num*8);
    buffered_dma_cpu (CM2OBM, PATH_0, BL, MAP_OBM_stripe (1,"B"), Y, 1, num*8);
    buffered_dma_cpu (CM2OBM, PATH_0, CL, MAP_OBM_stripe (1,"C"), Z, 1, num*8);

    read_timer (&t0);

    for (i=0; i<num; i++) {
	DL[i] = CL[i] * (AL[i]>BL[i] ? AL[i]-BL[i] : AL[i]+BL[i]);
	}

    read_timer (&t1);

    *time = t1 - t0;

    buffered_dma_cpu (OBM2CM, PATH_0, DL, MAP_OBM_stripe (1,"D"), Q, 1, num*8);
}
