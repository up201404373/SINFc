//
//  main.c
//  sinf.c
//
//  Created by Ricardo Ribeiro on 09/03/2018.
//  Copyright © 2018 Ricardo Ribeiro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


void * sensor_prnt_file (char* strc, FILE* strf){
    
    while(fgets(strc, 23, strf) != NULL){
        pthread_mutex_lock(&m);
        fprintf(strf, "%s", strc);
        pthread_mutex_unlock(&m);
    }
    pthread_exit(NULL);
}

void * sensor_reaad_file(FILE * stred, FILE* strdata){
    
    int i = 0;
    
    char* strrd = (char*) malloc (sizeof(char)*(23+1));
    
    char* strid = (char*) malloc (sizeof(char)*(23+1));
    
    char* strdat = (char*) malloc (sizeof(char)*(23+1));
    
    int strdatt;
    
    while(i!=EOF){
        pthread_mutex_lock(&m);
        i = fscanf(stred, "%s",strrd);
        
        strncpy(strid, strrd + 15 , 5);
        strdatt =(int) strtol(strid, NULL, 16);
        
        switch(strdatt){
            case 1:
                strncpy(strdat, strrd + 30, 30);
                fprintf(strdata, " id 1: %s\n", strdat);
                pthread_mutex_unlock(&m);
                break;
            case 2:
                strncpy(strdat, strrd + 30, 30);
                fprintf(strdata, " id 2: %s\n", strdat);
                pthread_mutex_unlock(&m);
                break;
            case 3:
                strncpy(strdat, strrd + 30, 30);
                fprintf(strdata, " id 2: %s\n", strdat);
                pthread_mutex_unlock(&m);
                break;
        }
    }
    pthread_exit(NULL);
}


int main(int argc, const char * argv[]) {
    char* strcom = (char*) malloc (sizeof(char)*(23+1));
    int c;
    pthread_t * p1 = (pthread_t*) malloc (sizeof(pthread_t));
    pthread_t * p2 = (pthread_t*) malloc (sizeof(pthread_t));
    pthread_t * p3 = (pthread_t*) malloc (sizeof(pthread_t));
    
    FILE* file_ptr = fopen("text.txt", "w");
    
    FILE* file_data = fopen("data.txt", "w");
    
    FILE* file_user = fopen("user.txt", "w");
    
    FILE* file_atuador = fopen("atuador.txt", "w");
    
    c=pthread_create(p1, NULL, sensor_prnt_file(strcom, file_ptr), NULL);
    if(c != 0) exit (-1);
    
    c=pthread_create(p2, NULL, sensor_reaad_file(file_ptr, file_data), NULL);
    if(c != 0) exit (-1);
    
    fclose(file_ptr);
    fclose(file_data);
    fclose(file_user);
    fclose(file_atuador);
}


