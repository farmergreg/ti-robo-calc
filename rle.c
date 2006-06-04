#define RunMarker 0x91
	
unsigned long rle_decode(register unsigned char *out, register unsigned char *in, register unsigned long len)
{
	register unsigned long PosIn=0;
	register unsigned long PosOut=0;
	register unsigned char byte;
	//register unsigned char freq;
	register short freq;
	register unsigned char i;
	
	while(PosIn<len)
	{
		if(in[PosIn]==RunMarker)
		{
			PosIn++;
			byte=in[PosIn++];
			freq=(unsigned char)(in[PosIn++]-1);	//make a zero into 255 for the loop
			
			if(out)
			{
				freq++;
				for(i=0;i<freq;i++)
					out[PosOut++]=byte;
					
				//out[PosOut++]=byte;	//write the last byte
			}
			else
			{
				PosOut+=freq+1;
			}
		}
		else
		{
			if(out)
				out[PosOut++]=in[PosIn++];
			else
			{
				PosOut++;
				PosIn++;
			}
		}
	}
	
	return PosOut;
}
