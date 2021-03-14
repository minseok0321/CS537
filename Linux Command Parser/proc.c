#include "proc.h"
#include "s_parser.h"

int all_pid(int s1, int u, int s2, int v, int c){

    DIR *dir;
    struct dirent *sd;


    dir = opendir("/proc");

    if(dir == NULL){
        
        fprintf(stderr, "Error! Unable to open directory");
        exit(1);

    }

    while((sd=readdir(dir)) != NULL){

        char *check = sd->d_name;
        int count = 0;

        for(int i = 0 ; i < strlen(check) ; i++){
            if(isdigit(check[i]) == 0){
                break;
            }
            else{
                count++;
            }
        }

        if(count == strlen(check)){
	    printf(">> %s  ", check);
            data(check, s1, u, s2, v, c);
        }


    }

    closedir(dir);
    
    return 0;
}
