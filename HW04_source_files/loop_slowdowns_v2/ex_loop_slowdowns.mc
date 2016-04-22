#include <libmap.h>

void subr (int64_t I0[], int64_t Out[], int num, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)

	Stream_64 SA,SB;
    int64_t t0, t1, t2, t3, t4, t5;
    int i;
    t2=0;
    t5=0;

    //buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), I0, 1, num*8);


    #pragma src parallel sections
	{
		#pragma src section
		{
			streamed_dma_cpu_64 (&SA, PORT_TO_STREAM, I0, num*8);
		}
		#pragma src section
		{
    read_timer (&t0);
			int i;
			int64_t dma_packet, temp;

			for (i=0; i<num; i++) {
				get_stream_64 (&SA, &dma_packet);
                temp = dma_packet + 9;
                AL[i] = temp;
				put_stream_64 (&SB, ~dma_packet, 1);
			}
    read_timer (&t1);
    t2 = t1-t0+t2;
		}
        #pragma src section
		{
    read_timer (&t3);
			int i;
			int64_t dma_packet, temp;

			for (i=0; i<num; i++) {
				get_stream_64 (&SB, &dma_packet);
                temp = dma_packet * 5;
                BL[i] = temp;
			}
		}
    read_timer (&t4);
    t5 = t4-t3+t5;

	}

    *time = t2+t5;

    buffered_dma_cpu (OBM2CM, PATH_0, AL, MAP_OBM_stripe (1,"A"), &Out[0], 1, num*8);
    buffered_dma_cpu (OBM2CM, PATH_0, BL, MAP_OBM_stripe (1,"B"), &Out[num], 1, num*8);

}
