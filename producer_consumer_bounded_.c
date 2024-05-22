
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10


int buffer[BUFFER_SIZE];
int in = 0;  
int out = 0;  
int full=0,mutex=1,empty=BUFFER_SIZE;

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
    wait(&empty);
    wait(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    printf("Produced: %d\n", item);

    signal(&mutex);
    signal(&full);
    
    
}


void consume() {
    int item;
   
    wait(&full);
    wait(&mutex);

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("Consumed: %d\n", item);

    signal(&mutex);
    signal(&empty);

    
}

int main() {
    int c;

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
