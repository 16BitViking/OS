
typedef struct __attribute__((packed))
{
	char initialJump[3];
	char OEMName[8];

	struct BPB
	{
		short bytesPerSector;
		char sectorsPerCluster;
		short reservedSectorCount;
		char FATnum;
		short rootDirEntries;
		short totalSectors;
		char MDB; /* media descriptor byte */
		short sectorsPerFAT;
		short sectorsPerTrack;
		short heads;
		char nothing [10];
		char extendedBPB;
		char serialNum [4];
		char volumeLabel [11];
		char FSID [8];
	} __attribute__((packed)) BIOSParameterBlock;

	char code[446];
	char padding[2]; /* two null bytes */
	short magicNumber; /* 0xAA55. Always. */

} bootsect;

typedef struct __attribute__((packed))
{
	char entries[512 * 9]; /* 9 sectors, 512b each */	
} FAT;

typedef struct __attribute__((packed))
{
	char filename[11]; /* 8.3 filenames */
	char attributes;
	char reserved;
	char fctime;
	short createdTime;
	short createdDate;
	short accessDate;
	short highFirst; /* unused in FAT12 */
	short modTime;
	short modDate;
	short lowFirst;
	int fileSize; /* 0 for directories */

} RDEntry; 

typedef struct __attribute__((packed))
{
	RDEntry entries[224]; /* 224 = max entries */
} RootDirectory;

typedef struct __attribute__((packed))
{
	bootsect BS; /* sector 0 */
	FAT fat1; /* sectors 1-9 */
	FAT fat2; /* sectors 10-18 */
	RootDirectory RD; /* sectors 19-32 */
	char space[512 * 2847]; /* sectors 33 - 2879 */
	
} disk_144;

#define INITBOOTSECT(a) \
{ \
	a->initialJump[0] = 0xEB; \
	a->initialJump[1] = 0x3C; \
	a->initialJump[2] = 0x90; \
	a->magicNumber = 0xAA55;\
}

#define INITBASIC144(a) \
{ \
	a->BIOSParameterBlock.bytesPerSector = 512; \
	a->BIOSParameterBlock.sectorsPerCluster = 1; \
	a->BIOSParameterBlock.reservedSectorCount = 1; /* start of diskette is reserved */ \
	a->BIOSParameterBlock.FATnum = 2; \
	a->BIOSParameterBlock.rootDirEntries = 224;\
	a->BIOSParameterBlock.totalSectors = 2880;\
	a->BIOSParameterBlock.MDB = 0xF0 /* 1.44MB Floppy */ ;\
	a->BIOSParameterBlock.sectorsPerFAT = 9;\
	a->BIOSParameterBlock.sectorsPerTrack = 18;\
	a->BIOSParameterBlock.heads = 2;\
	strcpy(&(a->BIOSParameterBlock.FSID), "FAT12   "); \
}

#define CLUSTER_TO_OFFSET(c) \
{ \
 (c - 2) >> 1 * 3 + (c & 1);\
}
