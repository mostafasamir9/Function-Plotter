#include <QCoreApplication>
#include <QDebug>
#include "functions.h"

#define PRECISION 100

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /****************** Test Values ******************/
    double initial_value = -100;
    double maximum_value = 100;

    QVector<double> x_test;
    QVector<double> y_test;

    int arr_index = 0;
    for (double x=initial_value; x<maximum_value; x += 1.0/PRECISION)
    {
       x_test[arr_index] = x;
       y_test[arr_index] = pow(x,2.0) + (3.0*x) - (x/2.0) + 1.0;
    }

    /****************** Function Values ******************/
    QString equation = "x^2 + 3*x - x/2 + 1";
    QByteArray chararray = equation.toLocal8Bit(); // string -> qbytearray
    char* expression = chararray.data(); // qbytearray -> char*

    //Initial the vectors
    //precision is 100
    QVector<double> x_arr((maximum_value+abs(initial_value))*PRECISION + 1);
    QVector<double> y_arr((maximum_value+abs(initial_value))*PRECISION + 1);

    // call the parsing function
    parseEquation(expression, equation, x_arr, y_arr , initial_value , maximum_value);


    /***************** Compare Values *******************/
    bool test_fail_flag = false;
    for (int arr_index = 0; arr_index < ((maximum_value+abs(initial_value))*PRECISION + 1); arr_index++)
    {
        if (x_test[arr_index] != x_arr[arr_index])
        {
            test_fail_flag = true;
        }
        if (y_test[arr_index] != y_arr[arr_index])
        {
            test_fail_flag = true;
        }
    }

    if (test_fail_flag)
    {
        qDebug()<<"Test Failed";
    }
    else
    {
        qDebug()<<"Test Successed";
    }

    return a.exec();
}
