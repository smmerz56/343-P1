using namespace std;
#include "polynomial.h"

// Polynomial 
// ---------------------------------------------------------------------------

// Merz, Sean CSS 343A

// Creation Date - 6.26.2020

// Date of Last Modification - 7.4.2020

// ---------------------------------------------------------------------------

// Purpose - This program creates a polynomial in the form of a circular  
//           linked list.

// --------------------------------------------------------------------------- 
 
// Notes on specifications, special algorithms, and assumptions:
//    -The program will ignore any negative exponent
//    -The dummy head will have a coefficient and power both set to 0

// ---------------------------------------------------------------------------

//constructor
Polynomial::Polynomial(){
   head = new Term();   
   head->next = head;
   head->prev = head;
   
   size = 0;
   head->coeff = 0.0;
   head->power = 0;
}

//----------------------------------------------------------------------------
//copy constructor
Polynomial::Polynomial(const Polynomial& p){    
   copy(p);      
}

//----------------------------------------------------------------------------
//destructor
// deletes the Polynomial by looping through it and calling remove();
Polynomial::~Polynomial(){
   Term* current = head->next;
   
   while(current != head){
      remove(current);
      current = head->next;
   }
   delete head;    
}

//---------------------------------------------------------------------------- 
//degree
//finds the degree of the polynomial
// postcondition: returns 0 if there are not any Terms in the Polynomial
int Polynomial::degree() const{
   Term* current = head->next;
   return current->power;
}

//---------------------------------------------------------------------------- 
//coefficient
// finds the coefficient of the term with the power given to the method
// postcondition: returns 0 if power is not found
double Polynomial::coefficient(const int power) const{
   Term* current = head->next;
   
   while(current != head){
      if(current->power == power){
         return current->coeff;
      }
      current = current->next;
   }   
   return 0;  
}

//---------------------------------------------------------------------------- 
//changeCoefficient
// Calls insert() if the head is the only node in the list, if the power of 
// the new term is less than the power of the term at current or if the head
// is current->next (end of list). If power matches and newCoefficient == 0, 
// function calls remove.
// precondition: must have a power >= 0
// postcondition: returns bool to caller.
bool Polynomial::changeCoefficient(const double newCoefficient, const 
                                                               int power){
   Term* current = head;      
   if(power >= 0){ 
      // for the first insertion after the dummy head
      if(current->next == head){
         bool success = insert(current, newCoefficient, power);
         return success;
      }
      
      //loop through the Polynomial to find where Term goes
      while(current->next != head){
         current = current->next;
         //if user wants to manipulate a Term
         if(current->power == power){
            if(newCoefficient == 0){
               return remove(current);
            }
            else{        
               current->coeff = newCoefficient;
               return true;
            }
         }   
         // to find the correct spot for insertion
         if(current->power < power || current->next == head){
            bool success = insert(current, newCoefficient, power);
            return success;
         }
      }    
   }
   return false;
}

//---------------------------------------------------------------------------- 
//operator+
// adds two Polynomials
// calls insert()
Polynomial Polynomial::operator+(const Polynomial& p) const{
   Polynomial addition;
   
   Term* current = head->next;// Pointer for Polynomial left of +
   Term* pCurrent = p.head->next; // Pointer for Polynomial right of +
   Term* additionCurrent = addition.head; // Pointer for new Polynomial
   
   //loop through both Polynomials until one or both reach their dummy head
   while(current != head && pCurrent != p.head){
      if(current->power > pCurrent->power){
         addition.insert(additionCurrent, current->coeff, current->power);
         additionCurrent = additionCurrent->next;
         current = current->next;
      }
      else if(current->power < pCurrent->power){
         addition.insert(additionCurrent, pCurrent->coeff, pCurrent->power);
         additionCurrent = additionCurrent->next;
         pCurrent = pCurrent->next;
      }
      else if(current->power == pCurrent->power){
         bool success = addition.insert(additionCurrent, current->coeff + 
                                          pCurrent->coeff, pCurrent->power);
         if(success){
            additionCurrent = additionCurrent->next;         
         }
         current = current->next;   
         pCurrent = pCurrent->next;         
      }
   } 
   // both of these if's will add any more Terms, to the addition Polynomial, 
   // if either of the other Polynomials have any left after the loop
   if(current != head){  
          
      while(current != head){            
         addition.insert(additionCurrent, current->coeff, current->power);
         additionCurrent = additionCurrent->next;
         current = current->next;
      }
   }
   if(pCurrent != p.head){  
           
      while(pCurrent != p.head){            
         addition.insert(additionCurrent, pCurrent->coeff, pCurrent->power);
         additionCurrent = additionCurrent->next;
         pCurrent = pCurrent->next;
      }
   }   

   return addition;
}

