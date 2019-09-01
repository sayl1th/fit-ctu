#include <stdio.h>
#include <math.h>
#include <stdlib.h>


long long int gcd(long long int a,long long int b);
long long int lcm(long long int a,long long int b);

int main(void) {
    int LENGTH = 10;
    int *pArr1 = (int *) malloc(LENGTH * sizeof(int)); 
    int *pArr2 = NULL;
    long long int result,prevLcm;
    long long int from,to;
    char ch1;
    int input,num;
    int n = 0;
    

    puts("Lanes:");
    
    while(1) {
    	
        scanf(" %c",&ch1);

    	
    	if (ch1 != '{' && ch1 != '}' && ch1 != ',') {
    		printf("Invalid input.\n");
    		free(pArr1);
    		return 0;
    	}


        if (ch1 == '}')
            break; 
    	

        if (n >= LENGTH) {
    		pArr2 = (int *) realloc(pArr1,((LENGTH*=2) * sizeof(int)));
    		pArr1 = pArr2;
    	}
    		

    	input = scanf("%d",&num);
    		
    	if (input != 1) {
    		printf("Invalid input.\n");
    		free(pArr1);
    		return 0;
    	
        }

        pArr1[n] = num;

        if (pArr1[n] < 1) {
            printf("Invalid input.\n");
            free(pArr1);
            return 0;
        }
    	
    	if (ch1 == '}')
    		break; 
    
        n++;	
    }
    
    puts("Routes:");
    

    while(1) {
        
        input = scanf("%lld  %lld", &from,&to);
        
       	if (input == EOF) {
            break;
        }

        
        if (input != 2 || from >= to || from > n || to > n || from < 0 || to < 0 ) {
        	printf("Invalid input.\n");
        	free(pArr1);
        	return 0;
        }


        prevLcm = 1;


        while (from < to) {

            result = lcm(prevLcm,pArr1[from]);
            prevLcm = result;
            from++;
        }

        printf("Vehicles: %lld\n",result);

        
    }
    free(pArr1);
}

long long  gcd(long long int a, long long int b)
{
    
    long long temp;
    while (b != 0)
    {
        temp = a % b;
        
        a = b;
        b = temp;
    }
    return a;
}

long long int lcm(long long int a,long long int b) {
    
    return a / gcd(a,b) * b;
}

