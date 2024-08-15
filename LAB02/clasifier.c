#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int last_digit(int number) {
    int dig = number % 10;
    return dig == 2 || dig == 1 ? 1 : 0;
}

int main(int na, char *argv[]) {
    int n, i, pid;
    int root = getpid();
    int pipes[3][2];	
    
    if (na != 2) {
        fprintf(stderr, "Uso: %s <n>\n", argv[0]);
        exit(1);
    }
    n = atoi(argv[1]);

    for (int j = 0; j < 3; j++) {
        pipe(pipes[j]);
    }

    for (i = 0; i < 3; i++) {
		//create 3 sons
        if (!(pid = fork())) {
            int r, mypid;
            mypid = getpid();
            srand(mypid);			

            for (int j = 0; j < n; j++) {
                r = rand() % 528; 
                //consider
                if (last_digit(r)) {
                    write(pipes[2][1], &r, sizeof(r));
                } else if (r % 2 == 0) {
                    write(pipes[1][1], &r, sizeof(r));
                } else {
                    write(pipes[0][1], &r, sizeof(r));
                }
            }
			//close write pipe
            for (int j = 0; j < 3; j++) {
                close(pipes[j][1]);
            }
			//close read pipe -> not the i pipe
            for (int j = 0; j < 3; j++) {
                if (j == i) continue;
                close(pipes[j][0]);
            }
			//read i-pipe 
            int num;
            int hasNumbers = 0;
			//this will read until EOF
            while (read(pipes[i][0], &num, sizeof(num)) > 0) {
            	hasNumbers = 1; //will check data 
                printf("PID %d: %d\n", mypid, num);
            }
            if (!hasNumbers) {
                printf("PID %d: Conjunto vacío\n", mypid);
            }

            close(pipes[i][0]); //close i-pipe
            exit(0);
        }
    }
    if (getpid() == root) {
        for (int j = 0; j < 3; j++) {
            close(pipes[j][1]);
            close(pipes[j][0]);
        }
        for (int j = 0; j < 3; j++) {
            wait(NULL);
        }
    }

    return 0;
}
