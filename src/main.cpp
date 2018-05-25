#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<string>
#include <unordered_map>
#include <fstream>
#include "sac.h"
#include "cmsketch.h"
#include "cusketch.h"
#include "csketch.h"
#include "bobhash.h"
#include "exp.h"
#include "sketch.h"
#include <limits>
#include <time.h>
using namespace std;


//void synthetic_experiment(int number, int memory, double &ret_error, long double &sigma,double &ret_error2,long double &sigma2) {
//	ret_error = 0;
//	ret_error2 = 0;
//	unordered_map<string, int> ump[20];
////	CMSketch *cmsketch[20];
////	CMSketch *cmsketch2[20];
////	CSketch *csketch[20];
////	CSketch *csketch2[20];
//     CUSketch *cusketch[20];
//	 CUSketch *cusketch2[20];
//	double error1[20];
//	double error2[20];
//	memset(error1, 0, sizeof(double) * 20);
//	memset(error2, 0, sizeof(double) * 20);
//	double gamma_2[20] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576,4194304,16777216,67108864,268435456 };
//	//double gamma_2[20] = { 1,6,36,216,1296,7776,46656,279936,1679616,10077696,60466176,362797056,2176782336,13060694016,78364164096 };
//	//double gamma_2[20] = { 1,4,16,64,128,200,300,400,400,400,400,400,400,400,400};
//	int package_num = 0;
//	int	 total_size = 0;
//	ifstream click("0_750.txt", ios::in);
//	char x[20];
//	int cnt = 0;
//	for (int m = 0; m < 5; m++) {
//	//	cmsketch[m] = new CMSketch(memory, 12);
//	//	cmsketch2[m] = new CMSketch(memory/2, 12);
//	//	csketch[m] = new CSketch(memory, 12, 1);
//	//	csketch2[m] = new CSketch(memory/2, 12, 1);
//		cusketch[m]=new CUSketch(memory,12);
//		cusketch2[m] = new CUSketch(memory/2, 12);
//		package_num = 0;
//		total_size = 0;
//		while (click >> x && package_num < number) {
//		//	strcpy(insert[cnt], x);
//			
//		
//				ump[m][(string)x] += 1;
//		//		cmsketch[m]->dynamic_sac_insert(x, 1, gamma_2);
//		//		cmsketch2[m]->Insert(x, 1);
//			//cmsketch[m]->static_sac_insert(x,3,gamma_2);
//			//csketch[m]->static_sac_insert(x,3,gamma_2);
//		//	csketch[m]->asc_insert(x, 1, gamma_2);
//		//	csketch2[m]->Insert(x, 1);
//			cusketch2[m]->Insert(x,1);
//			cusketch[m]->dynamic_sac_insert(x, 1, gamma_2);
//			++cnt;
//			package_num++;
//			/*if (cnt > 2901000)
//				cout << cnt << endl;*/
//
//		}
//		int flow_num = ump[m].size();
//		cout <<m<<" "<< flow_num << endl;
//		unordered_map<string, int>::iterator it1;
//		for (it1 = ump[m].begin(); it1 != ump[m].end(); ++it1) {
//			//cmsketch[m]->check(it1->first.c_str(), gamma_2);
//			//cout << "**********************************" << endl;
//		//	error1[m] += abs(csketch[m]->asc_query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//			//error1[m]+=abs(csketch[m]->fixed_Asc_Query(it1->first.c_str(),?,gamma_2)-it1->second)/(double)it1->second;
//	        error1[m] += abs(cusketch[m]->dynamic_sac_query(it1->first.c_str(),gamma_2) - it1->second) / (double)it1->second;
//			error2[m] += abs(cusketch2[m]->Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//			//error1[m]+=abs(cmsketch[m]->fixed_Asc_Query(it1->first.c_str(),?,gamm_2)-it1->second)/(double)it1->second;
//		//	error1[m] += abs(cmsketch[m]->asc_Query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//			//error2[m] += abs(cmsketch2[m]->int_Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//		//	error2[m] += abs(csketch2[m]->Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//
//		}
//		error1[m] /= flow_num;
//		error2[m] /= flow_num;
//	}
//	//cout << cnt << endl;
//
//
//	sigma = 0;
//	sigma2 = 0;
//	for (int m = 0; m<5; ++m) {
//		ret_error += error1[m];
//		ret_error2 += error2[m];
//	}
//
//	ret_error /= 5;
//	ret_error2 /= 5;
//	for (int m = 0; m<5; ++m) {
//		sigma += pow(error1[m] - ret_error, 2);
//		sigma2 += pow(error2[m] - ret_error2, 2);
//	}
//	sigma = sqrt(sigma / 4);
//	sigma2 = sqrt(sigma2 / 4);
//}

