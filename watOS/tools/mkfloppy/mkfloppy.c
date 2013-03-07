
#include "floppy.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE * outputFile, * inputFile;
	disk_144 * outputDisk;
	char * bootSectorCode;

	outputDisk = malloc(sizeof(disk_144));

	bootSectorCode = malloc(446); /* maximum size */
	memset(bootSectorCode, 0, 446); /* clear it out */
	memset(outputDisk, 0, sizeof(disk_144));

	inputFile = fopen(argv[1], "r");
	outputFile = fopen("floppy.img", "w");

	fread(bootSectorCode, 1, 446, inputFile);

	write144BootSector(outputDisk, bootSectorCode);
	
	fwrite(outputDisk, sizeof(disk_144), 1, outputFile);

	return 0;
}

void write144BootSector(disk_144 * outputDisk, char * bscode)
{
	bootsect * floppyBS;
	floppyBS = malloc(sizeof(bootsect));
	memset(floppyBS, 0, sizeof(bootsect));
	INITBOOTSECT(floppyBS);
	INITBASIC144(floppyBS);
	memcpy(floppyBS->code, bscode, 446);
	memcpy(outputDisk->BS, floppyBS, sizeof(bootsect));
	free(floppyBS);
}

void writeFileToDisk(disk_144 * outputDisk, FILE * fileToWrite)
{
	int cluster, firstCluster;

	/* find first empty FAT entry */
	clust = findNextFreeCluster(2, outputDisk);

	/* write next 512 byte block of file to that sector */
	/* add to dictionary if first block */
	/* rinse and repeat until done */
}

int findNextFreeCluster(int current, disk_144 * outputDisk)
{
	
}