//---------------------------------------------------------------------------- 
// operator-
// subtracts two Polynomials
// calls insert()
Polynomial Polynomial::operator-(const Polynomial& p) const{
   Polynomial subtraction;
   
   Term* current = head->next;// Pointer for Polynomial left of +
   Term* pCurrent = p.head->next;// Pointer for Polynomial right of +
   Term* subtractionCurrent = subtraction.head;// Pointer for new Polynomial
   
   //loop through both Polynomials until one or both reach their dummy head
   while(current != head && pCurrent != p.head){
      if(current->power > pCurrent->power){
         subtraction.insert(subtractionCurrent, current->coeff, 
                                                            current->power);
         subtractionCurrent = subtractionCurrent->next;
         current = current->next;
      }
      else if(current->power < pCurrent->power){         
         subtraction.insert(subtractionCurrent, pCurrent->coeff * -1, 
                                                            pCurrent->power);
         subtractionCurrent = subtractionCurrent->next;
         pCurrent = pCurrent->next;         
      }
      else if(current->power == pCurrent->power){
         bool success = subtraction.insert(subtractionCurrent, current->coeff - 
                                             pCurrent->coeff, pCurrent->power);
         if(success){
            subtractionCurrent = subtractionCurrent->next;         
         }
         current = current->next;
         pCurrent = pCurrent->next;
      }
   }   
   
   // both of these if's will add any more Terms, to the subtraction Polynomial, 
   // if either of the othe Polynomials have any left after the loop
   if(current != head){      
      while(current != head){            
         subtraction.insert(subtractionCurrent, current->coeff, current->power);
         subtractionCurrent = subtractionCurrent->next;
         current = current->next;
      }
   }
   if(pCurrent != p.head){      
      while(pCurrent != p.head){            
         subtraction.insert(subtractionCurrent, pCurrent->coeff * -1, 
                                                               pCurrent->power);
         subtractionCurrent = subtractionCurrent->next;
         pCurrent = pCurrent->next;
      }
   }   

   return subtraction;
} 

//---------------------------------------------------------------------------- 
//operator==
// compares two Polynomials by size or Terms to see if they are the same
// postcondition: Returns bool 
bool Polynomial::operator==(const Polynomial& p) const{
   if(this->size != p.size){      
      return false;
   }
   else{
      Term* currentLeft = head->next;
      Term* currentRight = p.head->next;
      
      while(currentLeft != head){
         if(currentLeft->coeff != currentRight->coeff || currentLeft->power 
                                                   != currentRight->power){
            return false;
         }
         currentLeft = currentLeft->next;
         currentRight = currentRight->next;
      }
   }
   return true;
}

//---------------------------------------------------------------------------- 
//operator!=
// compares two Polynomials by size or Terms to see if they are the same
// postcondition: Returns bool 
bool Polynomial::operator!=(const Polynomial& p) const{
   
   if(this->size != p.size){      
      return true;
   }
   else{
      Term* currentLeft = head->next;
      Term* currentRight = p.head->next;
      
      while(currentLeft != head){
         if(currentLeft->coeff != currentRight->coeff || currentLeft->power 
                                                   != currentRight->power){
            return true;
         }
         currentLeft = currentLeft->next;
         currentRight = currentRight->next;
      }
   }
   return false;
}

//---------------------------------------------------------------------------- 
//operator=
// sets one Polynomial equal to another
// precondition: must be a different Polynomial on the left side of the 
// equation than on the right.
// postcondition: If the user tries to copy the same Polynomial, the function  
// just returns the original Polynomial.
Polynomial& Polynomial::operator=(const Polynomial& p){
   if(*this != p){
      Term* current = head->next;
      
      while(current != head){
         // Calls the remove function while walking down the Polynomial 
         // that is being replaced.
         remove(current);
         current = head->next;
      }
      delete head;
      // Uses the copy function to do some of its work.
      copy(p);
      
      return *this;
   }
   return *this;
}

