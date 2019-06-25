#include <Eigen/Dense> 
#include <iostream> 

using namespace Eigen;

int main()
{  
	Matrix3d A;  
	A<<1,1,1,  
		2,-1,-1,  
		2,-4,5;  

	HouseholderQR<Matrix3d> qr;  
	qr.compute(A);  
	MatrixXd R = qr.matrixQR().triangularView<Upper>();  
	MatrixXd Q =  qr.householderQ();  
	std::cout << "QR2(): HouseholderQR---------------------------------------------"<< std::endl;  
	std::cout << "A "<< std::endl <<A << std::endl << std::endl;  
	std::cout <<"qr.matrixQR()"<< std::endl << qr.matrixQR() << std::endl << std::endl;  
	std::cout << "R"<< std::endl <<R << std::endl << std::endl;  
	std::cout << "Q "<< std::endl <<Q << std::endl << std::endl;  
	std::cout <<"Q*R" << std::endl <<Q*R << std::endl << std::endl;  

	return 0;
}  
