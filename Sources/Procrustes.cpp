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

int main(){
	const int m=40;
	const int n=63;

	int SeqNo;
	int Grp;
	double x,y,z;
	FILE *fp;

	fp=fopen("../DataSet/Protein1Green","r");
	if(fp==NULL)	return EXIT_FAILURE;

	for(int i=0; i<m; i++){
		fscanf(fp,"%d",&SeqNo);
		fscanf(fp,"%d",&Grp);
		fscanf(fp,"%lf",&x);
		fscanf(fp,"%lf",&y);
		fscanf(fp,"%lf",&z);
		cout<<x<<y<<z<<endl;
	}
	fclose(fp);
	return 0;
}