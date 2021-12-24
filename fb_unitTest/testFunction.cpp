#include "testfunction.h"
#define PRECISION 100

void testFunction1()
{
    /****************** Test Values ******************/
    double initial_value = -0.05;
    double maximum_value = 0.05;

    QVector<double> x_test((maximum_value+abs(initial_value))*PRECISION + 1);
    QVector<double> y_test((maximum_value+abs(initial_value))*PRECISION + 1);

    int arr_index = 0;
    for (double x=initial_value; x<maximum_value + .1/PRECISION; x += (1.0/PRECISION))
    {
        // if x is smaller than most step then it's zero
       if(x < .1/PRECISION && x > -.1/PRECISION)
           x = 0;

       x_test[arr_index] = x;
       y_test[arr_index] = pow(x,2.0) + (3.0*x) - (x/2.0) + 1.0;
       arr_index++;
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
    for (int arr_index = 0; arr_index < ((maximum_value+abs(initial_value))*PRECISION); arr_index++)
    {
        if (x_test[arr_index] - x_arr[arr_index] > 0.000000000001)
        {
            test_fail_flag = true;
            break;
        }
        if (y_test[arr_index] - y_arr[arr_index] > 0.000000000001)
        {
            test_fail_flag = true;
            break;
        }
    }

    if (test_fail_flag)
    {
        qDebug()<<"Test 1 Failed";
    }
    else
    {
        qDebug()<<"Test 1 Successed";
    }

}

void testFunction2()
{
    /****************** Test Values ******************/
    double initial_value = -1;
    double maximum_value = 1;

    QVector<double> x_test((maximum_value+abs(initial_value))*PRECISION + 1);
    QVector<double> y_test((maximum_value+abs(initial_value))*PRECISION + 1);

    int arr_index = 0;
    for (double x=initial_value; x<maximum_value + .1/PRECISION; x += (1.0/PRECISION))
    {
        // if x is smaller than most step then it's zero
       if(x < .1/PRECISION && x > -.1/PRECISION)
           x = 0;

       x_test[arr_index] = x;
       y_test[arr_index] = pow(x,3.0) - (2.0*x) + 10.0;
       arr_index++;
    }

    /****************** Function Values ******************/
    QString equation = "x^3 - 2*x + 10";
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
    for (int arr_index = 0; arr_index < ((maximum_value+abs(initial_value))*PRECISION); arr_index++)
    {
        if (x_test[arr_index] - x_arr[arr_index] > 0.000000000001)
        {
            test_fail_flag = true;
            break;
        }
        if (y_test[arr_index] - y_arr[arr_index] > 0.000000000001)
        {
            test_fail_flag = true;
            break;
        }
       //  qDebug()<<arr_index<<":pass";
    }

    if (test_fail_flag)
    {
        qDebug()<<"Test 2 Failed ";
    }
    else
    {
        qDebug()<<"Test 3 Successed ";
    }

}

void testFunction3()
{
    /****************** Test Values ******************/
    double initial_value = -10;
    double maximum_value = 10;

    QVector<double> x_test((maximum_value+abs(initial_value))*PRECISION + 1);
    QVector<double> y_test((maximum_value+abs(initial_value))*PRECISION + 1);

    int arr_index = 0;
    for (double x=initial_value; x<maximum_value + .1/PRECISION; x += (1.0/PRECISION))
    {
        // if x is smaller than most step then it's zero
       if(x < .1/PRECISION && x > -.1/PRECISION)
           x = 0;

       x_test[arr_index] = x;
       y_test[arr_index] = 5;
       arr_index++;
    }

    /****************** Function Values ******************/
    QString equation = "5";
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
    for (int arr_index = 0; arr_index < ((maximum_value+abs(initial_value))*PRECISION); arr_index++)
    {
        if (abs(x_test[arr_index] - x_arr[arr_index]) > 0.000000000001)
        {
            test_fail_flag = true;
            qDebug()<<arr_index<<" x failed";
            break;
        }
        if (abs(y_test[arr_index] - y_arr[arr_index]) > 0.000000000001)
        {
            test_fail_flag = true;
            qDebug()<<arr_index<<" y failed";
            break;
        }
     //    qDebug()<<arr_index<<":pass";
    }

    if (test_fail_flag)
    {
        qDebug()<<"Test 3 Failed ";
    }
    else
    {
        qDebug()<<"Test 3 Successed ";
    }

}
