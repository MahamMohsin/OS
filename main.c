#include <stdio.h>
#include "math.h"

int main(){
double num1,num2,result;
char op;
printf("Enter expression: (eg: num1 + num2)");
scanf("%lf %c %lf",&num1,&op,&num2);

if(op=='+'){result=add(num1,num2);}
if(op=='-'){result=sub(num1,num2);}
if(op=='/'){result=div(num1,num2);}

printf("result: %.2lf",result);
}
