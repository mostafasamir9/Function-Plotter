#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QMainWindow>

/* function to display the error message */
void displayMessage(QString msg);

/* function to return the values of x and y vectors */
void parseEquation(char* expression, QString equation, QVector<double> &x_arr, QVector<double> &y_arr, double x_min_d ,double x_max_d);

#endif // FUNCTIONS_H
