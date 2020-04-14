#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdbool.h>

#define size 1000000
//int x;
int arr[size];
//int thread_id = 0;
//int maxArr[x];
char *filename = "./File1M.txt";
char *resultFile = "./result1M.txt";
FILE *fileWrite;

 struct Pair{
	int left;
	int right;
};

struct Pair pair[100];

void  *read_ints(const char* file_name,int arr[]){
	FILE *file = fopen(file_name, "r");
	int i = 0;
	int pointer = 0;
	fscanf(file, "%d", &i);
	while (!feof (file)){

		arr[pointer]= i;
		pointer++;
		fscanf(file, "%d", &i);
	}
	fclose(file);
}

void *findMax(void *arg){
//	int *arr = (int *)arg;
	struct Pair* pair_p =  arg;
	int * max = (int*) malloc (sizeof(int));
	* max = arr[pair_p->left];
	int i = 0;
	int hiddenKey;
	bool found = false;
	for(i = pair_p->left; i <= pair_p->right; i++){
		if ( *max <= arr[i]){
			*max = arr[i];
		}
		if(arr[i] < 0){
			hiddenKey = i;
			found = true;
			printf("\nHi I am Pthread %u and I found hidden key in position A[%d]\n", pthread_self(), hiddenKey);
			fprintf(fileWrite, "\nHi I am Pthread %u and I found hidden key in position A[%d]\n", pthread_self(), hiddenKey);
		}
	}
//	pthread_exit(0);
	if(!found){
		printf("\nHi I am Pthread %u and I cannot find hidden key\n", pthread_self());
		fprintf(fileWrite, "\nHi I am Pthread %u an I cannot find hidden key\n", pthread_self());
	}
//	printf("\nHi I am Pthread %d and I found max in position A[%d]\n", pthread_self(), key);
	return max;
}

int main(){
	read_ints(filename,arr);
	fileWrite = fopen(resultFile, "r+");
//	FILE *file = fopen(resultFile, "r+");
//	for(j = 0; j < size; j++) printf("%d\n", arr[j]);
	int i; // count variable
	int x; // x is number of thread => input from user
	scanf("%d",&x);
	printf("\nNumber of threads is: %d\n", x);
	fprintf(fileWrite, "\nNumber of threads is: %d\n",x);
	printf("\n Thank you for your cooperation. Please wait for the result :) \n");
	
//	struct Pair* pair = malloc(x*sizeof *pair);

	int interval =  size/x;
//	printf("Your interval: %d", interval);
	int preLeft = -1;
	for(i = 0; i < x-1; i++){
		pair[i].left = preLeft +1;
		pair[i].right = pair[i].left + interval -1;
		preLeft = pair[i].right;

	}
	pair[x-1].left = preLeft + 1;
	pair[x-1].right = size - 1;

	pthread_t threads[x];
	for(i = 0; i < x; i++){
		pthread_create(&threads[i], NULL, findMax, &pair[i]);
	}
	
	int max = arr[0];
	int*tempMax;
	for(i = 0; i < x; i++){
		pthread_join(threads[i],(void*) &tempMax);
//		printf("Your temp max is: %d \n", *tempMax);
		if(max < *tempMax) max = *tempMax;
	}

	printf("\n Max is: %d\n", max);
	fprintf(fileWrite,"\n Max is: %d", max);
	
	fclose(fileWrite);

	return 0;
}
