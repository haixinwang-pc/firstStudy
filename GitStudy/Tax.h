#pragma once
#include<iostream>
#include<vector>

using namespace std;

//config
#define		NEEDPRINT				1

//time information
#define		OnboardingMonth			7
#define		OnboardingDate			6
#define		NewYearMonth			1

//salary information
#define     baseSalary              23000
#define     bonus                   1250
#define		monthSalary				baseSalary + bonus
#define		signBonus				30000
#define		annualSalary			baseSalary * 4
#define		maxSocialSecurity		27786
#define		accumulationFundRatio	0.12

class taxMessage
{
public:
	int amountMin;
	int amountMax;
	float ratio;
	int quickCalc;
public:
	taxMessage() : amountMin(0), amountMax(INT_MAX), ratio(0.0), quickCalc(0) {};
	taxMessage(int a, int b, double c, int d) : amountMin(a), amountMax(b), ratio(c), quickCalc(d) {};
};