//void error_click_experiment(int number, int memory, double &ret_error, long double &sigma, double &ret_error2, long double &sigma2) {
//	ret_error = 0;
//	ret_error2 = 0;
//	unordered_map<string, int> ump[20];
//	//CMSketch *cmsketch[20];
//	//CMSketch *cmsketch2[20];
//	CSketch *csketch[20];
//	CSketch *csketch2[20];
//	//CUSketch *cusketch[20];
//	//CUSketch *cusketch2[20];
//	double error1[20];
//	double error2[20];
//	memset(error1, 0, sizeof(double) * 20);
//	memset(error2, 0, sizeof(double) * 20);
//	double gamma_2[20] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576,4194304,16777216,67108864,268435456 };
//	//double gamma_2[20] = { 1,6,36,216,1296,7776,46656,279936,1679616,10077696,60466176,362797056,2176782336,13060694016,78364164096 };
//	int package_num = 0;
//	int total_size = 0;
//	ifstream click("click.txt", ios::in);
//	char x[20];
//	int cnt = 0;
//	for (int m = 0; m < 10; m++) {
//		//cmsketch[m] = new CMSketch(memory, 12);
//		//cmsketch2[m] = new CMSketch(memory/2, 12);
//		csketch[m] = new CSketch(memory, 12);
//		csketch2[m] = new CSketch(memory, 12);
//		//cusketch[m]=new CUSketch(memory,12);
//		//cusketch2[m] = new CUSketch(memory/2, 12);
//		package_num = 0;
//		total_size = 0;
//		while (click >> x && package_num < number) {
//			//strcpy(insert[cnt], x);
//			ump[m][(string)x] += 1;
//			//cmsketch[m]->asc_Insert(x, 1, gamma_2);
//			//cmsketch2[m]->int_Insert(x, 1);
//			csketch[m]->dynamic_sac_insert(x, 1, gamma_2);
//			csketch2[m]->Insert(x, 1);
//			//cusketch2[m]->int_Insert(x, 1);
//			//cusketch[m]->sac_insert(x, 1, gamma_2);
//			++cnt;
//			package_num++;
//
//		}
//		int flow_num = ump[m].size();
//		cout << m << " " << flow_num << endl;
//		unordered_map<string, int>::iterator it1;
//		for (it1 = ump[m].begin(); it1 != ump[m].end(); ++it1) {
//			//if(it1->first!="1"&&(it1->first!="2")&&(it1->first!="3"))
//			//cout << cmsketch->int_Query(it1->first.c_str()) << " " << it1->second << endl;
//		//	error1[m] += abs(csketch[m]->asc_query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//			//error1[m] += abs(cusketch[m]->type_Query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//		//	error1[m] += abs(cmsketch[m]->asc_Query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//		//	error2[m] += abs(cmsketch2[m]->int_Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//	//		error2[m] += abs(csketch2[m]->Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//			//error1[m] += abs(cusketch[m]->sac_query(it1->first.c_str(), gamma_2) - it1->second) / (double)it1->second;
//			//error2[m] += abs(cusketch2[m]->Query(it1->first.c_str()) - it1->second) / (double)it1->second;
//		}
//		/*error1[m] += (abs(csketch[m]->asc_query("1", gamma_2) - ump[m]["1"])) / (double)ump[m]["1"];
//		error1[m] += (abs(csketch[m]->asc_query("2", gamma_2) - ump[m]["2"])) / (double)ump[m]["2"];
//		error1[m] += (abs(csketch[m]->asc_query("3", gamma_2) - ump[m]["3"])) / (double)ump[m]["3"];
//		error2[m] += (abs(csketch2[m]->Query("1") - ump[m]["1"])) / (double)ump[m]["1"];
//		error2[m] += (abs(csketch2[m]->Query("2") - ump[m]["2"])) / (double)ump[m]["2"];
//		error2[m] += (abs(csketch2[m]->Query("3") - ump[m]["3"])) / (double)ump[m]["3"];*/
//		/*error1[m] += (abs(cmsketch[m]->asc_Query("1", gamma_2) - ump[m]["1"])) / (double)ump[m]["1"];
//		error1[m] += (abs(cmsketch[m]->asc_Query("2", gamma_2) - ump[m]["2"])) / (double)ump[m]["2"];
//		error1[m] += (abs(cmsketch[m]->asc_Query("3", gamma_2) - ump[m]["3"])) / (double)ump[m]["3"];
//		error2[m] += (abs(cmsketch2[m]->int_Query("1") - ump[m]["1"])) / (double)ump[m]["1"];
//		error2[m] += (abs(cmsketch2[m]->int_Query("2") - ump[m]["2"])) / (double)ump[m]["2"];
//		error2[m] += (abs(cmsketch2[m]->int_Query("3") - ump[m]["3"])) / (double)ump[m]["3"];*/
//	//	}
//		error1[m] /= flow_num;
//		error2[m] /= flow_num;
//	}
//	cout << cnt << endl;
//
//
//	sigma = 0;
//	
//	sigma2 = 0;
//	for (int m = 0; m<10; ++m) {
//		ret_error += error1[m];
//		ret_error2 += error2[m];
//		
//	}
//
//	ret_error /= 10;
//	ret_error2 /= 10;
//	
//	for (int m = 0; m<10; ++m) {
//		sigma += pow(error1[m] - ret_error, 2);
//		sigma2 += pow(error2[m] - ret_error2, 2);
//		
//	}
//	sigma = sqrt(sigma / 9);
//	sigma2 = sqrt(sigma2 / 9);
//}

