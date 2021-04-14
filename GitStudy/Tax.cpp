/*
v0: 粗略估算一下年薪
v1：按照入职时间运算第一年的薪水，有一些TODO
v2：增加第二年薪水的测试
*/

#include"Tax.h"

int main()
{
	vector<taxMessage> taxLaw;
	taxLaw.push_back(taxMessage(0, 36000, 0.03, 0));
	taxLaw.push_back(taxMessage(36000, 144000, 0.10, 2520));
	taxLaw.push_back(taxMessage(144000, 300000, 0.20, 16920));
	taxLaw.push_back(taxMessage(300000, 420000, 0.25, 31920));
	taxLaw.push_back(taxMessage(420000, 660000, 0.30, 52920));
	taxLaw.push_back(taxMessage(660000, 960000, 0.35, 85920));

	double allYearSum = 0;
	double realYearSum = 0;
	double untilLastMonthTax = 0;

	for (int monthIdx = 1; monthIdx <= 12; monthIdx++)
	{
		//before tax.
		double monthEarnWithoutAnything = 0;
		if (monthIdx < OnboardingMonth)
			monthEarnWithoutAnything = 0;
		else if (monthIdx == OnboardingMonth)
			monthEarnWithoutAnything = signBonus + ((monthSalary) * (18 - OnboardingDate) / 22);//TODO: if later than 22
		else if (monthIdx == NewYearMonth)
			monthEarnWithoutAnything = (monthSalary) + annualSalary;
		else
			monthEarnWithoutAnything = (monthSalary);
		allYearSum += monthEarnWithoutAnything;

		//Exclude social insurance, all need to be tax.
		int numJobMonth = (monthIdx >= OnboardingMonth ? (monthIdx - OnboardingMonth + 1) : 0);
		double socialSecurity = (monthEarnWithoutAnything > maxSocialSecurity ? maxSocialSecurity : monthEarnWithoutAnything) * (0.102 + accumulationFundRatio);
		double alltax = 0;
		double taxableAccount = allYearSum - (socialSecurity + 5000) * numJobMonth;//TODO: if allYearSum < (socialSecurity + 5000) * numJobMonth
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
#if NEEDPRINT
		printf("Month %02d earn %8.2f, in sum %9.2f\n", monthIdx, monthEarn, realYearSum);
#endif 
	}

	system("timeout 20");
	return 0;
}