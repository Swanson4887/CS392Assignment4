#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

void transpif(int width, int height, int block){
	//Program which transposes a matrix, utilizing cache locality
	int totalInts = width * height;
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
		//printf("%f\n", randNum);
	}
	//begin looping by blocksize, then loop through each block.
	gettimeofday(&prevTime, NULL);
	for(j = 0; j < width; j += block){
		for(k = 0; k < height; k += block){
			if(height <= width){
				for(x = j;  x < width && x < j + block; x++){
					for(y = k; y < height && y < k + block; y++){
						OutputResMatrix[(x * height) + y] = InputResMatrix[(y * width) + x];
					}
				}
			} else{
				for(x = k;  x < height && x < k + block; x++){
					for(y = j; y < height && y < j + block; y++){
						OutputResMatrix[(y * height) + x] = InputResMatrix[(x * width) + y];
					}
				}
			}
		}
	}
	printf("\n\n");
	//for(i = 0; i < totalInts; i++){
	//	printf("%f\n", OutputResMatrix[i]);
	//}
	gettimeofday(&postTime, NULL);
	int prevTimeMicro = (prevTime.tv_sec * 1000000) + prevTime.tv_usec;
	int postTimeMicro = (postTime.tv_sec * 1000000) + postTime.tv_usec;
	printf("Transposition took %d microseconds\n", postTimeMicro - prevTimeMicro);
	free(InputResMatrix);
	free(OutputResMatrix);
}

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("Wrong number of command lines arguements\n");
		return -1;
	}
	transpif(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	return 0;
}