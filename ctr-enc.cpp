#include "util.h"
#include <cstdio>
#include <cstdlib>

void *encrypt(u_char *data, u_char *iv, int start, int end, int *tnum)
{
	int *i;

	i=(int*) tnum;
	printf("Thread %d\n", *i);
	return NULL;
}

int main(int argc, char ** argv)
{
	SSL_load_error_strings();
	int k, i, in, o, v, tmp;
	FILE *input, *output, *kf, *iv;

	//command line args
	k = -1, in = -1, o = -1, v = -1;
	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-k") == 0)
			k = i+1;
		else if(strcmp(argv[i], "-i") == 0)
			in = i+1;
		else if(strcmp(argv[i], "-o") == 0)
			o = i+1;
		else if(strcmp(argv[i], "-v") == 0)
			v = i+1;
		else if(argv[i][0] == '-')
			fprintf(stderr, "%s flag not recognized.\n", argv[i]);
	}
	if(k == -1 || in == -1 || o == -1){
		fprintf(stderr, "must specify a key, an input file, and an output file.\n");
		return 1;
	}

	//open files
	kf = fopen(argv[k],"rb");
	input = fopen(argv[in],"rb");
	output = fopen(argv[o],"wb");
	if(kf == NULL || input == NULL || output == NULL){
		fprintf(stderr, "Unable to open the specified files.\n");
		return 1;
	}
	if(v != -1){
		iv = fopen(argv[v],"rb");
	}
	if(iv == NULL){
		fprintf(stderr, "Unable to open the specified files.\n");
		return 1;
	}
	
	//get file size
	int filesize;
	fseek(input, 0, SEEK_END);
	filesize = ftell(input);
	rewind(input);

	printf("filesize = %d\n", filesize);
	
	//malloc and read file into buffer.
	u_char *fbuffer, *obuffer;
	fbuffer = (u_char*)malloc(sizeof(u_char) * (filesize));
	obuffer = (u_char*)malloc(sizeof(u_char) * (filesize+16));
	if(fbuffer == NULL)
		printf("memory error\n");
	fread(fbuffer, 1, filesize, input);
	printf("FILE:\n%s\n",fbuffer);

	rewind(input);

	//encryption
	time_t t;
	srand((unsigned) time(&t));
	u_char key[16];
	u_char prev[16];
	u_char buf[17];
	u_char buf2[17];
	


	for(i = 0; i < 16; i++){
		prev[i] = (u_char) rand();
	}
	
	if(fread(&key,1,16,kf) != 16)
		fprintf(stderr,"Not enought bytes read for the key.\n");
	if(v != -1 && iv !=NULL){
		if(fread(&prev,1,16,iv) != 16)
			fprintf(stderr,"Not enought bytes read for the key.\n");
	}		
	//printf("%s\n",prev);
	fwrite(prev,1,16,output);
	
	for(i=0; i<4; i


	tmp = fread(&buf,1,16,input); 
	unsigned int *convert;
	convert = (unsigned int*)&prev[12];	
	while(tmp == 16){
		xor_128(buf,prev);
		encode_128(key, buf, buf2);
		*convert++;
		buf2[16] = '\0';
		//printf("%s\n",buf2);
		fwrite(buf2,1,16,output);
		tmp = fread(&buf,1,16,input); 
	}
	for(i = tmp; i < 16; i++){
		buf[i] = (u_char) (16 - tmp);
	}
	xor_128(buf,prev);
	encode_128(key, buf, buf2);
	buf2[16] = '\0';
	//printf("%s\n",buf2);
	
	fwrite(buf2,1,16,output);





	printf("File written.\n");
	fclose(kf);
	fclose(input);
	fclose(output);
	return 0;
}
