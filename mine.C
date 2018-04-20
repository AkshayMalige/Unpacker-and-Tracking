#include<iostream.h>
#include<conio.h>
#include<math.h>

void main() 
{ 
double N = 15387, dT = 6354823, NbydT = 0, C =0 , yes = 0;  

NbydT = N / dT;

C = NbydT / 0.55;

for ( i = 250; i < 450; i++){

yes = (NbydT * i) / C ;

}

cout<<"\n Squre of "<< yes <<; 
getch(); 
} 
