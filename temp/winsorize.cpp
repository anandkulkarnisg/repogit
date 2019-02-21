#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

template<typename T> void printArrayToConsole(const vector<T>& inputArr)
{
  size_t size=inputArr.size();
  for(unsigned long i=0; i<size-1; ++i)
    cout << inputArr[i] << " , ";
  cout << inputArr[size-1] << '\n';
}

template<typename T> void winsorizeInternal(vector<T>& arr, const float& winsorizeSize)
{
  vector<int> inputData(arr);
  sort(inputData.begin(), inputData.end());

  float upperPercentileBound=100-winsorizeSize;
  float lowerPercentileBound=winsorizeSize;

  float upperIdx=round((static_cast<float>(upperPercentileBound)/static_cast<float>(100))*static_cast<float>(inputData.size()))-1;
  float lowerIdx=round((static_cast<float>(lowerPercentileBound)/static_cast<float>(100))*inputData.size());
  if(lowerIdx<0)
    lowerIdx=0;

  int upperPercentile=inputData[upperIdx];
  int lowerPercentile=inputData[lowerIdx];

  cout << "debug : " << upperIdx << ", " << lowerIdx << endl;
  cout << "debug : " << upperPercentileBound << ", " << lowerPercentileBound << endl;

  if(upperPercentileBound==lowerPercentileBound || upperPercentileBound<lowerPercentileBound)
    upperPercentile=lowerPercentile;

  for(unsigned int i=0; i<arr.size(); ++i)
  {
    if(arr[i]<lowerPercentile)
      arr[i]=lowerPercentile;
    else
    {
      if(arr[i]>upperPercentile)
        arr[i]=upperPercentile;
    }
  }
}

template<typename T> void winsorize(vector<T>& arr, const string& winsorizeSize)
{
  // Ex:- winsorize parameter passed as absolute value, i.e 0.05 [ absolute not percent)
  winsorizeInternal(arr, stof(winsorizeSize)*100);
}

template<typename T> void winsorize(vector<T>& arr, const float& winsorPercent)
{
  // Ex:- a 90% winsorization means (100-90)/2, rather saying that we cut outliers beyond 5% on lower end and 95% on the higher end.
  winsorizeInternal(arr, (100-winsorPercent)/200.0);
}


int main(int argc, char* argv[])
{
  vector<int> originalData = { 92, 19, 101, 58, 1053, 91, 26, 78, 10, 13, -40, 101, 86, 85, 15, 89, 89, 28, -5, 41};  
  string winsor;
  // TODO partial k sort rather than full sort to reduce the complexity to O(kn) than O(nlog(n))
  if(argc==1)
    winsor="0";
  else
    winsor=argv[1]; 
  winsorize(originalData, winsor);
  printArrayToConsole(originalData);
  return(0);
}
