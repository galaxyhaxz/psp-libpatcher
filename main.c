#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *LoadBinaryFile(char *file, int *filesize)
{
	unsigned char *p;
	FILE *fp;
	int bufsize;

	fp = fopen(file, "rb");

	if(fp == NULL) {
		fprintf(stderr, "Can't open file %s\n", file);
		exit(-1);
	}

	fseek(fp, 0L, SEEK_END);
	bufsize = ftell(fp);
	p = (unsigned char *)malloc(sizeof(unsigned char) * (bufsize + 1));
	fseek(fp, 0L, SEEK_SET);
	fread(p, sizeof(char), bufsize, fp);
	fclose(fp);

	*filesize = bufsize;

	return p;
}

void WriteBinaryFile(char *file, unsigned char *buff, int size)
{
	FILE *fp;

	fp = fopen(file, "wb");

	if(fp == NULL) {
		fprintf(stderr, "Can't write file %s\n", file);
		exit(-1);
	}

	fwrite(buff, sizeof(char), size, fp);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	unsigned char *p;
	int offset, filesize;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s library.a\n", argv[0]);
		return 0;
	}

	p = LoadBinaryFile(argv[1], &filesize);

	offset = p[0x48] << 24 | p[0x49] << 16 | p[0x4A] << 8 | p[0x4B];

	if(p[offset] != 0x2F || p[offset + 1] != 0x30) {
		printf("'%s' is not a stub library\n", argv[1]);
		free(p);
		return 0;
	}

	if(p[offset+0x74] == 0x11) {
		printf("'%s' @ [0x%08X] patched!\n", argv[1], offset+0x74);
		p[offset+0x74] = 0;
		WriteBinaryFile(argv[1], p, filesize);
	} else {
		printf("'%s' is already patched\n", argv[1]);
	}

	free(p);

	return 0;
}
