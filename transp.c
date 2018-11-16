#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

void transp(int input, int block){
	//Program which transposes a matrix, utilizing cache locality
	int totalInts = input * input;
	float* InputResMatrix = (float *)malloc(sizeof(float)*totalInts);
	float* OutputResMatrix = (float *)malloc(sizeof(float)*totalInts);
	float randNum = 0;
	struct timeval prevTime, postTime;
	int i; 
	int j; 
	int k; 
	int x; 
	int y;
	//populates the Array with random numbers from 0 to 99
	for(i = 0; i < totalInts; i++){
		randNum = (float) (rand() % 100);
		InputResMatrix[i] = randNum;
	}
	//begin looping by blocksize, then loop through each block.
	gettimeofday(&prevTime, NULL);
	for(j = 0; j < input; j += block){
		for(k = 0; k < input; k += block){
			for(x = j; x < j + block; x++){
				for(y = k; y < k + block; y++){
					OutputResMatrix[(y * input) + x] = InputResMatrix[(x * input) + y];
				}
			}
		}
	}
	gettimeofday(&postTime, NULL);
	int prevTimeMicro = (prevTime.tv_sec * 1000000) + prevTime.tv_usec;
	int postTimeMicro = (postTime.tv_sec * 1000000) + postTime.tv_usec;
	printf("Transposition took %d microseconds\n", postTimeMicro - prevTimeMicro);
	free(InputResMatrix);
	free(OutputResMatrix);
}

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Wrong number of command lines arguements\n");
		return -1;
	}
	transp(atoi(argv[1]), atoi(argv[2]));
	return 0;
}