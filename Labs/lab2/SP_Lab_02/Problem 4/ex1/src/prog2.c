/*
**	function takes three parameters one char on which we 
**	want to test its bits are set 2nd and third are integer 
**	parametersn give the range of bits we want to check
**	function returns integer value, 1 if set otherwise 0. 
*/
int isBitSetInRange(unsigned char ch, int low, int hi){

	unsigned char ch1 = ch;
	unsigned char result;
	for(int i = low; i<= hi; i++)
	{
		unsigned char mask = 1<<i;
		 result = ch & mask;
		if(result != 0)
		{
			break;
		}
	}
	if(result == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