//---------------------------------------------------------------------------- 
//operator+=
// adds two Polynomials and sets *this equal to their sum
Polynomial& Polynomial::operator+=(const Polynomial& p){
   return *this = *this + p;
}

//---------------------------------------------------------------------------- 
//operator-=
// subtracts two Polynomials and sets *this equal to their difference
Polynomial& Polynomial::operator-=(const Polynomial& p){
   return *this = *this - p;
}

//---------------------------------------------------------------------------- 
//insert
// called by changeCoefficient() to insert Term into a Polynomial
// precondition: newCoefficient cant equal 0
// postcondition: returns false if newCoefficient == 0 and Increases the 
// size by 1 after every insert.
bool Polynomial::insert(Term* pos, const double newCoefficient, const int 
                                                                     power){

   if(newCoefficient != 0){
      Term* newPoly = new Term;     
      newPoly->coeff = newCoefficient;
      newPoly->power = power;  
      size++;
      // case for inserting after the head and middle of the polynomial
      if(pos->power < power){
         newPoly->next = pos;
         newPoly->prev = pos->prev;
         
         Term* current = pos->prev;
         pos->prev = newPoly;
         current->next = newPoly; 
         return true;
      }
      //case for inserting at the end of the polynomial 
      if(pos->next == head){
         newPoly->next = head;
         newPoly->prev = pos;
         pos->next = newPoly;
         head->prev = newPoly;
         return true;
      }
   }
   
   return false;
}

//---------------------------------------------------------------------------- 
//remove
// used by the destructor and changeCoefficient to remove a Term from the 
// Polynomial
// postcondition: reduces size by one
bool Polynomial::remove(Term* pos){
   Term* previous = pos->prev;//the term before the one to be deleted
   previous->next = pos->next;               
   delete pos;
   pos = previous->next;
   pos->prev = previous;
   size--;
   return true;
}

//---------------------------------------------------------------------------- 
//copy
// A helper method for use in copy constructor and operator=
// calls insert() with currents coefficient and power 
void Polynomial::copy(const Polynomial& p){
   // creates and sets head to 0
   head = new Term;
   head->next = head;
   head->prev = head;
   
   head->coeff = 0.0;
   head->power = 0;
   size = 0;
   
   Term* current = p.head->next; 
   Term* newCurrent = head;
   //walks along Polynomial to be copied
   while(current != p.head){
      insert(newCurrent, current->coeff, current->power);
      newCurrent = newCurrent->next;
      current = current->next;
   }
}

//----------------------------------------------------------------------------
//operator<<
// prints the Polynomial
ostream& operator<<(ostream &output, const Polynomial& p){
   Polynomial::Term* current = p.head;
   
   while(current->next != p.head){
      current = current->next;  
     
      // case to display negative coefficient or head
      if(current->coeff < 0 || current->prev == p.head){
         if(current->coeff == -1){
            if(current->power == 0){
               output << "-1";
            }
            else if(current->power == 1){
               output << "-x";
            }
            else{
               output << "-x^" << current->power;            
            }
         }
         // if head, case to display if the coefficient is 1
         else if(current->coeff == 1){
            if(current->power == 0){
               output << "1";
            }
            else if(current->power == 1){
               output << "x";
            }
            else{
               output << "x^" << current->power;            
            }
         }
         else{
            if(current->power == 0){
               output << current->coeff;
            }
            else if(current->power == 1){
               output << current->coeff << "x";
            }
            else{
               output << current->coeff << "x^" << current->power;       
            }                  
         }
      }
      // case to display if the coefficient is 1
      else if(current->coeff == 1){     
      
         if(current->power == 0){
            output << " + " << "1";
         }
         else if(current->power == 1){
            output << " + " << "x";
         }
         else{
            output << " + " << "x^" << current->power;            
         }
      }
      // can to print any other Term in the Polynomial
      else{         
         if(current->power == 0){
            output << " + " << current->coeff;
         }
         else if(current->power == 1){
            output << " + " << current->coeff << "x";
         }
         else{
            output << " + " << current->coeff << "x^" << current->power;            
         }               
      }  
      
   }
   return output;
}
