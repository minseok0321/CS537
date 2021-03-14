#include "s_parser.h"

int data(char* pid, int s1, int u, int s2, int v, int c){
    
    FILE *file1, *file2, *file3;
    
    uid_t my_uid = getuid();
    struct stat buffer;
    char filename[20];
    sprintf(filename, "/proc/%s", pid);
    stat(filename, &buffer);
    int proc_uid = buffer.st_uid;
               
    
//    char path[100] = "/proc/";
//    strcat(path, pid);
//    strcat(path, "/status");
//    file = fopen(path, "r");
//    int line_count = 0;
//    int line_num = 8;

    if(proc_uid == my_uid){
        
        char path1[100] = "/proc/";
        strcat(path1, pid);
        strcat(path1, "/stat");
        file1 = fopen(path1, "r");

        char path2[100] = "/proc/";
        strcat(path2, pid);
        strcat(path2, "/statm");
        file2 = fopen(path2, "r");
    
        char path3[100] = "/proc/";
        strcat(path3, pid);
        strcat(path3, "/cmdline");
        file3 = fopen(path3, "r");
    
        char line[150];

//    if(file != NULL){
//	while(fgets(line, 150, file) != NULL){
//		if(line_count == line_num){
//			char *split = strtok(line, "\t");
//			split = strtok(NULL, "\t");
//			printf("%s", split);
//			break;
//		}
//		else{
//			line_count++;
//		}
//	}
//    }

    
//    if(getuid() != split){
//	printf("%s", "you are not what I want.");
//    }
    
        char *asdf = fgets(line, 150, file1);
        char *split = strtok(asdf, " ");
        int count = 0;

            while(split != NULL){
            
                if(count == 2 && s1 == 1){
                    printf("State: %s  ", split);
                }

                else if(count == 13 && u == 1){
                    printf("User time: %s  ", split);
                }

                else if(count == 14 && s2 == 1){
                    printf("Start time: %s  ", split);
                }

                count++;
                split = strtok(NULL, " ");
            }
    
        asdf = fgets(line,150,file2);
        split = strtok(asdf, " ");
        count = 0;

            while(split != NULL){
             
                if(count == 0 && v == 1){
                    printf("Virtual Memory Being Used: %s  ", split);
                    break;
                }

                count++;
                split = strtok(NULL, " ");
             
                }

        char d;

        if(c == 1){
            printf("%s", "Cmdline: ");
            while((d = fgetc(file3)) != EOF){
                if(d != '\0'){
                    printf("%c", d);
                
                }
            }
        }
    
    printf("\n");

    fclose(file1);
    fclose(file2);
    fclose(file3);

    }
    
    return 0;
}
