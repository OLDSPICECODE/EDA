#include <iostream>
#include<stdlib.h>
//3.3
// Class CVector definition
class CVector{
  private:
    int *m_pVect, // Pointer to the buffer
    m_nCount, // Control how many elements are actually used
    m_nMax, // Control how many are allocated as maximum
    m_nDelta; // To control the growing
    void Init(int delta); // Init our private variables, etc
    void Resize(); // Resize the vector when occurs an overflow
  public:
    CVector(int delta = 10); // Constructor
    void Insert(int elem); // Insert a new element
  // More methods go here
};

void CVector::Insert(int elem)
{
  if( m_nCount == m_nMax ) // Verify the overflow
    Resize(); // Resize the vector before inserting elem
  m_pVect[m_nCount++] = elem; // Insert the element at the end
}
//3.2
struct Vector{
  int*m_pVect, 
  m_nCount, 
  m_nMax,
  m_nDelta;

};
void Resize(Vector *pThis,int gpVect[])
  {
    pThis->m_pVect = (int*)realloc(gpVect, sizeof(int) * (pThis->m_nMax + pThis->m_nDelta));
    pThis->m_nMax += pThis->m_nDelta;
  }
  void Insert(Vector *pThis, int elem,int gpVect[])
  {
    if( pThis->m_nCount == pThis->m_nMax ) // Verify the overflow
    Resize(pThis,gpVect); // Resize the vector before inserting elem
    // Insert the element at the end of the sequence
    pThis->m_pVect[pThis->m_nCount++] = elem;
  }
  

//3,1,2
/*void Resize(int gpVect[],int gnMax)
{
 const int delta = 10; // Used to increase the vector size
  gpVect = (int *)realloc(gpVect, sizeof(int) * (gnMax + delta));
} 

void Insert_1(int elem,int &gnMax,int &gnCount,int gpVect[])
{
  if( gnCount == gnMax ) // There is no space at this moment for elem
  Resize(gpVect,gnMax); // Resize the vector before inserting elem
  gpVect[gnCount++] = elem; // Insert the element at the end of the sequence
}
//3.1.1
void Insert(int elem,int &gnCount,int gVect[]){
  if( gnCount < 100 ) // we can only insert if there is space
    gVect[gnCount++] = elem; // Insert the element at the end
}
*/

int main() {
  //3.1
  int gVect[100]; 
  int gnCount = 0;
  /*Insert(3,gnCount,gVect);
  for(int i =0;i<gnCount;i++){
    std::cout<<gVect[i]<<std::endl;
  }*/
  //3.2
  int *gpVect = NULL; 
  /*gnCount = 0; 
  int gnMax = 0;
  Insert_1(3,gnMax,gnCount,gpVect);
  for(int i=0;i<gnCount;i++){
    std::cout<<*(gpVect+1)<<std::endl;
  }*/
  //3.2
  Vector *v1;
  Insert(v1,3,gpVect);
  //3.3
  CVector *v2;
}
