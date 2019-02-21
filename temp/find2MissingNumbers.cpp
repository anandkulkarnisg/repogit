#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int findSingleMissingNumber(const int arr[], const size_t& size, const int& maxItem)
{
  long theoraticalSum=(maxItem*(maxItem+1))/2; 
  long sum=0;  
  for(unsigned int i=0; i<size; ++i)
    sum+=arr[i];
  return(theoraticalSum-sum);  
}

long sumOfSquares(const int arr[], const size_t& size)
{
  long squareSum=0;
  for(unsigned int i=0; i<size; ++i)
    squareSum+=(arr[i]*arr[i]);
  return(squareSum);
}

int solveQuadratic(const int& a, const int& b, const int& c)
{
  int sol1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
  int sol2 = (-b - sqrt(b*b - 4*a*c))/(2*a);
   
  if(sol1>sol2)
    return(sol1);
    
  return(sol2);  
}

pair<int, int> findTwoMissingNumbers(const int arr[], const size_t& size, const int& maxItem)
{
  long squareSum=sumOfSquares(arr, size);
  long sum=findSingleMissingNumber(arr, size, maxItem);
  
  long theoraticalSquareSum = maxItem * (maxItem+1) * ((2*maxItem) + 1)/6;
  long missingSquareNum = theoraticalSquareSum - squareSum;      
  
  int result = solveQuadratic(2, -2*sum, (sum*sum)-missingSquareNum);  
  return(make_pair(result, sum-result));
}

int main(int argc, char* argv[])
{
 int arr[] = { 1, 2, 3, 4, 6, 7, 8, 9, 10, 11 }; 
 const size_t size = sizeof(arr)/sizeof(arr[0]); 
 int maxItem=arr[size-1];
 int result=findSingleMissingNumber(arr, size, maxItem);  
 cout << "Missing number is = " << result << endl;
 
 int arr2[] = { 1, 2, 4, 5, 7, 8, 9, 10, 11 };
 const size_t size2 = sizeof(arr2)/sizeof(arr2[0]);
 int maxItem2 = arr[size-1]; 
 pair<int, int> resultPair=findTwoMissingNumbers(arr2, size2, maxItem2);
 int first = resultPair.first;
 int second = resultPair.second;
 int status=(first==0) + (second==0);
 if(status==2)
	cout << "nothing is missing" << endl;
 if(status==1)	
    cout << "only one item is missing" << endl;
 cout << "First missing number = " << resultPair.first << ", second missing number = " << resultPair.second << endl;  
 return(0);  
}
