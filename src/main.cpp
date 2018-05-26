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
	else if (dataset=="synthetic") {
		int sketch, arr;
		double start, ends;
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
		for (int i = 11; i <= 20; i += 1) {
			cout << "experiment: a = " << (double)i / 10 << endl;
			ofstream file;
			cout << "type in the file name your data will output(including '.txt')" << endl;
			string file_name;
			cin >> file_name;
			file.open(file_name);
			file << "memory(in KB)  ARE  sigma    AAE    sigma" << endl;
			for (double j = start; j < ends; j += (ends - start) / 10) {
				synthetic_experiment(100000.0, err1,i, j, arr, sig1, sketch, err2, sig2);
				file << j << "  " << err1 << "  " << sig1 << "  " << err2 << "  " << sig2 << endl;
			}
		}
	}
	else {
		cout << "No such dataset exists! Please type in datasets we generate above or modify our functions and use sketches we write here." << endl;
	}
	return 0;
}

