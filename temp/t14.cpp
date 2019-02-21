#include<iostream>
#include<string>

using namespace std;

double& calcalt(double r)
{
	static double alt = (2 * 3.14159 ) * r;
	return alt;
}

double& calculateCircumference(double r)
{
	double result= (2 * 3.14159) * r;
	return result;
}


int main(int argc, char* argv[]) 
{
	//double circumference=calculateCircumference(12.14); // This blows up reference to local variable is wrong.
	double circumference=calcalt(12.14);	 
	cout << "circumference = " << circumference << endl;
}
