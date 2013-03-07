
#include "floppy.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE * outputFile, * inputFile;
	char * bootSectorCode;

	bootSectorCode = malloc(352); /* maximum size */	
	memset(bootSectorCode, 0, 352); /* clear it out */

	inputFile = fopen(argv[1], "r");
	outputFile = fopen("floppy.img", "w");

	fread(bootSectorCode, 1, 352, inputFile);

	write144BootSector(outputFile, bootSectorCode);
	write144Padding(outputFile);

	return 0;
}

void write144BootSector(FILE * outputFile, char * bscode)
{
	bootsect * floppyBS;
	floppyBS = malloc(sizeof(bootsect));
	memset(floppyBS, 0, sizeof(bootsect));
	INITBOOTSECT(floppyBS);
	INITBASIC144(floppyBS);
	memcpy(floppyBS->code, bscode, 352);
	fwrite(floppyBS, sizeof(bootsect), 1, outputFile);
}

void write144Padding(FILE * outputFile)
{
	int i;

	for(i = 0; i < 512 * 2879; i++)
	{
		fputc(0, outputFile);
	}
}
