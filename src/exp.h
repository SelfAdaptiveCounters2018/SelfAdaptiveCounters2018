#pragma once

#include <iostream>
#include <math.h>
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <fstream>
#include "sac.h"
#include "cmsketch.h"
#include "cusketch.h"
#include "csketch.h"
#include "bobhash.h"
#include <limits>
#include <time.h>
using namespace std;
char insert[9999998][20];
char five_tuple[9999998][15];
int package_length[9999998];
char query[9999998][20];
double memory = 1.0;
int w = memory * 100000;
CMSketch *cmsketch = new CMSketch(1.5*w, 12);
CUSketch *cusketch = new CUSketch(1.5*w, 12);

double re[810];
int counter[810];


void CAIDA_experiment(int number, double &ret_error, double n, int m, long double &sigma, int sketch, double &ret_aae, long double &aae_sig) { 
	//n is the memory size(in KB) and m is the number of arrays used in the sketch
	cout << "your sketch number is: " << sketch << " (0~5 for 'CM', 'CU', 'C', 'SACCM', 'SACCU' or 'SACC' sketches)" << endl;
	class_sketches* s[20];
	if (sketch == 0) {
		
		for (int i = 0; i < 12; ++i) {
			s[i] = new CMSketch(n * 1024 / 4 / m, m);
		}
		cout << "CMSketch with " << n << "KB hash memory generated!" << endl;
		
	}
	if (sketch == 1) {
		for (int i = 0; i < 12; ++i) {
			s[i] = new CUSketch(n * 1024 / 4 / m, m);
		}
		cout << "CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 2) {
		for (int i = 0; i < 12; ++i) {
			s[i] = new CSketch(n * 1024 / 4 / m, m);
		}
		cout << "CSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 3) {
		for (int i = 0; i < 12; ++i) {
			s[i] = new CMSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CMSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 4) {
		for (int i = 0; i < 12; ++i) {
			s[i] = new CUSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch  == 5) {
		for (int i = 0; i < 12; ++i) {
			s[i] = new CSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CSketch with " << n << "KB hash memory generated!" << endl;
	}


	unordered_map<string, int> unmp[20];

	double gamma_2[20] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576,4194304,16777216,67108864,268435456 };
	int package_num = 0;
	int total_size = 0;
	double error[20];
	double error_aae[20];
	char filename[15];
	memset(filename, 0, sizeof(char)*15);

	sprintf(filename, "CAIDA.dat", 0);

	FILE *file_stream = fopen(filename, "rb");

	for (int m = 0; m<12; ++m) {
		package_num = 0;
		total_size = 0;

		while (fread(insert[package_num], 1, 15, file_stream) && total_size< number) {

			for (int i = 0; i<13; ++i) {
				five_tuple[package_num][i] = insert[package_num][i];
			}
			package_length[package_num] = (unsigned char)insert[package_num][13] * 256 + (unsigned char)insert[package_num][14];

			unmp[m][string(five_tuple[package_num])] += package_length[package_num];

			total_size += package_length[package_num];
			++package_num;
		}

		//cout<<"total size="<<total_size<<endl;
	}
	fclose(file_stream);

	for (int m = 0; m<12; ++m) {
		int max_freq = 0;
		unordered_map<string, int>::iterator it = unmp[m].begin();

		for (int i = 0; i < unmp[m].size(); i++, it++)
		{
			strcpy(query[i], it->first.c_str());

			int temp2 = it->second;

			max_freq = max_freq > temp2 ? max_freq : temp2;
		}

		//cout<<"loading complete and max_freq="<<max_freq<<endl;
		//cout<<"total size="<<total_size<<endl;
		//cout<<"package_number="<<package_num<<endl;
		unordered_map<string, int>::iterator it1;
		for (it1 = unmp[m].begin(); it1 != unmp[m].end(); ++it1) {
			
			if (sketch <= 2)
				s[m]->Insert(it1->first.c_str(), it1->second);
			else
				s[m]->dynamic_sac_insert(it1->first.c_str(), it1->second, gamma_2);

		}

		for (int i = 0; i<810; ++i) {
			re[i] = 0;
			counter[i] = 0;
		}

		int flow_num = unmp[m].size();
		unordered_map<string, int>::iterator it2;

		error[m] = 0;
		error_aae[m] = 0;
		for (it2 = unmp[m].begin(); it2 != unmp[m].end(); ++it2) {
			if (sketch <= 2) {
				error[m] += abs(s[m]->Query(it2->first.c_str()) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->Query(it2->first.c_str()) - it2->second);
			}
			else
			{
				error[m] += abs(s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second);
			}
		}
		error[m] /= flow_num;
		error_aae[m] /= flow_num;
	}
	ret_error = 0;
	sigma = 0;
	ret_aae = 0;
	aae_sig = 0;
	for (int m = 0; m<12; ++m) {
		ret_error += error[m];
		ret_aae += error_aae[m];
	}

	ret_error /= 12;
	ret_aae /= 12;
	for (int m = 0; m<12; ++m) {
		sigma += pow(error[m] - ret_error, 2);
		aae_sig += pow(error_aae[m] - ret_aae, 2);
	}
	sigma = sqrt(sigma / 11);
	aae_sig = sqrt(aae_sig / 11);
}

void webpage_experiment(int number, double &ret_error, double n, int m, long double &sigma, int sketch, double &ret_aae, long double &aae_sig) { 
	//n is the memory size(in KB) and m is the number of arrays used in the sketch
	cout << "your sketch number is: " << sketch << " (0~5 for 'CM', 'CU', 'C', 'SACCM', 'SACCU' or 'SACC' sketches)" << endl;
	class_sketches* s[20];
	if (sketch == 0) {

		for (int i = 0; i < 10; ++i) {
			s[i] = new CMSketch(n * 1024 / 4 / m, m);
		}
		cout << "CMSketch with " << n << "KB hash memory generated!" << endl;

	}
	if (sketch == 1) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CUSketch(n * 1024 / 4 / m, m);
		}
		cout << "CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 2) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CSketch(n * 1024 / 4 / m, m);
		}
		cout << "CSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 3) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CMSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CMSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 4) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CUSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 5) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CSketch with " << n << "KB hash memory generated!" << endl;
	}


	unordered_map<string, int> unmp[20];

	double gamma_2[20] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576,4194304,16777216,67108864,268435456 };
	int package_num = 0;
	int total_size = 0;
	double error[20];
	double error_aae[20];
	char filename[15];
	memset(filename, 0, sizeof(char) * 15);

	sprintf(filename, "webpage.txt", 0);

	ifstream file_read(filename,ios::in);
	char tmp_read[20];
	for (int m = 0; m<10; ++m) {
		total_size = 0;
		while (file_read>>tmp_read && total_size< number) {
			unmp[m][(string)tmp_read] += 1;
			++total_size ;		
		}
		//cout<<"total size="<<total_size<<endl;
	}
	for (int m = 0; m<10; ++m) {
		int max_freq = 0;
		unordered_map<string, int>::iterator it = unmp[m].begin();

		for (int i = 0; i < unmp[m].size(); i++, it++)
		{
			int temp2 = it->second;
			max_freq = max_freq > temp2 ? max_freq : temp2;
		}
		//cout<<"loading complete and max_freq="<<max_freq<<endl;
		//cout<<"total size="<<total_size<<endl;
		unordered_map<string, int>::iterator it1;
		for (it1 = unmp[m].begin(); it1 != unmp[m].end(); ++it1) {
			if (sketch <= 2)
				s[m]->Insert(it1->first.c_str(), it1->second);
			else
				s[m]->dynamic_sac_insert(it1->first.c_str(), it1->second, gamma_2);

		}

		int flow_num = unmp[m].size();
		unordered_map<string, int>::iterator it2;

		error[m] = 0;
		error_aae[m] = 0;
		for (it2 = unmp[m].begin(); it2 != unmp[m].end(); ++it2) {
			if (sketch <= 2) {
				error[m] += abs(s[m]->Query(it2->first.c_str()) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->Query(it2->first.c_str()) - it2->second);
			}
			else
			{
				error[m] += abs(s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second);
			}
		}
		error[m] /= flow_num;
		error_aae[m] /= flow_num;
	}
	ret_error = 0;
	sigma = 0;
	ret_aae = 0;
	aae_sig = 0;
	for (int m = 0; m<10; ++m) {
		ret_error += error[m];
		ret_aae += error_aae[m];
	}

	ret_error /= 10;
	ret_aae /= 10;
	for (int m = 0; m<10; ++m) {
		sigma += pow(error[m] - ret_error, 2);
		aae_sig += pow(error_aae[m] - ret_aae, 2);
	}
	sigma = sqrt(sigma / 9);
	aae_sig = sqrt(aae_sig / 9);
}


