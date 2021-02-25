#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"

/* currently only suppports standard cartridges (like mario for example) */
void
read_header(FILE *rom, u32 *pout, u32 *cout)
{
	byte signature[4];

	byte correct_sig[] = {'N', 'E', 'S', 0x1a};
	for (int i = 0; i < 4; i++) {
		signature[i] = fgetc(rom);
		if (signature[i] != correct_sig[i]) {
			printf("invalid header!\n");
			exit(1);
		}
	}
	*pout = fgetc(rom) * 16384;
	*cout = fgetc(rom) * 8192;
	rewind(rom);
}

int
main(int argc, char *argv[])
{
	assert(argv[1] != NULL);
	FILE *cartridge = fopen(argv[1], "rb");
	u32 prog_size;
	u32 chr_size;
	read_header(cartridge, &prog_size, &chr_size);
	fseek(cartridge, 16, SEEK_CUR);

	FILE *prog_out = fopen("out.prog", "wb");
	for (u32 i = 0; i < prog_size; i++) {
		byte b = fgetc(cartridge);
		fputc(b, prog_out);
	}

	FILE *chr_out = fopen("out.chr", "wb");
	for (u32 i = 0; i < chr_size; i++) {
		byte b = fgetc(cartridge);
		fputc(b, chr_out);
	}

	fclose(chr_out);
	fclose(prog_out);
	fclose(cartridge);
}
