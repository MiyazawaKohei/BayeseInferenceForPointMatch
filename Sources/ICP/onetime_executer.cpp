// comple with "-std=c++11"

#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include "../Eigen/SVD"
#include <algorithm>
#include <functional>
#include "InitAndFind.h"
using namespace std;

int main(int argc,char* argv[]){


	int n_a, n_b; //The number of the vectors of A, B
	n_a=stoi(argv[1]);
	n_b=stoi(argv[2]);
	double SDofnoise=(argc==3?-1:stod(argv[3]));
	vector<double*> A,B;
	B=Init_Vectors_inB(n_b);
	cout<<"B:"<<endl;
	for(int i=0; i<n_b;i++)		cout<<B[i][0]<<","<<B[i][1]<<","<<B[i][2]<<endl;
	vector<vector<double>> rotation=Create_Random_Rotation_Matrix();
	vector<int> permutation=Create_Random_Permutaiton(n_b);

	A=Init_Vectors_inA(B,rotation,permutation,n_a,SDofnoise);
	vector<int> permutationcut(n_a,0);
	for(int i=0; i<n_a; i++) permutationcut[i]=permutation[i];
	Eigen::Matrix<double,3,3> R;
	vector<double> v(3);
	cout<<"Minimized_RMSD:"<<Minimize_RMSD(A,B,permutationcut,&R,&v)<<endl;
	vector<double*> Dmatrix;
	for(int i=0; i<B.size();i++){
		Dmatrix.push_back(new double [B.size()]);
		for(int j=0; j<B.size(); j++)		Dmatrix.back()[j]=0;
	}
	Make_Distance_Matrix(&Dmatrix,A,B,&R,&v);
	for(int i=0; i<B.size();i++){
		for(int j=0; j<B.size(); j++){
			cout<<Dmatrix[i][j]<<",";
		}
		cout<<endl;
	}
	//Find_Minimizing_Permutation(A,B);
	Close_Vectors(A);
	Close_Vectors(B);

}

