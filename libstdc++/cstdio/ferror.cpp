/* ferror example: writing error */
#include <stdio.h>
int main ()
{
  FILE * pFile;
  pFile=fopen("myfile.txt","r");
  if (pFile==NULL) perror ("Error opening file");
  else {
    fputc ('x',pFile);
    if (ferror (pFile))
      printf ("Error Writing to myfile.txt\n");
    fclose (pFile);
  }
  return 0;
}

/*
This program opens an existing file called myfile.txt in read-only mode but tries to write a character to it, generating an error that is detected by ferror.

Output:
Error Writing to myfile.txt
*/
