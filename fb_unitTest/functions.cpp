#include "functions.h"
#include "tinyexpr.h"
#define PRECISION 100

void parseEquation(char* expression, QString equation , QVector<double> &x_arr, QVector<double> &y_arr, double x_min_d ,double x_max_d){
    double x; // The x variable in f(x)

    // Store variable names and pointers.
    te_variable vars[] = { {"x", &x}};

    int err; // the error index

    // Compile the expression with variable
    // te_compile params -> (pointer of chars array , pointer of the vars 2d  array , int count of varaibles , error pointer)
    te_expr* expr = te_compile(expression, vars,1, &err);

    //if there's no errors
    if (expr) {
        //index of the vector begin from 0
        int arr_index = 0;
        for (double i=x_min_d; i<x_max_d + .1/PRECISION; i+= (1.0/PRECISION))
        {
            //iterate the values of x and the corresponding y values
            x = i;

            // if x is smaller than most value then it's zero
            if(x < 0.1/PRECISION && x > -0.1/PRECISION)
                x = 0;

            x_arr[arr_index]=x;

            double y = te_eval(expr); // evaluate the expression and put the value in y
            y_arr[arr_index]=y;
            arr_index++;

        }
        te_free(expr); // free the expression
    }
    else {
        /**************************** Parsing Errors *******************************/
        QString errormsg = "Error at character " + QString::number(err);
        if(equation[err-1].isLetter() && equation[err-1] != 'x')
        {
            errormsg += "\t \n you must use ' x ' only as a variable.  y = f(x) \t";
        }
        else if (equation[err-2].isSpace())
        {
            errormsg += "\t \n you should insert any operation in this space \t";
        }
        return;
    }
}
