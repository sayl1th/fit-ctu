#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 250000

int main(void) {
    
    
    static int arr[SIZE];
    int count = 0;
    int seq,input;
    int biggestSeq = 0;
    int len;
    int answers = 0;
    
    
    printf("Values:\n");
    
    
    while((input = scanf("%d",&arr[count])) == 1) {
        count++;
    }
    

    
    if ( input == 0 || count < 2 || count > 250000) {
        printf("Invalid input.\n");
        return 0;
    }

    for (len = count - 1; len >= 0 ; len--) {
        
        for(int n = 0; n < len; n++) {
            
            if (len - n  + 1 < biggestSeq)
                break;
            
            if (arr[len] >= arr[n]) {
                seq = len - n + 1;
                
                if (biggestSeq <= seq) {
                    
                    biggestSeq = seq;
                    break;
                }
            }
        }
    }
    
    
    if (biggestSeq == 0) {
        printf("Does not exist.\n");
        return 0;
    }
    
    for (len = count - 1; len >= 0 && len - biggestSeq + 1 >= 0; len--) {

        if (arr[len] >= arr [len - biggestSeq + 1]) {
                printf("%d: %d - %d\n",biggestSeq,len - biggestSeq + 1,len);
                answers+=1;
        
    }
    
    }  
    
    printf("Answers: %d\n",answers);

}

