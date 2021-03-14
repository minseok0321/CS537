#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "s_parser.h"
#include "proc.h"

int main(int argc, char **argv){

    int option_val = 0;
    char *pid = NULL;
    int pflag = 0, sflag = 0, Uflag = 1, Sflag = 0, vflag = 0, cflag = 1;
    int pcount = 0;
    char *cmp = "-";
    
    while((option_val = getopt(argc, argv, "p:s::S::U::v::c::")) != -1){
	
        switch(option_val){

            case 'p':
                
                if(optarg == NULL){
                    fprintf(stderr, "there must be a valid PID. \n");
                    exit(1);
                }
                
                //only supporting a single -p option
                if(pcount == 1){
                    fprintf(stderr, "only single -p option is allowed. \n");
                    exit(1);
                }
                
                pid = optarg;
                printf(">>PID: %s  ", pid);
                pcount++;
                pflag = 1;
                break;

            case 's':
                            
                if(optarg == NULL){
                    sflag = 1;
                    break;
                }
                            
                if(strcmp(optarg, "-") != 0){
                    fprintf(stderr, "the argument is invalid. \n");
                    exit(1);
                }
                            
                if(strcmp(optarg, cmp) == 0){
		    sflag = 0;
                    break;
                }
                
            case 'U':
                            
                if(optarg == NULL){
                    Uflag = 1;
		    break;
                }
                if(strcmp(optarg, "-") != 0){
                    fprintf(stderr, "the argument is invalid. \n");
                    exit(1);
                }
                            
                if(strcmp(optarg, cmp) == 0){
                    Uflag = 0;
                    break;
                }
                
            case 'S':
                            
                if(optarg == NULL){
                    Sflag = 1;
                    break;
                }
                            
                if(strcmp(optarg, "-") != 0){
                    fprintf(stderr, "the argument is invalid. \n");
                    exit(1);
                }
                            
                if(strcmp(optarg, cmp) == 0){
                    Sflag = 0;
		    break;
                }

            case 'v':
                
                if(optarg == NULL){
                    vflag = 1;
                    break;
                }
                            
                if(strcmp(optarg, "-") != 0){
                    fprintf(stderr, "the argument is invalid. \n");
                    exit(1);
                }
                            
                if(strcmp(optarg, cmp) == 0){
                    vflag = 0;
		    break;
                }
               
            case 'c':
                
                if(optarg == NULL){
                    cflag = 1;
		    break;
                }
                
                if(strcmp(optarg, "-") != 0){
                    fprintf(stderr, "the argument is invalid. \n");
                    exit(1);
                }
                            
                if(strcmp(optarg, cmp) == 0){
                    cflag = 0;
                    break;
                }

            case '?':
                fprintf(stderr, "Unknown option -%c. \n", optopt);
                exit(1);
                
            default:
                fprintf(stderr, "Something has gone wrong with your command");
                exit(1);

        }
    
    }

    //a specific PID with specific options o
    if(pflag == 0){
	    all_pid(sflag, Uflag, Sflag, vflag, cflag);
    }
    else if(pflag != 0 || sflag != 0 || Uflag != 1 || Sflag != 0 || vflag != 0 || cflag != 1){
            data(pid, sflag, Uflag, Sflag, vflag, cflag);
    }
    
    return 0;
}
