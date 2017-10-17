// comple with "-std=c++11"

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <math.h>
#include "Eigen/SVD"
#include <algorithm>
#include <functional>
using namespace std;

vector<double*> GetDataofProtein(int m, const char* linkofData){
	int SeqNo;
	int Grp;
	double x,y,z;
	FILE *fp;
	vector<double*> Protein;
	//fp=fopen("../DataSet/Protein1Green","r");
	fp=fopen(linkofData,"r");
	if(fp==NULL)		cout<<"File is not found"<<endl;

	for(int i=0; i<m; i++){
		fscanf(fp,"%d",&SeqNo);
		fscanf(fp,"%d",&Grp);
		fscanf(fp,"%lf",&x);
		fscanf(fp,"%lf",&y);
		fscanf(fp,"%lf",&z);
		Protein.push_back(new double [3]);
		Protein.back()[0]=x;
		Protein.back()[1]=y;
		Protein.back()[2]=z;
	}
	fclose(fp);
	return Protein;
}

int main(){
	const int m=40;
	const int n=63;
	vector<double*> Protein1;
	vector<double*> Protein2;
	Protein1=GetDataofProtein( m, "../DataSet/Protein1Green");
	Protein2=GetDataofProtein( n, "../DataSet/Protein2Green");
	return 0;
}