/*****************************************************************************
* Emily Dunham 
* 10/23/2012
* CS311 Project 3
*  
* Resources: 
* http://stackoverflow.com/questions/3554120/open-directory-using-c for app_all
* http://www.cprogramming.com/tutorial/cfileio.html for append
* http://cboard.cprogramming.com/c-programming/104274-detecting-empty-file-situation.html for append
*****************************************************************************/

#include <stdio.h>
#include <dirent.h>
#include <ar.h>
#define  ARMAG   "!<arch>\n"	 /* magic string */
#define  SARMAG   8		 /* length of magic string */

#define  ARFMAG   "`\n"	 /* header trailer string */

 struct  ar_hdr 		 /* file member header */
 {
     char    ar_name[16];	 /* '/' terminated file member name */
     char    ar_date[12];	 /* file member date */
     char    ar_uid[6]		 /* file member user identification */
     char    ar_gid[6]		 /* file member group identification */
     char    ar_mode[8] 	 /* file member mode (octal) */
     char    ar_size[10];	 /* file member size */
     char    ar_fmag[2];	 /* header trailer string */
 };

void  usage(){
    printf("Myar.c, written by Emily Dunham, October 2012\n");
    printf("Usage: $ myar -key afile name\n");
    printf("\t-q Quickly append name to archive afile\n");
    printf("\t-x Extract first file matching name from archive afile, without deleting it from afile\n");
    printf("\t-t Concise table of contents for afile (name arg gets ignored)\n");
    printf("\t-v Verbose table of contents (like -t)\n");
    printf("\t-d Delete name from archive afile\n");
    printf("\t-A Append all regular files in current directory to afile (name arg is ignored)\n");
    printf("\t-w Add all modified files (not currently implemented)\n");
}

int create(char* ark){
/*    int ar = open(ark, O_WRONLY | O_CREAT, S_IRWXU);
    if(ar == -1){
        perror("can't open archive file");
        exit(-1);
    }
    int wrote = write(ar, (void*)ARMAG, SARMAG * sizeof(ARMAG[0]));
    wrote = write(ar, (void*)ARFMAG + wrote, 3 * sizeof(ARFMAG[0]));
    if(close(ar) == -1){
        perror("archive failed to close");
        exit(-1);
    }
*/
    return 1;
}

int append(char *ark, char *file){
    printf("quick append %s to %s \n", file, ark);
/*    FILE ar = fopen(ark, "r");
    if(ar == -1){
        perror("Couldn't even open archive file to read it");
        exit(-1);
    }
    if(ar == 0){
        create(ark);
    }
    fclose(ar);
    int wr = open(ark, O_WRONLY);
    if(fseek(wr, 11, SEEK_CUR) != 0){
        perror("fseek broke");
        exit(-1);
    }
*/
    /*okay, i admit it, i have no idea what i'm doing */
     

    return 0;
}
int app_all(char *ark){
/*    struct dirent *dent;
    DIR *dr;
    dr = opendir(".");
    if(dr == NULL){
        printf("Myar Failed: Could not open current directory.\n");
        return -1;
    }
    while((dent = readdir(dr)) != NULL){
        if((dent -> d_name != ark) && (opendir(dent -> d_name) == NULL)){
           append(ark, dent->d_name);
        }
    }

*/
    return 0;
}
int xtract(char *ark, char *file){
    printf("extract %s from %s \n", file, ark);
    
    return 0;
}
int print(char *ark, int v){
    return 0;
}
int rm(char *ark, char *file){

    return 0;
}

int main (int argc, char **argv){
    if(argc < 2){
        usage();
        return 0;
    }
    switch(argv[1][1]){
        case 'q':
            append(argv[2], argv[3]);
            break;
        case 'x':
            xtract(argv[2], argv[3]);
            break;
        case 't':
            print(argv[2], 0);
            break;
        case 'v':
            print(argv[2], 1);
            break;
        case 'd':
            rm(argv[2], argv[3]);
            break;
        case 'A':
            app_all(argv[2]);
            break;        
        case 'w':
            printf("-w feature is not currently implemented. \n");
        default:
            usage();
    }
   return 0;
}


