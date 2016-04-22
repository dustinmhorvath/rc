#include <libmap.h>

void subr (int64_t input_data[], int64_t output_data[], int num,
	   int64_t *dt1, int64_t *dt2, int64_t *dt3, int64_t *dt4, 
	   int64_t *dt5, int64_t *dt6, int64_t *dt7, int mapnum) {

	Stream_64 SA,SB;
	
	int64_t t0, t1, t2, t3, t4, t5, t6, t7;
	
	read_timer (&t0);

	#pragma src parallel sections
	{
		#pragma src section
		{
			read_timer (&t1);
			streamed_dma_cpu_64 (&SA, PORT_TO_STREAM, input_data, num*sizeof(int64_t));
			read_timer (&t2);
		}
		#pragma src section
		{
			int i;
			int64_t dma_packet;

			read_timer (&t3);
			for (i=0; i<num; i++) {
				get_stream_64 (&SA, &dma_packet);
				put_stream_64 (&SB, ~dma_packet, 1);
			}
			read_timer (&t4);
		}
		#pragma src section
		{
			read_timer (&t5);
			streamed_dma_cpu_64 (&SB, STREAM_TO_PORT, output_data, num*sizeof(int64_t));
			read_timer (&t6);
		}
	}

	read_timer (&t7);

	*dt1   = t1 - t0;
	*dt2   = t2 - t0;
	*dt3   = t3 - t0;
	*dt4   = t4 - t0;
	*dt5   = t5 - t0;
	*dt6   = t6 - t0;
	*dt7   = t7 - t0;
}
