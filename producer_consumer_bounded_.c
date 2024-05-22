
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int BUFFER_SIZE;
int *buffer;
int in = 0;  
int out = 0;  
int full=0,mutex=1,empty;

void wait(int *s){
    while(*s<=0);
    *s=*s-1;
}

void signal(int *s){
    *s=*s+1;
}


void produce() {
    int item;
    
    printf("enter data to produce");
    scanf("%d",&item);
    if(!(empty<=0)){
    wait(&empty);
    wait(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    printf("Produced: %d\n", item);

    signal(&mutex);
    signal(&full);
    }else{
        printf("buffer full\n");
    }
    
}


void consume() {
    int item;
   if(!(full<=0)){
    wait(&full);
    wait(&mutex);

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("Consumed: %d\n", item);

    signal(&mutex);
    signal(&empty);
   }else{
       printf("buffer empty can't consume\n");
   }

    
}

int main() {
    int c;
    printf("Enter the buffer size:");
    scanf("%d",&BUFFER_SIZE);
    empty=BUFFER_SIZE;
    buffer=(int *)calloc(BUFFER_SIZE,sizeof(int));
    while(1){
        printf("enter choice:\n1.produce\n2.consume\n");
        scanf("%d",&c);

        if(c==1){
            produce();
        }
        else if(c==2){
            consume();
        }
        else{
            break;
        }
    }
}
