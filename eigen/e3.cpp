#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main()
{
	Matrix3d m = Matrix3d::Random();//"Matrix3d"直接定义了一个3-by-3的方块矩阵
	m = (m + Matrix3d::Constant(1.2)) * 50;
	cout << "m =" << endl << m << endl;
	Vector3d v(1,2,3); //"Vector3d"直接定义了一个维度为3的列向量
	cout << "m * v =" << endl << m * v << endl;
}

