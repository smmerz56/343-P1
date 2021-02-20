#include <iostream>
using namespace std;

#include "polynomial.h"

int main( ) 
    
{
  //Testing constructor
  Polynomial p1; 
  
  Polynomial p2; 
  
  //Testing changeCoefficient()
  p1.changeCoefficient( -3, 1 );
   
  p1.changeCoefficient( 1, 0 ); 

  p1.changeCoefficient( 4, 5 );  

  cout << "p1 = " << p1 << endl;
  
  
  p2.changeCoefficient( 1, 3 );

  p2.changeCoefficient( 8, 2 );  

  p2.changeCoefficient( -2, 0 );  

  p2.changeCoefficient( -1, 4 );

  p2.changeCoefficient( 8, -1 );

  cout << "p2 = " << p2 << endl; 
  
  
  cout << endl;
  // Testing copy constructor
  Polynomial p3(p1);
  
  cout << "p3(p1) " << p3 << endl;
  
  cout << endl;
  //Testing degree() and coefficient()   
  cout << "p1 degree = " << p1.degree() << endl;
  
  cout << "p2 coeff = " << p2.coefficient(4) << endl; 
  
  
  cout << endl;
  // Testing operator+  
  p3 = p1 + p2;  

  cout << "p3 " << p3 << endl;  

  Polynomial p4;
  
  Polynomial p5;
 
  p3 = p4 + p1;

  cout << p3 << endl; 
  
  cout << "p4 + p5 " << p4 + p5 << endl;
  
  
  cout << endl;
  //Tetsing operator-  
    
  p4.changeCoefficient( 14, 3 );
   
  p4.changeCoefficient( -3, 1 ); 

  p4.changeCoefficient( 2, 0 );  

  cout << "p4 = " << p4 << endl;
  
  p5.changeCoefficient( 1, 4 );

  p5.changeCoefficient( -2, 3 );  

  p5.changeCoefficient( 5, 2 );  

  p5.changeCoefficient( -5, 0 );

  p5.changeCoefficient( 8, -1 );

  cout << "p5 = " << p5 << endl;
  
  cout << "p4 - p5 " << p4 - p5 << endl;
  
  
  cout << endl;
  // != test and == test 
  Polynomial p7;
  
  bool success = p4 != p5;
  
  bool success2 = p4 == p5;
  
  bool success3 = p7 == p5;
  
  cout << "p4 != p5 " << success << endl; 
  
  cout << "p4 == p5 " << success2 << endl;
  
  cout << "Empty p7 == p5 " << success3 << endl;
  
  success3 = p7 != p5;
  
  cout << "Empty p7 != p5 " << success3 << endl;
  
  Polynomial p6(p5);
  
  success = p6 != p5;
  
  success2 = p6 == p5;  

  cout << "After p6(p5)" << endl;

  cout << "p6 != p5 " << success << endl; 
  
  cout << "p6 == p5 " << success2 << endl;
  
  
  cout << endl;
  // = test
  cout << "p7 " << endl;
  
  cout << "p1 " << p1 << endl;
  
  p7 = p1; 
  
  cout << "p7 = p1 " << p7 << endl; 
  
  p1 = p1; 
  
  cout << "p1 = p1 " << p1 << endl;
  
  
  cout << endl;
  //Testing operator+= and operator-=
  cout << "p1 " << p1 << endl;
  
  cout << "p2 " << p2 << endl;
  
  p2 += p1; 

  cout << "p2 += p1 " << p2 << endl;

  cout << endl;
  cout << "p2 " << p2 << endl;  
  
  cout << "p1 " << p1 << endl;
  
  p2 -= p1;

  cout << "p2 -= p1 " << p2 << endl;  

}
 