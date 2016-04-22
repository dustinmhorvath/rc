#include <libmap.h>

void subr (int64_t I0[], int n0, int n1, int64_t *res, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)

    int64_t t0, t1, v, accum = 0;
    int i, j, sz;
    
    sz = n0 * n1;

    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe(1,"A"), I0, 1, sz*sizeof(int64_t));

    read_timer (&t0);

    for (i=0; i<n0; i++)
        for (j=0; j<n1; j++) {
	    	v = AL[i*n1+j];
    		//if (v < 128) accum = accum + v;

            // Only resets on both initial conditions
            cg_accum_add_64 (v, v<128, 0, i==0 & j==0, &accum);
        }

    *res = accum;

    read_timer (&t1);
    
    *time = t1 - t0;
}
