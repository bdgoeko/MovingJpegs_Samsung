#include <stdio.h>
#include <string.h>
#include <errno.h>

// Copyright (C) 2023, Brian Dolan-Goecke 20230205 

/* Simple program to replace characters that may not be good for the shell
 * Do I want to quote it ? 
 */

const unsigned char MotionPhoto_Data_Marker[] = {
  0x4D, 0x6F, 0x74, 0x69, 0x6F, 0x6E, 0x50, 0x68,
  0x6F, 0x74, 0x6F, 0x5F, 0x44, 0x61, 0x74, 0x61 };

int 
iffile( char *filename ){
  // see if a file exists cheap and dirty say try and open it...
  FILE *tmp_file;

  if ( strlen( filename) <= 0 ) {
    //fprintf( stderr, "Error bad filename \"%s\"", filename);
    return 300;
  }
  if (( tmp_file = fopen( filename, "r" )) == NULL)  {
    //fprint( stderr, "");
    //perror( "Error opening file \"%s\"", filename);
    return errno;
  }
  // if we were able open the file, close it 
  fclose( tmp_file );
  return 0;
} 

int 
main (int argc, char *argv[])
{
  int thechar;
  char lastnl=0;
  char *photofilename="output.jpg";
  char *moviefilename="output.mp4";
  short match_count=0;
  FILE *thefile;
  FILE *jpg_file;
  FILE *mp4_file;
  FILE *outfile;
  int tmp_cnt=0;
  int filerr=0;
  
  //char filename[1024];

  if (argc != 2) {
    printf ("USAGE: %s {filename} %d\n", argv[0], argc);
    return 1;
  }

  // see if we have a string
  if ( strlen( argv[1] ) == 0 ) {
    printf( "Bad file name '%s'\n", argv[1]);
    return 3;
  }

  //printf( "Errno: %d\n", errno);
  printf( "Opening file %s\n", argv[1]);
  thefile = fopen( argv[1], "r");
  if ( thefile == NULL ) {
    perror( "fopen error");
    printf("Error opening file %s", argv[1]);
    printf( "Errno: %d\n", errno);
    return 4;
  }
  rewind( thefile);
  //printf( "Errno: %d\n", errno);

  // if I was a good programmer (person) I would check to make sure these files don't exists first...
  // see if file exits
  if( (filerr = iffile( photofilename)) == 0 ) {
    //fprintf( stderr, "Error '%d\' file \"%s\" exists ?  ", filerr, photofilename);
    fprintf( stderr, "Error file \"%s\" exists.\n", photofilename);
    return filerr;
  }

  // see if file exits
  if( (filerr = iffile( moviefilename)) == 0 ) {
    //fprintf( stderr, "Error '%d\' file \"%s\" exists ?  ", filerr, moviefilename);
    fprintf( stderr, "Error file \"%s\" exists.\n", moviefilename);
    return filerr;
  }

  jpg_file = fopen( photofilename, "w" );
  mp4_file = fopen( moviefilename, "w" );

  //outfile = mp4_file;
  outfile = jpg_file;
  printf( "Outputing to \"%s\"\n", photofilename);

  thechar= fgetc( thefile);
  //printf( "char: %d\n",thechar);
  //printf( "Errno: %d\n", errno);
  //while( (thechar = fgetc( thefile )) != EOF) {
  while ( thechar != EOF ) {
    //printf( "char: %d\n",thechar);
    if ( thechar == MotionPhoto_Data_Marker[match_count] ) {
      //printf("MotionPhoto_Data_Marker Match %d\n", match_count);
      // if complete match we are done
      if ( match_count == 15 ) {
        // we are done complete match
        // close jpg file
        fclose( jpg_file);
        // output the mp4 file
        outfile = mp4_file;
        printf( "Outputing to \"%s\"\n", moviefilename);
        // output rest of file to output.mp4
        while( thechar != EOF) {
          thechar = fgetc( thefile);
          //putchar();
          fputc( thechar, outfile);
          //printf( ".");
        }
        return(0); // exit done
      } else { // match_count == 15
        match_count++;
      } // match_count == 15
    } else { // thechar == MationPhotot_data_makrer[match_count]

      // see if we were in some part of the match, the print catch up
      if ( match_count != 0 ) {
        // have to do catch up on output
        tmp_cnt = 0;
        //for ( tmp_cnt = 0 ; tmp_cnt++; tmp_cnt < match_count ) {
        while ( tmp_cnt < match_count) {
          // printf( "%c", MotionPhoto_Data_Marker[tmp_cnt] )
          //putchar(thechar);
          fputc( MotionPhoto_Data_Marker[tmp_cnt++] , outfile);
          //printf( "+");
        }
        //fputc( thechar, outfile);
        //printf( "-");
        match_count=0; // reset match_count
      }
      fputc( thechar, outfile);
      //printf( ".");
      //printf( "%c", thechar );
    } // thechar == MationPhotot_data_makrer[match_count]
    thechar= fgetc( thefile);
  } // while wend

  printf( "Run Complete\n");
  return(0);
}

//    char *infile;
//    int fileSize;
//    int fd;
//    int i;
//    int j;
//    int temp;
//    int sum = 0;
//    int average;
//    /* enforce proper number of arguments
//    */
//    //open file
//    fd = open(infile, O_RDONLY);
//    fd = open(infile, O_RDONLY);

    //exit if open fails
//    assert (fd > -1);

    //add all integers into the array up
//    for (j = 0; j < fileSize; j++);
//     {
//            sum = sum + intArray[j];
//     }

//    if ( close(fd) == -1 )
//     {
//             fprintf(stderr, "error closing file -- quitting");
//             exit(1);
//     }

//return 0;
