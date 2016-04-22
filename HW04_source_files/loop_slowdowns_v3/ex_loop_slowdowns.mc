#include <libmap.h>

void subr (int64_t I0[], int64_t Out[], int num, int64_t *time, int mapnum) {
    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_C (CL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_D (DL, int64_t, MAX_OBM_SIZE)
    
    int64_t t0, t1;
    int i;
	Stream_64 SA,SB,SC,SD;
    int n = 0;
    int64_t a, b, c;


	buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1, "A"), I0, 1, (num-2)*8);
	buffered_dma_cpu (CM2OBM, PATH_0, BL, MAP_OBM_stripe (1, "B"), &I0[1], 1, (num-2)*8);
	buffered_dma_cpu (CM2OBM, PATH_0, CL, MAP_OBM_stripe (1, "C"), &I0[2], 1, (num-2)*8);

    read_timer (&t0);
    
    //#pragma src parallel sections
	//{
	//	#pragma src section
	//	{
	//		streamed_dma_cpu_64 (&SA, PORT_TO_STREAM, &I0[2], (num-2)*8);
	//	}
    //
	//}

    for(i = 0; i < num-2; i++){
        DL[i] = AL[i] + BL[i] + CL[i];
    }

    read_timer (&t1);
    *time = t1 - t0;
	
    buffered_dma_cpu (OBM2CM, PATH_0, DL, MAP_OBM_stripe (1, "D"), Out, 1, (num-2)*8);
}
