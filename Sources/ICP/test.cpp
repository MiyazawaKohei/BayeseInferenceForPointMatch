#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include "../Eigen/SVD"
#include <algorithm>
#include <functional>
#include "InitAndFind.h"

static const int dimention = 3;
using namespace std;
int main(){
	Eigen::Matrix<double,3,3> R;
	R(1,2)=1;
	double b=2;
	R(1,2)*=b;
	int i=1;
	vector<double> t(3);
	t[1]=1;
	cout<<R(i,2)*t[i]<<endl;
}