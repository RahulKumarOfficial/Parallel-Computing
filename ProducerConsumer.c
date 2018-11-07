#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 10

int number = 0;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sc = PTHREAD_COND_INITIALIZER;
pthread_cond_t sp = PTHREAD_COND_INITIALIZER;

//Consumer process
void* consumer(){
	printf("\n<-->Hello Consumer<-->");
	while(1){
		pthread_mutex_lock(&mu);
		pthread_cond_signal(&sp);
		pthread_cond_wait(&sc,&mu);
		printf("\nConsumer: %d",number);
		pthread_mutex_unlock(&mu);
		if(number==MAX){
			printf("\n<--Consumer Done-->");
			break;
		}
	}
}

//Producer process
void* producer(){
	printf("\n<--Hello producer-->");
	while(1){
		pthread_mutex_lock(&mu);
		number++;
		printf("\nProducer: %d",number);
		pthread_cond_signal(&sc);
		if(number!=MAX)
			pthread_cond_wait(&sp,&mu);
		pthread_mutex_unlock(&mu);
		if(number==MAX){
			printf("\n<--Producer Done-->");
			break;
		}
	}
}
int main(){
	int i, rc;
	pthread_t t[2];
	int consumerStart = pthread_create( &t[0], NULL, consumer, NULL );
	if(consumerStart == -1)
		printf("Error in starting consumer");
	int producerStart = pthread_create( &t[1], NULL, producer, NULL );
	if(producerStart == -1)
		printf("Error in starting producer");
	pthread_join( t[0], NULL );
	pthread_join( t[1], NULL );
	return 0;
}

// Instructions to run this program specially
// [terminal] : mpicc -o objectName ProducerConsumer.c -lpthread
// [terminal] : mpirun ./objectName
