#pragma once

//base class to make experimet function and main function simple and clear

class class_sketches {
public:
	virtual void Insert(const char * str, int c) {}
	virtual int Query(const char *str) = 0;
	virtual void dynamic_sac_insert(const char *str, int c, double *gamma) {}
	virtual int dynamic_sac_query(const char *str, double *gamma) = 0;
	virtual void static_sac_insert(const char *str, int l_sign, double *gamma) {}
	virtual int static_sac_query(const char *str, int l_sign, double *gamma) = 0;
};
