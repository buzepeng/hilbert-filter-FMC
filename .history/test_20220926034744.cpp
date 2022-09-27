#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
const struct comDouble
{
   vector<double> real;
   vector<double> imag;
};
comDouble filter(vector<double> b, vector<double> x)
{
   /*
   	注意：该函数仅实现了a为标量且为1时的函数滤波！！！
   	参数介绍：
   	b：		滤波器系数
   	a：		分母系数
   	x:		复数
   	x.real: 复数实部
   	x.imag: 复数虚部

   	Y：		复数滤波结果
   	Y.real：复数实部滤波结果
   	Y.imag：复数虚部滤波结果

   	公式：(a = 1时)
   	当 i < 滤波器阶数 时有:
   		Y[i] = ∑b[j]*x[i-j] (下限j=0, 上限j<i) 
   	当 i > 滤波器阶数 时有:
   		Y[i] = ∑b[j]*x[i-j] (下限j=0, 上限j<滤波器阶数)
   */
   comDouble Y;
   for (int i = 0; i < b.size(); i++)
   {
   		double real = 0.0;
   		double imag = 0.0;
   
   		for (int j = 0; j <= i; j++) {
   			real += b[j] * x[i - j];
   			// imag += b[j] * x.imag[i - j];
   		}
   		Y.real.push_back(real);
   		Y.imag.push_back(imag);
   }
   for (int i = b.size(); i < x.size(); i++) {
   		double real = 0.0;
   		double imag = 0.0;
   		
   		for (int j = 0; j < b.size(); j++) {
   			real += b[j] * x[i - j];
   			// imag += b[j] * x.imag[i - j];
   		}
   		
   		Y.real.push_back(real);
   		Y.imag.push_back(imag);
   }
   return Y;
}

int main(){
	double fs = 150, f1 = 10, f2 = 20, f3 = 30;
	vector<double> signal(151);
	vector<double> B = {-0.000734498107994464,	0.00169295265156365,	0.00134224421382085,	-0.000830391728086922,	-0.000630182935624796,	-0.000136656846809355,	-0.00326365369394200,	-0.00168273399809086,	0.00922018440156065,	0.00901644082037819	-0.0111452361235621	-0.0174371529295370	0.00488720052189717	0.0146356060446640	0.000951418326278581,	0.00682768336437121,	0.0139160256225384,	-0.0340279581666285,	-0.0620463839022784,	0.0364102329736511,	0.127506136382855,	0.00808131265869404,	-0.169553946545181,	-0.0865805256704257,	0.154373257040634,	0.154373257040634,	-0.0865805256704257,	-0.169553946545181,	0.00808131265869404,	0.127506136382855,	0.0364102329736511,	-0.0620463839022784,	-0.0340279581666285,	0.0139160256225384,	0.00682768336437121	0.000951418326278581	0.0146356060446640	0.00488720052189717	-0.0174371529295370	-0.0111452361235621	0.00901644082037819	0.00922018440156065	-0.00168273399809086	-0.00326365369394200	-0.000136656846809355	-0.000630182935624796	-0.000830391728086922	0.00134224421382085	0.00169295265156365	-0.000734498107994464};
	for(int i = 0;i<151;i++){
		double t = i/fs;
		signal[i] = 5*sin(2*M_PI*f1*t)+10*sin(2*M_PI*f2*t)+8*sin(2*M_PI*f3*t);
	}
	comDouble res = filter(B, signal);
}