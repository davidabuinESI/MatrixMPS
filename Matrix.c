#include <OPMATRIX.h>
#include <IOMATRIX.h>
Matrix Substraction(Matrix A,Matrix B)
{
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R.m[i][j]=A.m[i][j]-B.m[i][j];
        }
    }
    return R;
}
Matrix Addition(Matrix A,Matrix B)
{
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R.m[i][j]=A.m[i][j]+B.m[i][j];
        }
    }
    return R;
}