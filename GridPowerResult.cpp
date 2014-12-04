#include "GridPowerResult.h"




void GridPowerResult:: findGridFinalTotalPower(float frequence)//求出每个网格的功率，将vector中的功率相加，频率以mhz为单位
{
	complex totalReiceiveElecFiledStrength={0,0};
	complexCalculate complexcalculate4;
	int s;
	s=gridFinalPower.size();
	if(s>0)
	{	
	for( int i=1;i<=s;i++)//求出网格中多条射线的电场强度的和，考虑相位
	{
		 complexcalculate4.findComplexAddComplex(totalReiceiveElecFiledStrength,gridFinalPower[i-1]);
		 totalReiceiveElecFiledStrength=complexcalculate4.consequence;
			
	}	
	float waveLength;
	waveLength=300/frequence;
	//要求接收点的功率，得对场强进行模平方
	gridFinalTotalPower=complexcalculate4.findComplexLength(totalReiceiveElecFiledStrength);//求出电场和的模值
	gridFinalTotalPower=gridFinalTotalPower*gridFinalTotalPower;//进行场强模平方
	gridFinalTotalPower=gridFinalTotalPower*waveLength*waveLength/(480*3.14*3.14);
	gridPowerLoss=10*log10(39.8/gridFinalTotalPower);
	

	}
}
