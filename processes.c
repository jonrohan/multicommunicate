//Project: Multitasking and Communication Using Pipes
//Author: Jon Rohan
//Date: 3.3.2005

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <stdlib.h>

void getline(char *string, int array_size);

int main(int argc, char *argv[])
{
	//This gets the command line number of Messages
	int numMesgs = atoi(argv[1]); 

	int child1Pipe[2], child2Pipe[2]; //Create the child 1 & 2 pipes
	
	//Check to make shure that the input was > 0 and < 11
	if(numMesgs==0 || numMesgs > 10)
	{
		printf("ERROR: Incorrect value entered %d\n",numMesgs);
		exit(0);	
	}

	pipe(child1Pipe);//This initializes the child 1 pipe as a pipe
	
	//The read and write buffers for getting input
	char writeBuffer[256];
	char readBuffer[256];

	//This is where I create my first child process
	int process1ID = fork(); 

	//This if statement determines 
	//if it is the parent of the first fork
	if(process1ID > 0) 
	{
		//This initializes the child 2 pipe as a pipe
		pipe(child2Pipe); 

		//This is where I create my second child process
		int process2ID = fork(); 

		if(process2ID==0) //Child process 2
		{

			printf("P3 created.\n");

			int j;
			/*This for loop will repeat the */
			/*child processes actions for*/
			/*the amount of times the user 
			/*input as the number of messages*/
			for(j=1; j<=numMesgs;j++)
			{
				//close the other end of 
				//the pipe end so no writing occurs
				close(child2Pipe[1]); 

				//read from the pipe
				read(child2Pipe[0], readBuffer, 256); 

				printf("P3 received message ");
			     printf("#%d ('%s') from P1\n", j, readBuffer);
			}

			printf("P3 exiting.\n");
			return 0;

		}//end Child process 2

		else //Parent Process
		{
			printf("P1 exists.");
			int n;
			/*This for loop will repeat */
			/*the parent processes actions for*/
			/*the amount of times the user 
			/*input as the number of messages*/
			for(n=1;n<=numMesgs;n++)
			{
				//close the other end of 
				//each child pipes so no info can be read
				close(child1Pipe[0]);
				close(child2Pipe[0]);

		fputs("\nEnter a message (max 30 chars): \n", stdout);

				//This is tricky: I had to 
				//write an extra function for reasons I'll
				//explain at the bottom
				getline(writeBuffer, 30);
	
				//Write the message to each 
				//child processes' pipe
				printf("P1 sending message ");
			printf("#%d ('%s') to P1\n",n,writeBuffer);
				write(child1Pipe[1], writeBuffer, 256);
				printf("P1 sending message ");
			printf(" #%d ('%s') to P2\n",n,writeBuffer);
				write(child2Pipe[1], writeBuffer, 256);
				fflush(stdin);
				//this will make the parent 
				//process wait for 1 sec	
				sleep(1); 
			}

			wait(NULL);
			printf("P1 exiting.\n");
			return 0;

		}//end Parent Process
			
	}//end parent of first fork

	else if(process1ID==0)//Child process 1
	{
		printf("P2 created.\n");

		int k;
		/*This for loop will repeat */
		/*the child processes actions for*/
		/*the amount of times the user */
		/*input as the number of messages*/
		for(k=1;k<=numMesgs;k++)
		{
			//close the other end of 
			//the pipe end so no writing occurs
			close(child1Pipe[1]);
			
			//read from the pipe
			read(child1Pipe[0], readBuffer, 256); 

			printf("P2 recieved message ");
		printf("#%d ('%s') from P1\n",k, readBuffer);
			
		}

		printf("P2 exiting.\n");
		return 0;

	}//end Child process 1

	return 0;
}

//I ran into the problem, using 
//fgets, that when it brought in the line from the screen
//it brought with it the newline character. 
//I did some reading in the book to find out
//the way to fix this problem and it 
//explained that I should write this function.
//The function will take in a char 
//array and a limit of the size of the string
//then it will search for the \n character and delete it
void getline(char *string, int array_size)
{
	while(((*string = getchar()) != '\n') &&
		(--array_size > 0) )
		
		++string;
	*string = '\0';
}
