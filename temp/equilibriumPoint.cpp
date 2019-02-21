int solution(vector<int> &A) 
{
std::size_t size = A.size();
if(size == 0)
    return(-1);    

long long sum = 0;
for(auto iter : A)
    sum +=iter;

long long leftSum=0;
long long rightSum=0;
vector<int> equilibriumIndexPositions;
equilibriumIndexPositions.reserve(size);

if((sum - A[0]) == 0)
 equilibriumIndexPositions.push_back(0);

for(unsigned int i=1; i<size; ++i)
{ 
 leftSum += A[i-1];
 rightSum = sum - leftSum - A[i];
 if(leftSum == rightSum)
      equilibriumIndexPositions.push_back(i);
}

if(equilibriumIndexPositions.size() == 0)
    return(-1);
else
    return(equilibriumIndexPositions[0]);
}    
