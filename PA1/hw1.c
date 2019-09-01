#include <stdio.h>
#include <math.h>


int main(void) {
    
    double x1,y1,x2,y2,x3,y3;
    double dotProductA,dotProductB,dotProductC;
    double lenghtAB,lenghtAC,lenghtBC;
    double pointForA1,pointForA2,pointForB1,pointForB2,pointForC1,pointForC2;
    char c1,c2,c3;
    double mistake;
    
    printf("Point A:\n");
    if ((scanf(" %c %lf %c %lf %c",&c1,&x1,&c2,&y1,&c3) != 5) || (c2 != ',') || (c1 != '[') || (c3 != ']')) {
        
        printf("Invalid input.\n");
        return 0;
    }
    printf("Point B:\n");
    if ((scanf(" %c %lf %c %lf %c",&c1,&x2,&c2,&y2,&c3) != 5) || (c2 != ',') || (c1 != '[') || (c3 != ']')) {
        
        printf("Invalid input.\n");
        return 0;
    }
    printf("Point C:\n");
    if ((scanf(" %c %lf %c %lf %c",&c1,&x3,&c2,&y3,&c3) != 5) || (c2 != ',') || (c1 != '[') || (c3 != ']')) {
        
        printf("Invalid input.\n");
        return 0;
    }
//    Points of A', B', C'
    pointForA1 = (x2 + x3) - x1;
    pointForA2 = (y2 + y3) - y1;
    pointForB1 = (x1 + x3) - x2;
    pointForB2 = (y1 + y3) - y2;
    pointForC1 = (x1 + x2) - x3;
    pointForC2 = (y1 + y2) - y3;

//    Dot Products of Points
    dotProductA = (x2-x1) * (x3-x1) + (y2 - y1) * (y3 - y1);
    dotProductB = (x1-x2) * (x3-x2) + (y1 - y2) * (y3 - y2);
    dotProductC = (x2-x3) * (x1-x3) + (y2 - y3) * (y1 - y3);
 
//    Lenght for Points
    lenghtAB = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    lenghtAC = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
    lenghtBC = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2);

    
//    If parallelogram does not exist
    
    mistake = 1e-12 * (fabs((x2-x1) * (y3 - y2)) + fabs((y2 - y1) * (x3 - x2)));
    
  
   if (((fabs((x1-x2) * (y2-y3) - (y1-y2) * (x2-x3))) < mistake) || (x1 == x2 && y1 == y2) ||(x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)) {
        
        printf("Parallelograms do not exist.\n");
        return 0;
    }
    
//    Test for A
    if ((fabs(lenghtAB - lenghtAC) < mistake) && (fabs(dotProductA) < mistake))
        printf("A\': [%.10g,%.10g], square\n",pointForA1,pointForA2);
    
    if ((fabs(lenghtAB - lenghtAC) < mistake) && (fabs(dotProductA) > mistake))
        printf("A\': [%.10g,%.10g], rhombus\n",pointForA1,pointForA2);
    
    if ((fabs(lenghtAB - lenghtAC) > mistake) && (fabs(dotProductA) < mistake))
        printf("A\': [%.10g,%.10g], rectangle\n",pointForA1,pointForA2);
    
    if ((fabs(lenghtAB - lenghtAC) > mistake) && (fabs(dotProductA) > mistake))
        printf("A\': [%.10g,%.10g], parallelogram\n",pointForA1,pointForA2);
    
//    Test for B
    
    if ((fabs(lenghtBC - lenghtAB) < mistake) && (fabs(dotProductB) < mistake))
        printf("B\': [%.10g,%.10g], square\n",pointForB1,pointForB2);
    
    if ((fabs(lenghtBC - lenghtAB) < mistake) && (fabs(dotProductB) > mistake))
        printf("B\': [%.10g,%.10g], rhombus\n",pointForB1,pointForB2);
    
    if ((fabs(lenghtBC - lenghtAB) > mistake) && (fabs(dotProductB) < mistake))
        printf("B\': [%.10g,%.10g], rectangle\n",pointForB1,pointForB2);
   
    if ((fabs(lenghtBC - lenghtAB) > mistake) && (fabs(dotProductB) > mistake))
        printf("B\': [%.10g,%.10g], parallelogram\n",pointForB1,pointForB2);

//    Test for C
    
    if ((fabs(lenghtAC - lenghtBC) < mistake) && (fabs(dotProductC) < mistake))
        printf("C\': [%.10g,%.10g], square\n",pointForC1,pointForC2);
    
    if ((fabs(lenghtAC - lenghtBC) < mistake) && (fabs(dotProductC) > mistake))
        printf("C\': [%.10g,%.10g], rhombus\n",pointForC1,pointForC2);
    
    if ((fabs(lenghtAC - lenghtBC) > mistake) && (fabs(dotProductC) < mistake))
        printf("C\': [%.10g,%.10g], rectangle\n",pointForC1,pointForC2);
    
    if ((fabs(lenghtAC - lenghtBC) > mistake) && (fabs(dotProductC) > mistake))
        printf("C\': [%.10g,%.10g], parallelogram\n",pointForC1,pointForC2);
    
    
}
