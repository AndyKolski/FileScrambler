#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	char buffer;
	long filelen;
	float perc = 1;
	int w = 0;
	if (argc >= 4) {
		perc = atof(argv[3]);
		printf("Using chance of %f%%\n", perc);
	}
	if (argc == 5) {
		w = atoi(argv[4]);
		printf("Using byte offset of %iB\n", w);
	}
	if (argc < 4) {
		printf("Usage: %s [Input File] [Output File] [Byte Change Chance %%] <Byte Offset>\n", argv[0]);
		return 1;
	}
	if ( access(argv[1], F_OK) == -1 ) {
			printf("Unable to open file \"%s\"\n", argv[1]);
			return 1;
	}
	FILE *sourcefile = fopen(argv[1], "rb");
	FILE *outfile = fopen(argv[2],"wb");       
	fseek(sourcefile, 0, SEEK_END);          
	filelen = ftell(sourcefile);            
	rewind(sourcefile);
	srand(time(NULL)); 

	for (long i = 0; i < filelen; i++) {
		buffer = 0;
		fread(&buffer, 1, 1, sourcefile); 
		if (i >= w && rand()/2147483647.0*100<perc) {
			buffer = rand()/2147483647.0*255-128;
		}
		if (i % (long)(0.05*filelen) == 0) {
			if (filelen > 1048576) {
				printf("Progress: %f%% (%dMB / %dMB)\n", 100.0*i/filelen, i/1024/1024, filelen/1024/1024);
			} else {
				printf("Progress: %f%% (%dB / %dB)\n", 100.0*i/filelen, i, filelen);
			}
		}
		fwrite(&buffer,1,1,outfile);
	}
	printf("Done!\n");
	fclose(outfile);
}