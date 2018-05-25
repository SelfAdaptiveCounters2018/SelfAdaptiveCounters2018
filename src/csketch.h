#pragma once
#include <algorithm>
#include <cstring>
#include <string.h>
#include <vector>
#include "sketch.h"
#include "bobhash.h"
#include "sac.h"
#include <iostream>
class CSketch:public class_sketches
{	
public:
    BOBHash * bobhash[20 * 2];
    int index[20];
    int *counter[20];
    long_sign *sign_counter[20];
    const int COUNTER_SIZE= 32;
	int w, d;
    int base_num;
	int MAX_CNT, MIN_CNT;
	int counter_index_size;
	uint64_t hash_value;


    CSketch(int _w, int _d)//w is the size of the hash area, d is the number of hash functions in the Mediean trick
	{
		counter_index_size = 20;
        w = _w/base_num;              //divide each of the d hash aera into yet base_num sub sections
        d = _d/base_num;
		
        for(int i = 0; i < _d; i++)
        {
            counter[i] = new int[_w];
            memset(counter[i], 0, sizeof(int) * _w);

            sign_counter[i] = new long_sign[_w];
            memset(sign_counter[i], 0, sizeof(long_sign) * _w);
		}

		MAX_CNT = (1 << (COUNTER_SIZE - 1)) - 1;
        MIN_CNT = (-(1 << (COUNTER_SIZE - 1)));



        for(int i = 0; i < _d * 2; i++)
		{
			bobhash[i] = new BOBHash(i + 1000);
		}
	}
    void Insert(const char * str,int c)
	{
		int g = 0;
        for(int i = 0; i < d; i++)
        {
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;

			if(g == 0)
			{
                if(counter[i][index[i]]+c < MAX_CNT)
				{
                    counter[i][index[i]] += c;
				}
                else cout<<"int overflow, counter value = "<< counter[i][index[i]]<<endl;
			}
			else
			{
                if(counter[i][index[i]]-c > MIN_CNT)
				{
                    counter[i][index[i]] -= c;
				}
                else cout<<"int underflow, counter value = "<< counter[i][index[i]]<<endl;

            }
		}
	}
	int Query(const char *str)
	{
		int temp;
		int res[20];
		int g;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = counter[i][index[i]];
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;
			res[i] = (g == 0 ? temp : -temp);
		}
		sort(res, res + d);
		int r;
		if (d % 2 == 0)
		{
			r = (res[d / 2] + res[d / 2 - 1]) / 2;
		}
		else
		{
			r = res[d / 2];
		}
		return r;
	}
	void Delete(const char * str)
	{
		int g = 0;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;

			if (g == 1)
			{
				if (counter[i][index[i]] != MAX_CNT)
				{
					counter[i][index[i]]++;
				}
			}
			else
			{
				if (counter[i][index[i]] != MIN_CNT)
				{
					counter[i][index[i]]--;
				}
			}
		}
	}
    void dynamic_sac_insert(const char *str,int c,double *gamma){

        int g = 0;
        for(int i = 0; i < d; i++)
        {
            index[i] = (bobhash[i]->run(str, strlen(str))) % w;
            g = (bobhash[i + d]->run(str, strlen(str))) % 2;

            if(g == 0)
            {
                if(sign_counter[i][index[i]] != MAX_CNT)
                    adding(sign_counter[i][index[i]],c,gamma);
            }
            else
            {
                if(sign_counter[i][index[i]] != MIN_CNT)
                    subtracting(sign_counter[i][index[i]],c,gamma);
            }

        }
    }
	int dynamic_sac_query(const char *str, double *gamma) {
		int temp;
		int res[20];
		int g;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sign_counter[i][index[i]], gamma);
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;
			res[i] = (g == 0 ? temp : -temp);
		}
		sort(res, res + d);
		int r;
		if (d % 2 == 0)
		{
			r = (res[d / 2] + res[d / 2 - 1]) / 2;
		}
		else
		{
			r = res[d / 2];
		}
		return r;
	}
	void static_sac_insert(const char *str, int l_sign, double *gamma) {

		int g = 0;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;

			if (g == 0)
			{
				if (sign_counter[i][index[i]] != MAX_CNT)
					add_one(sign_counter[i][index[i]], l_sign, gamma);
			}
			else
			{
				if (sign_counter[i][index[i]] != MIN_CNT)
					minus_one(sign_counter[i][index[i]], l_sign, gamma);
			}
		}
	}
	int static_sac_query(const char *str,int l_sign, double *gamma) {
		int temp;
		int res[20];
		int g;
		for (int i = 0; i < d; i++)
		{
			index[i] = (bobhash[i]->run(str, strlen(str))) % w;
			temp = predict(sign_counter[i][index[i]],l_sign, gamma);
			g = (bobhash[i + d]->run(str, strlen(str))) % 2;
			res[i] = (g == 0 ? temp : -temp);
		}
		sort(res, res + d);
	//	for (auto thing : res)cout << thing << "  ";
	//	cout << endl;
		int r;
		if (d % 2 == 0)
		{
			r = (res[d / 2] + res[d / 2 - 1]) / 2;
		}
		else
		{
			r = res[d / 2];
		}
		return r;
	}
//

    void check(const char *str,double *gamma){     
        int temp;
		int result[22];
        cout<<"[[";
        //check str's correspond hash table content
        for(int i=0;i<d;++i){
            int pos=(bobhash[i]->run(str, strlen(str))) % w;
            result[i]=abs(predict(sign_counter[i][pos],4,gamma));
			
        }
		sort(result, result + d);
		for (auto x : result)cout << x << " ";
        cout<<"]]"<<endl;
    }

   
	~CSketch()
	{
		for(int i = 0; i < d; i++)	
		{
			delete []counter[i];
		}
		for(int i = 0; i < d * 2; i++)
		{
			delete bobhash[i];
		}
	}
};
 // CSKETCH_H
