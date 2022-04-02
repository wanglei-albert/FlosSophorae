#include <eigen3/Eigen/Dense>
#include <console_bridge/console.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

void ConstructVector();
void VectorNorm();
void ResizeVector();


void ArrayToMatrixXd();
void TransposeVector();

void SwapMatrixes();
void MatrixSlice();

void QuaternionToMatrix();
void MatrixToQuaternion();
void TransformMatrix();


int main(int argc, char** argv)
{
    console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_INFO);
    
    // vector related operation
    ConstructVector();
    VectorNorm();
    ResizeVector();
    TransposeVector();
    
    // matrix related operation
    MatrixToQuaternion();
    QuaternionToMatrix();
    MatrixSlice();
    SwapMatrixes();
    ArrayToMatrixXd();
    
    TransformMatrix();
    
    
    return 0;
}


std::ostream& operator << (std::ostream& oss, const Eigen::Isometry3d& tf)
{
    for(int r = 0; r < tf.rows(); ++r)
    {
        oss << "\t\t";
        for(int c = 0; c < tf.cols(); ++c)
        {
            oss << tf(r,c) << " "; 
        }
        
        oss << std::endl;
    }
            
    
    return oss;
}

void ConstructVector()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    
    Eigen::VectorXd sized_5_vect(5);
    std::cout << "init a vector with capbility of 5 elemens, actural vector size result: " 
        << sized_5_vect.size() << std::endl;
        
        
    int arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Eigen::VectorXi vi = Eigen::Map<Eigen::VectorXi, 0, Eigen::InnerStride<2>>(arr, 6);
    
    
    CONSOLE_BRIDGE_logInform("construct with array(InnerStride)[total: %d]: ", std::end(arr) - std::begin(arr));
    std::cout << "vector value: " << vi.transpose() << std::endl;
}


void VectorNorm()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::Vector3d v{3, 4, 5};
    std::cout << "vector:" << v.transpose() << std::endl;
    std::cout << "normal: " << v.norm() << std::endl;
}


void ResizeVector()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::VectorXd vxd;
    CONSOLE_BRIDGE_logInform("VectorXd default size: %d, %d.", vxd.rows(), vxd.cols()) ;
    vxd.resize(3);
    CONSOLE_BRIDGE_logInform(" resized VectorXd: %d, %d.", vxd.rows(), vxd.cols()) ;
}

void ArrayToMatrixXd()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    int arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    CONSOLE_BRIDGE_logInform("array to matrix3i: ");
    std::cout << Eigen::Map<Eigen::Matrix3i>(arr) << std::endl;
         
    CONSOLE_BRIDGE_logInform("array to vectorxd(OutterStride): ");
    std::cout << Eigen::Map<Eigen::MatrixXi, 0, Eigen::OuterStride<>>(arr, 3, 3,  Eigen::OuterStride<>(4)) << std::endl;
}

void TransformMatrix()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::Isometry3d tf;
    tf.translation() = Eigen::Vector3d(0.1, 0, 0);
    tf.linear() = Eigen::Quaterniond(1, 0, 0, 0).matrix();
    
    std::cout << "transform matrix: " << std::endl
         << tf << std::endl;
}

void TransposeVector()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::VectorXi vxi(5);
    vxi << 1 , 2 , 3 , 4 , 5;
    CONSOLE_BRIDGE_logInform("initial vector: ");
    std::cout << vxi << std::endl;
    
    vxi *= 3;
    CONSOLE_BRIDGE_logInform("vector * scalar: ");
    std::cout << vxi << std::endl;
    
    CONSOLE_BRIDGE_logInform("after transpose: ");
    std::cout << vxi.transpose() << std::endl;
}

void SwapMatrixes()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::MatrixXd xd = Eigen::MatrixXd::Identity(5, 5);
    xd(3,3) = 3.333;
    
    std::cout << "xd's initial values: " << std::endl
    << xd << std::endl;
    
    Eigen::MatrixXd xd2;
    xd2.swap(xd);
    
    std::cout << "after swapped: " << std::endl;
    std::cout << "rows@xd: " << xd.rows() << "\tcolums@xd: " << xd.cols() << std::endl;
    std::cout << "rows@xd2: " << xd2.rows() << "\tcolums@xd2: " << xd2.cols() << std::endl;
    
    // std::cout is more convenient to probe the values of eigen matrix
    std::cout << "xd2: " << std::endl
              << xd2 << std::endl;
}

void MatrixSlice()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    
    Eigen::Isometry3d tf;
    tf.translation() << -1, 1.5, 0.1;
    tf.linear() = Eigen::Quaterniond(1, 0, 0, 0).matrix();
		  
    std::cout << "tf: " << std::endl
        << tf << std::endl;
    
    Eigen::Matrix3d m;
    m << 1,2,3,
         4,5,6,
         7,8,9;
    std::cout << "block operation: tr.row(1).head(2) = vxi.head(2)" << std::endl;
    
    Eigen::Vector3d v3d(3);
    v3d << 1 , 2 , 3 ;
    std::cout << "maxtrix minus result:" << (m.col(0) - v3d).transpose() << std::endl;
    
    m.row(1).head(2) = tf.translation().head(2).transpose();
    std::cout << m.row(1).head(2) << std::endl;
}

void QuaternionToMatrix()
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    Eigen::Vector3d rot_axis{0, 0, 1};
    double rot_rad = M_PI / 4;
    Eigen::AngleAxisd tv(rot_rad, rot_axis); 
    std::cout << "rotate " << rot_rad 
              << " radian around axis: " << Eigen::Vector3d() << std::endl;
              
    Eigen::Isometry3d tr = Eigen::Isometry3d::Identity();
    tr.rotate(tv);
    tr.pretranslate(Eigen::Vector3d(21, 32, 53));
    
    std::cout << "the matrix as rel. quaternion: " << std::endl
        << tr << std::endl;
}

void MatrixToQuaternion() 
{
    CONSOLE_BRIDGE_logInform("\n\n%s", __func__);
    //Eigen::Quaterniond q1 = tr;
    Eigen::Matrix3d m;
    m << cos(M_PI / 3), -sin(M_PI / 3), 0,
         sin(M_PI / 3), cos(M_PI / 3),  0,
         0,             0,              1;
    std::cout << "rotation matrix: " << std::endl
        << m;
    Eigen::Quaterniond q(m);
    std::cout << "quaternion: w:"<< q.w() 
              << ", x: " << q.x() 
              << ", y: " << q.y() 
              << ", z: " << q.z() 
              << std::endl;
}
