/*
 * main.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>
#include<vector>

using namespace std;

extern void basicLinkedListDemo();
extern void extraExamplesDemo();
extern void demoInsertionSort();
extern void demobubbleSort();
extern void demoselectionSort();
extern void demoquickSort();
extern void demoheapSort();
extern void demomergeSort();
extern void deleteatEndTestDemo();
extern void demoShellSort();

void linkedListDemo() {

	basicLinkedListDemo();
	extraExamplesDemo();
	deleteatEndTestDemo();
}


void runSortDemo() {
		demoInsertionSort();
		demobubbleSort();
		demoselectionSort();
		demoquickSort();
		demoheapSort();
		demomergeSort();
		demoShellSort();
}


std::string solution(const vector<vector<int>>& vecItems, const vector<vector<int>> subVecItems,
                     const int& R, const int& C, const int& r, const int& c)
{

    int A[R][C];
    int B[r][c];
    vector<int> vecItem;
    vecItem.reserve(C);

    for(unsigned int i=0; i<R; ++i)
    {
        vecItem = vecItems[i];
        for(unsigned int j=0; j<C; ++j)
        {
            A[i][j] = vecItem[j];
        }
    }

    vecItem.reserve(c);

    for(unsigned int i=0; i<r; ++i)
    {
        vecItem = subVecItems[i];
        for(unsigned int j=0; j<c; ++j)
        {
            B[i][j] = vecItem[j];
        }
    }

    // First pick the edge items of the submatrix.
    int leftTop =  B[0][0];
    int rightTop = B[0][c-1];
    int leftBottom = B[r-1][0];
    int rightBottom = B[r-1][c-1];

    for(unsigned int i=0; i<R; ++i)
    {
        for(unsigned int j=0; j<C; ++j)
        {
            if(A[i][j] == leftTop)
            {
               if(R >= (i+r-1) && C>= (j+c-1))
                {
                    if(A[i][j+c-1] == rightTop && A[i+r-1][j] == leftBottom && A[i+r-1][j+c-1] == rightBottom)
                    {
                        bool isSame = true;
                        int r = 0;
                        int s = 0;

                        for(unsigned int p=i; p<=i+r-1; ++p)
                        {
                            for(unsigned int q=j; q<=j+c-1; ++q)
                            {
                                cout << "comparing the items" << A[p][q] << " and " << B[r][s] << endl;
                                if(A[p][q] != B[r][s])
                                  {
                                      isSame=false;
                                  }
                               s++;
                            }
                           r++;
                        }

                        if(isSame)
                            return("YES");
                    }

                }
            }
        }
    }

 return("NO");

}




void dsearch()
{

    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++)
    {
        int R;
        int C;
        std::string temp;
        cin >> R >> C;

        vector<vector<int>> vecItems;
        vecItems.reserve(R);

        vector<int> vecItem;
        vecItem.reserve(C);

        for(unsigned int i=0; i<R; ++i)
        {
            vecItem.erase(vecItem.begin(), vecItem.end());
            cin >> temp;
            for(unsigned int j=0; j<C; ++j)
            {
                vecItem.push_back(temp[j]-'0');
            }
            vecItems.push_back(vecItem);
        }

        int r, c;
        cin >> r >> c;
        vector<vector<int>> subVecItems;
        subVecItems.reserve(r);
        vecItem.erase(vecItem.begin(), vecItem.end());
        vecItem.reserve(c);

        for(unsigned int i=0; i<r; ++i)
        {
            vecItem.erase(vecItem.begin(), vecItem.end());
            cin >> temp;
            for(unsigned int j=0; j<c; ++j)
            {
                vecItem.push_back(temp[j]-'0');
            }
            subVecItems.push_back(vecItem);
        }

        std::string result = solution(vecItems, subVecItems, R, C, r, c);
        cout << result << endl;
    }


}


int main(int argc, char* argv[]) {

	//linkedListDemo();
	//runSortDemo();
	dsearch();
	return (0);

}
