#include<iostream>
#include<iomanip>
#include<vector>


template<class function_t>
void runge_kutta4(function_t f, function_t g, std::vector<double>& initial, std::vector<double>& resu, double h){
	double f1,f2,f3,f4,g1,g2,g3,g4,t0,x0,y0,x1,y1;
	t0 = initial[0];
	x0 = initial[1];
	y0 = initial[2];
	f1 = f(t0,x0,y0);
	g1 = g(t0,x0,y0);
	f2 = f(t0+h/2,x0+h*f1/2,y0+h*g1/2);
	g2 = g(t0+h/2,x0+h*f1/2,y0+h*g1/2);
	f3 = f(t0+h/2,x0+h*f2/2,y0+h*g2/2);	
	g3 = g(t0+h/2,x0+h*f2/2,y0+h*g2/2);
	f4 = f(t0+h,x0+h*f3,y0+h*g3);	
	g4 = g(t0+h,x0+h*f3,y0+h*g3);
	x1 = x0+h*(f1+2*f2+2*f3+f4)/6;
	y1 = y0+h*(g1+2*g2+2*g3+g4)/6;
	resu[0] = t0+h;
	resu[1] = x1;
	resu[2] = y1;
}

double F(double t, double x, double y){
	double dx;
	dx = x+2*y;
	return dx;
}
double G(double t, double x, double y){
	double dy;
	dy = 3*x+2*y;
	return dy;
}


int main(){
	std::vector<double> initial(3);
	std::vector<double> resu(3);
	double a,b,H;
	double t,step;
	int i;
	std::cout << "输入所求微分方程组的初值：t0 x0 y0:";
	std::cin >> initial[0] >> initial[1] >> initial[2];
	std::cout << "输入区间：[a,b]";
	std::cin >> a >> b;
	std::cout << "输入子区间的个数：";
	std::cin >> step;
	std::cout << std::setiosflags(std::ios::right) << std::setiosflags(std::ios::fixed) << std::setprecision(10);
	H = (b-a)/step;
	std::cout << initial[0] << std::setw(18) << initial[1] << std::setw(18) << initial[2] << std::endl;
	for(int i=0;i<step;++i){
		runge_kutta4(F,G,initial,resu,H);
		std::cout << resu[0] << std::setw(20) << resu[1] << std::setw(20) << resu[2] << std::endl;
	}
	return 0;
}