int main()
{
	greeting();
	string dataset;
	cin >> dataset;
	if (dataset == "CAIDA") {
		int sketch,arr,start,ends;
		cout << "type 0~5 for 'CM','CU','C','SACCM','SACCU' or 'SACC' sketches" << endl;
		cin >> sketch;
		cout << "type in number of arrays in sketch(type 0 for default setting" << endl;
		cin >> arr;
		if (arr == 0)
			arr = 12;
		cout << "type in the range of memory usage(in KB)" << endl;
		cout << "from:" << endl;
		cin >> start;
		cout << "to:" << endl;
		cin >> ends;
		double err1,err2;
		long double sig1,sig2;
		ofstream file;
		cout << "type in the file name your data will output(including '.txt')" << endl;
		string file_name;
		cin >> file_name;
		file.open(file_name);
		file << "memory(in KB)  ARE  sigma    AAE    sigma" << endl;
		for (int i = start; i < ends; i += (ends - start) / 12) {
			CAIDA_experiment(28000099.0, err1, i, arr, sig1, sketch,err2,sig2);
			file << i << "  " << err1 << "  " << sig1<<"  "<<err2<<"  "<<sig2 << endl;
		}
	}
	else if (dataset == "webpage") {
		int sketch, arr, start, ends;
		cout << "type 0~5 for 'CM','CU','C','SACCM','SACCU' or 'SACC' sketches" << endl;
		cin >> sketch;
		cout << "type in number of arrays in sketch(type 0 for default setting" << endl;
		cin >> arr;
		if (arr == 0)
			arr = 12;
		cout << "type in the range of memory usage(in KB)" << endl;
		cout << "from:" << endl;
		cin >> start;
		cout << "to:" << endl;
		cin >> ends;
		double err1, err2;
		long double sig1, sig2;
		ofstream file;
		cout << "type in the file name your data will output(including '.txt')" << endl;
		string file_name;
		cin >> file_name;
		file.open(file_name);
		file << "memory(in KB)  ARE  sigma    AAE    sigma" << endl;
		for (int i = start; i < ends; i += (ends - start) / 10) {
			webpage_experiment(100000, err1, i, arr, sig1, sketch, err2, sig2);
			file << i << "  " << err1 << "  " << sig1 << "  " << err2 << "  " << sig2 << endl;
		}
	}
	return 0;
}

