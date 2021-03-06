#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *r;
int rSize;
int fSize;
int offset;

void readFile(char *inName);
void writeFile(char *outName);
void xorBuffer();

int main(int argc, char** argv)
{

  if( argc < 3 )
  {
    printf("Usage: %s <infile> <outfile>\n", argv[0]);
    exit(1);
  }

  readFile(argv[1]); 
  xorBuffer();
  writeFile(argv[2]);

  free(r);

  printf("%i bytes written from %s to %s starting at offset %i\n", 
      fSize, 
      argv[1], 
      argv[2],
      offset );

  return 0;

}

void xorBuffer()
{
  int i = 0;
  for( i; i < rSize; i++ )
  {
    r[i]=(r[i]^1);
  }
}

void readFile(char *inName)
{
  FILE *in;

  //Open file
  in = fopen(inName, "rb");
  if (!in)
  {
    fprintf(stderr, "Unable to open file %s", inName);
    return;
  }
   //Get file length
  fseek(in, 0, SEEK_END);
  fSize=ftell(in);
  fseek(in, 0, SEEK_SET);

  //Allocate memory
  rSize = fSize + 1;
  r=(unsigned char *)malloc(rSize);
  if (!r)
  {
    fprintf(stderr, "Memory error!");
      fclose(in);
    return;
  }


  //Read file contents into buffer
  fread(r, fSize, 1, in);
  
  fclose(in);

  
}

void writeFile(char* outName)
{
  FILE *out = fopen( outName, "ab" );
  
  if (!out)
  {
    fprintf(stderr, "Unable to open file %s", outName);
  }

  fseek(out, 0, SEEK_END);
  offset=ftell(out);
  fseek(out, 0, SEEK_SET);
    
  fwrite(r, 1, fSize, out);

  fclose(out);

}
