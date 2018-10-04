#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
	int i,j,size,rank,array[4][4],gathered_arr[4],record_buff[4],second_arr[4],sum=0;;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0){
		printf("Enter the array here: [16 elements]");
		for(i=0;i<4;i++){
			printf("\n");
			for(j=0;j<4;j++){
				printf("\t");
				scanf("%d",&array[i][j]);
			}
		}
		printf("\n");
		printf("Enter second array here : [4 elements]");
		for(i=0;i<4;i++){
			printf("\t");
			scanf("%d",&second_arr[i]);
		}
	}
	MPI_Scatter(&array,4,MPI_INT,record_buff,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&second_arr,4,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<=4;i++){
		sum += record_buff[i]*second_arr[i];
	}
	MPI_Gather(&sum,1,MPI_INT,gathered_arr,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0;i<4;i++)
			printf("\t%d",gathered_arr[i]);
	MPI_Finalize();
	return 0;
	
	
}
