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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ar.h>
#define HEADER_BYTES 60 // Size of struct ar_hdr

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
    // ssize_t read(int fd, void *buf, size_t count);
    int fd = open(ark, O_RDONLY);
    if (fd < 0){
        perror("Couldn't open archive file");
        exit(-1);
    }
    char armag_buf[SARMAG];
    int numRead = read(fd, armag_buf, SARMAG);
    while (numRead < SARMAG){
        printf("didn't read enough; continuing to try\n");
        numRead += read(fd, armag_buf + numRead, SARMAG - numRead); 
        if (numRead == -1)
            perror("read failed");
            exit(-1);
    }
    char name[16];
    char date[12];
    char uid[6];
    char gid[6];
    char mode[8];
    char size[10];
    char fmag[2];

    while (1){
        if (read(fd, name, 16) == -1 || read(fd, date, 12) == -1 ||
            read(fd, uid, 6) == -1 || read(fd, gid, 6) == -1 || read(fd, mode, 8) == -1 ||
            read(fd, size, 10) == -1 || read(fd, fmag, 2) == -1)
            return 1; 
        if (!v){
            printf("%s\n", name);
        }
        else{
            printf("%s %s/%s\t%s %s", mode, uid, gid, date, name);
        }
        //long int strtol(const char *nptr, char **endptr, int base)
        lseek(fd, strtol(size, NULL, 10), SEEK_CUR);
    }
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
            if (argv[2][1] == 'v'){
                print(argv[3], 1);
            }
            else
                print(argv[2], 0);
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


