#include<iostream>
#include<vector>

using namespace std;

#define		NEEDPRINT				0
#if NEEDPRINT
#else
#define     baseSalary              30000
#define     bonus                   (1500+3586)
#define		monthSalary				baseSalary + bonus
#define		signBonus				10000
#define		annualSalary			baseSalary * 3
#define		maxSocialSecurity		23565
#define		accumulationFundRatio	0.12
#endif 

class taxMessage
{
public:
	int amountMin;
	int amountMax;
	float ratio;
	int quickCalc;
public:
	taxMessage() : amountMin(0), amountMax(INT_MAX), ratio(0.0), quickCalc(0) {};
	taxMessage(int a, int b, float c, int d) : amountMin(a), amountMax(b), ratio(c), quickCalc(d) {};
};


int main()
{
	vector<taxMessage> taxLaw;
	taxLaw.push_back(taxMessage(0, 36000, 0.03, 0));
	taxLaw.push_back(taxMessage(36000, 144000, 0.10, 2520));
	taxLaw.push_back(taxMessage(144000, 300000, 0.20, 16920));
	taxLaw.push_back(taxMessage(300000, 420000, 0.25, 31920));
	taxLaw.push_back(taxMessage(420000, 660000, 0.30, 52920));
	taxLaw.push_back(taxMessage(660000, 960000, 0.35, 85920));

	double socialSecurity = (monthSalary > maxSocialSecurity ? maxSocialSecurity : monthSalary) * (0.102 + accumulationFundRatio);
	double allYearSum = 0;
	double realYearSum = 0;
	double untilLastMonthTax = 0;

	for (int monthIdx = 1; monthIdx <= 12; monthIdx++)
	{
		//before tax
		double monthEarnWithoutAnything = monthSalary + (monthIdx == 1 ? signBonus : (monthIdx == 12 ? annualSalary : 0));
		allYearSum += monthEarnWithoutAnything;

		//all need to be tax
		double alltax = 0;
		double taxableAccount = allYearSum - (socialSecurity + 5000) * monthIdx;
		for (int i = taxLaw.size() - 1; i >= 0; i--)
		{
			if (taxableAccount > taxLaw[i].amountMin)
			{
				alltax = taxableAccount * taxLaw[i].ratio - taxLaw[i].quickCalc;
				break;
			}
		}

		//Tax calculate
		double monthTax = alltax - untilLastMonthTax;
		double monthEarn = monthEarnWithoutAnything - socialSecurity - monthTax;
		untilLastMonthTax = alltax;
		realYearSum += monthEarn;

		printf("Month %02d earn %8.2f, in sum %9.2f\n", monthIdx, monthEarn, realYearSum);
	}

	system("pause");
	return 0;
}