#pragma once
#include "sac.h"
#include <algorithm>
#include <cstring>
#include <string.h>
#include "bobhash.h"
#include "sketch.h"
#include <iostream>

using namespace std;

class CUSketch:public class_sketches
{
private:
    BOBHash * bobhash[20];
    int index[20];
    long_sign *sac_counter[20];
    int *counter[20];
    int w, d;
    int MAX_CNT=2000;
	int MAX_COUNT = 2147483647;
    int counter_index_size;
    uint64_t hash_value;

public:
    CUSketch(int _w, int _d)
    {
        counter_index_size = 20;
        w = _w;
        d = _d;

        for(int i = 0; i < d; i++)
        {
            counter[i] = new int[w];
            memset(counter[i], 0, sizeof(int) * w);
        }

        for(int i = 0; i < d; i++)
        {
            sac_counter[i] = new long_sign[w];
            memset(sac_counter[i], 0, sizeof(long_sign) * w);
        }

        MAX_CNT = (1 << 32) - 1;

        for(int i = 0; i < d; i++)
        {
            bobhash[i] = new BOBHash(i + 1000);
        }
    }
	void Insert(const char *str, int c) {
		int min_value = MAX_COUNT;
		int temp;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = counter[i][index[i]];
			min_value = temp < min_value ? temp : min_value;
		}
		if (min_value + c >= MAX_COUNT)
			for (int i = 0; i < d; i++)
			{
				counter[i][index[i]] = MAX_COUNT;
				return;
			}
		for (int i = 0; i < d; i++)
		{
			if (counter[i][index[i]] == min_value) {
				counter[i][index[i]] += c;
			}
			else if (counter[i][index[i]] < min_value + c) {
				counter[i][index[i]] = min_value + c;
			}
		}
	}
	int Query(const char *str)
	{
		int min_value = 1 << 30;
		int temp;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = counter[i][index[i]];
			min_value = temp < min_value ? temp : min_value;
		}
		return min_value;
	}
	void dynamic_sac_insert(const char *str, int c, double *gamma) { 
		int min_value = (int)predict(long_maxi, gamma);
		int temp;
		int inde;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sac_counter[i][index[i]], gamma);
			min_value = temp < min_value ? temp : min_value;
		}
		if (min_value + c >= predict(long_maxi, gamma))
			for (int i = 0; i < d; i++)
			{
				sac_counter[i][index[i]] = long_maxi;
				return;
			}
		for (int i = 0; i < d; i++)
		{
			if (predict(sac_counter[i][index[i]], gamma) == min_value) {
				adding(sac_counter[i][index[i]], c, gamma);
				inde = i;
			}
		}
		for (int i = 0; i<d; ++i) {
			if (predict(sac_counter[i][index[i]], gamma) < min_value + c) {
				sac_counter[i][index[i]] = sac_counter[inde][index[inde]];
			}
		}
	}
	int dynamic_sac_query(const char *str, double *gamma) {
		int min_value = (int)predict(long_maxi, gamma);
		int temp;
		int ind = 0;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sac_counter[i][index[i]], gamma);
			if (temp < min_value) {
				ind = i; min_value = temp;
			}
		}
		return predict(sac_counter[ind][index[ind]], gamma);
	}

	void static_sac_insert(const char *str, int l_sign, double *gamma) { 
		int min_value = (int)predict(long_maxi,l_sign, gamma);
		int temp;
		int inde;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sac_counter[i][index[i]],l_sign, gamma);
			min_value = temp < min_value ? temp : min_value;
		}
		if (min_value + 1 >= predict(long_maxi,l_sign, gamma))
			for (int i = 0; i < d; i++)
			{
				sac_counter[i][index[i]] = long_maxi;
				return;
			}
		for (int i = 0; i < d; i++)
		{
			if (predict(sac_counter[i][index[i]],l_sign, gamma) == min_value) {
				add_one(sac_counter[i][index[i]], l_sign, gamma);
				inde = i;
			}
		}
		for (int i = 0; i<d; ++i) {
			if (predict(sac_counter[i][index[i]],l_sign, gamma) < min_value + 1) {
				sac_counter[i][index[i]] = sac_counter[inde][index[inde]];
			}
		}
	}

	
	int static_sac_query(const char *str,int l_sign, double *gamma) {
		int min_value = (int)predict(long_maxi,l_sign, gamma);
		int temp;
		int ind = 0;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sac_counter[i][index[i]],l_sign, gamma);
			if (temp < min_value) {
				ind = i; min_value = temp;
			}
		}
		return predict(sac_counter[ind][index[ind]],l_sign, gamma);
	}

	void check(const char *str) {
		int temp;
		int result[22];
		cout << "[[";
		//check str's correspond hash table content
		for (int i = 0; i<d; ++i) {
			int pos = (bobhash[i]->run(str, strlen(str))) % w;
			result[i] = counter[i][pos];

		}
		//sort(result, result + d);
		for (auto x : result)cout << x << " ";
		cout << "]]" << endl;
	}

    ~CUSketch()
    {
        for(int i = 0; i < d; i++)
        {
            delete []counter[i];
        }
        for(int i = 0; i < d; i++)
        {
            delete bobhash[i];
        }
    }
};
 // CUSKETCH_H
