#include <iostream>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;

int main()
{
	MatrixXd m(2,2);//MatrixXd表示是任意尺寸的矩阵ixj, m(2,2)代表一个2x2的方块矩阵
	m(0,0) = 3;//代表矩阵元素a11
	m(1,0) = 2.5;//a21
	m(0,1) = -1;//a12
	m(1,1) = m(1,0) + m(0,1);//a22=a21+a12
	cout << m << endl;//输出矩阵m
}

