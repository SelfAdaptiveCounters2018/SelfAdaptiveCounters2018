#pragma once 
#include <algorithm>
#include <cstring>
#include "sketch.h"
#include <string.h>
#include "bobhash.h"
#include "sac.h"
#include <iostream>
using namespace std;
class CMSketch:public class_sketches{
private:
    BOBHash *bobhash[20];
    int index[20];
    long_sign *counter[20];
    int *int_counter[20];
    int w,d;
    int MAX_CNT=2147483647;
    int counter_index_size;
    uint64_t hash_value;
public:
    CMSketch(int _w,int _d){ //w is the size of the hash area, d is the number of hash functions in the Mediean trick
        counter_index_size = 20;
                w = _w;
                d = _d;

                for(int i = 0; i < d; i++)
                {
                    counter[i] = new long_sign[w];
                    memset(counter[i], 0, sizeof(long_sign) * w);
                    bobhash[i] = new BOBHash(i + 1000);

                    int_counter[i] = new int[w];
                    memset(int_counter[i], 0, sizeof(int) * w);
                }
    }
	void Insert(const char *str, int c) {
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			if (int_counter[i][index[i]] + c <= MAX_CNT) {
				int_counter[i][index[i]] += c;
			}
		}
	}
	int Query(const char *str) {
		int min_value = MAX_CNT;
		int temp;

		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = int_counter[i][index[i]];
			min_value = temp < min_value ? temp : min_value;
		}
		return min_value;
	}
    void dynamic_sac_insert(const char *str,int c,double *gamma){
        for(int i = 0; i < d; i++){
            index[i] = (bobhash[i]->run(str, strlen(str))) % w;
            adding(counter[i][index[i]],c,gamma);
        }
    }
	int dynamic_sac_query(const char *str, double *gamma)
	{
		long_sign min_value = long_maxi;
		long_sign temp;

		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = counter[i][index[i]];
			min_value = min(min_value, temp);
		}
		return predict(min_value, gamma);

	}
	void static_sac_insert(const char *str,int l_sign, double *gamma) {
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			add_one(counter[i][index[i]],l_sign, gamma);
		}
	}	
	int static_sac_query(const char *str,int l_sign, double *gamma)
	{
		long_sign min_value = long_maxi;
		long_sign temp;

		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = counter[i][index[i]];
			min_value = min(min_value, temp);
		}
		return predict(min_value,l_sign, gamma);

	} 
	void check(const char *str, double *gamma) {
		int temp;
		int result[22];
		cout << "[[";
		//check str's correspond hash table content
		for (int i = 0; i<d; ++i) {
			int pos = (bobhash[i]->run(str, strlen(str))) % w;
			result[i] = abs(predict(counter[i][pos], gamma));

		}
		//sort(result, result + d);
		for (auto x : result)cout << x << " ";
		cout << "]]" << endl;
	}
};

 // CMSKETCH_H
