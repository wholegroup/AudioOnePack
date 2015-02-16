#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <windows.h>
#include "../TTALib/TTAlib.h"
using namespace TTALib;

bool DrawStat (const TTAStat &stat, void *uParam)
{
	printf (".");
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argv[1][0] == 'd' && argc == 4)
	{
		printf ("Decompressing %s to %s\n", argv[2], argv[3]); 
		TTAError result = TTA2Wav(argv[2], argv[3],  false, DrawStat, NULL); 
		if (result > 0)
			printf ("\nError: %d %s\n", result, GetErrStr (result));
		else
			printf ("\nOK\n", result, GetErrStr (result));
		return result;
	}
	else if (argv[1][0] == 'e' && argc == 4)
	{
		printf ("Compressing %s to %s\n", argv[2], argv[3]); 
		TTAError result = Wav2TTA(argv[2], argv[3], false, DrawStat, NULL); 
		if (result > 0)
			printf ("\nError: %d %s\n", result, GetErrStr (result));
		else
			printf ("\nOK\n", result, GetErrStr (result));
		return result;
	}
	else if (argv[1][0] == 't' && argc == 3)
	{
		printf ("Test %s\n", argv[2]); 
		TTAError result = TTATest(argv[2], DrawStat, NULL); 
		if (result > 0)
			printf ("\nError: %d %s\n", result, GetErrStr (result));
		else
			printf ("\nOK\n", result, GetErrStr (result));
		return result;
	}

	return -1;
}

