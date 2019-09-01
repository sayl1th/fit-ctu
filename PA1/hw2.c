#include <stdio.h>
#include <math.h>

long long int gcd(long long int a, long long int b);
long long int lcm(long long int a, long long int b);


int main(void) {
    
    double minWidth, minLength;
    unsigned int minWidthToInt,minLengthToInt;
    double tile,joint;
    unsigned int tileToInt,jointToInt;
    unsigned long long int length,width,dimension,tDimension;
    unsigned long long int k,newK,biggestK; // konstant
    unsigned long long int tileAndJoint,firstTileAndJoint,biggestTileAndJoint;
    unsigned long long int LCM;
    int input,noSolution = 0;
    
    
    printf("Minimum dimensions:\n");
    input = scanf("%lf %lf",&minLength,&minWidth);
    
    if (input != 2 || minLength <= 0 || minWidth <= 0 || minWidth > 10000000 || minLength > 10000000 ||
        ((floor(minLength * 10)  / 10) != minLength) || ((floor(minWidth * 10) / 10) != minWidth)) {
        printf("Invalid input.\n");
        return 0;
    }
    
    minWidthToInt= (int)(minWidth * 10);
    minLengthToInt = (int)(minLength * 10);

    
    printf("Tiles:\n");
    input = scanf("%lf %lf",&tile,&joint);
    if (input != 2 || tile <= 0 || joint < 0 || tile > 10000000 || joint > 10000000
        || ((floor(tile * 10) / 10) != tile) || ((floor(joint * 10) / 10) != joint)) {
        
        printf("Invalid input.\n");
        return 0;
    }

    tileToInt = (int)(tile * 10);
    jointToInt = (int)(joint * 10);
    tileAndJoint = tileToInt + jointToInt;
    k = jointToInt;



    if (minLengthToInt < minWidthToInt)
        dimension = ((int)((minLengthToInt - jointToInt) / (jointToInt+tileToInt)) + 1) * (jointToInt + tileToInt) + jointToInt;

    else
        dimension = ((int)((minWidthToInt - jointToInt) / (jointToInt+tileToInt)) + 1) * (jointToInt + tileToInt) + jointToInt;


    do {

        if (input != 2 || tile <= 0 || joint < 0 || tile > 10000000 || joint > 10000000
            || ((floor(tile * 10) / 10) != tile) || ((floor(joint * 10) / 10) != joint)) {
            printf("Invalid input.\n");
            return 0;
        }

        if (noSolution == 1)
            continue;

        tileToInt = (int)(tile * 10);
        jointToInt = (int)(joint * 10);
        
        firstTileAndJoint = tileToInt + jointToInt;

        if (tileAndJoint > firstTileAndJoint)
            biggestK = k;
        else 
            biggestK = jointToInt;

        if (tileAndJoint > firstTileAndJoint)
            biggestTileAndJoint = tileAndJoint;
        else
            biggestTileAndJoint = firstTileAndJoint;
        
        newK = biggestK;

        LCM = lcm(tileAndJoint,firstTileAndJoint);
                
        int n = 1;
        while ((newK - k) % tileAndJoint != 0 || (newK - jointToInt) % firstTileAndJoint != 0) {
            
            if (newK > LCM) {

                if ((n * (biggestTileAndJoint + biggestK)) % (tileAndJoint + jointToInt) == 0 && (jointToInt + k) != 0) {
                    noSolution = 1;
                    break;
                }
                n++;
            }
            newK += biggestTileAndJoint;
            
        }
        
        tileAndJoint = LCM;
        k = newK;
        dimension = newK;

    }
    while ((input = scanf("%lf %lf",&tile,&joint)) != EOF);

    
    if (noSolution == 1) {
        printf("No solution.\n");
        return 0;
    }

    else {
        
        tDimension = dimension;

        while (dimension < minLengthToInt)
        dimension += tileAndJoint;

        length = dimension;

        while (tDimension < minWidthToInt)
        tDimension += tileAndJoint;

        width = tDimension;
    
    }
    
    printf("Dimensions: %.1f %c %.1f\n", (double)(length)/10 ,'x', (double)(width)/10);
    return 0;
}


long long int gcd(long long int a, long long int b) {
    if (a < b)
        return gcd(b, a);
    
    if (b == 0)
        return a;
    
    else
        return (gcd(b, a - floor(a / b) * b));
}

long long int lcm(long long int a, long long int b) {
    return (a * b / gcd(a,b));
}