void synthetic_experiment(int number, double &ret_error,int a_zipf, double n, int m, long double &sigma, int sketch, double &ret_aae, long double &aae_sig) {
	//a is the skewness parameter of Zipf distribution, n is the memory size(in KB) and m is the number of arrays used in the sketch
	cout << "your sketch number is: "<<sketch << " (0~5 for 'CM', 'CU', 'C', 'SACCM', 'SACCU' or 'SACC' sketches)" << endl;
	class_sketches* s[20];
	if (sketch == 0) {

		for (int i = 0; i < 10; ++i) {
			s[i] = new CMSketch(n * 1024 / 4 / m, m);
		}
		cout << "CMSketch with " << n << "KB hash memory generated!" << endl;

	}
	if (sketch == 1) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CUSketch(n * 1024 / 4 / m, m);
		}
		cout << "CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 2) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CSketch(n * 1024 / 4 / m, m);
		}
		cout << "CSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 3) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CMSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CMSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 4) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CUSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CUSketch with " << n << "KB hash memory generated!" << endl;
	}
	if (sketch == 5) {
		for (int i = 0; i < 10; ++i) {
			s[i] = new CSketch(n * 1024 / 2 / m, m);
		}
		cout << "SAC CSketch with " << n << "KB hash memory generated!" << endl;
	}


	unordered_map<string, int> unmp[20];

	double gamma_2[20] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576,4194304,16777216,67108864,268435456 };
	int package_num = 0;
	int total_size = 0;
	double error[20];
	double error_aae[20];
	char filename[15];
	memset(filename, 0, sizeof(char) * 15);

	sprintf(filename, "%d.txt", a_zipf);

	ifstream file_read(filename, ios::in);
	char tmp_read[20];
	for (int m = 0; m<10; ++m) {
		total_size = 0;
		while (file_read >> tmp_read && total_size< number) {
			unmp[m][(string)tmp_read] += 1;
			++total_size;
		}
		//cout<<"total size="<<total_size<<endl;
	}
	for (int m = 0; m<10; ++m) {
		int max_freq = 0;
		unordered_map<string, int>::iterator it = unmp[m].begin();

		for (int i = 0; i < unmp[m].size(); i++, it++)
		{
			int temp2 = it->second;
			max_freq = max_freq > temp2 ? max_freq : temp2;
		}
		//cout<<"loading complete and max_freq="<<max_freq<<endl;
		//cout<<"total size="<<total_size<<endl;
		unordered_map<string, int>::iterator it1;
		for (it1 = unmp[m].begin(); it1 != unmp[m].end(); ++it1) {
			if (sketch <= 2)
				s[m]->Insert(it1->first.c_str(), it1->second);
			else
				s[m]->dynamic_sac_insert(it1->first.c_str(), it1->second, gamma_2);

		}

		int flow_num = unmp[m].size();
		unordered_map<string, int>::iterator it2;

		error[m] = 0;
		error_aae[m] = 0;
		for (it2 = unmp[m].begin(); it2 != unmp[m].end(); ++it2) {
			if (sketch <= 2) {
				error[m] += abs(s[m]->Query(it2->first.c_str()) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->Query(it2->first.c_str()) - it2->second);
			}
			else
			{
				error[m] += abs(s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second) / (double)it2->second;
				error_aae[m] += abs((double)s[m]->dynamic_sac_query(it2->first.c_str(), gamma_2) - it2->second);
			}
		}
		error[m] /= flow_num;
		error_aae[m] /= flow_num;
	}
	ret_error = 0;
	sigma = 0;
	ret_aae = 0;
	aae_sig = 0;
	for (int m = 0; m<10; ++m) {
		ret_error += error[m];
		ret_aae += error_aae[m];
	}

	ret_error /= 10;
	ret_aae /= 10;
	for (int m = 0; m<10; ++m) {
		sigma += pow(error[m] - ret_error, 2);
		aae_sig += pow(error_aae[m] - ret_aae, 2);
	}
	sigma = sqrt(sigma / 9);
	aae_sig = sqrt(aae_sig / 9);
}