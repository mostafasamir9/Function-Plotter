#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include "tinyexpr.h"
#include "functions.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    // create graph and assign data to it:
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customplot->xAxis->setLabel("x");
    ui->customplot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customplot->xAxis->setRange(-1, 1);
    ui->customplot->yAxis->setRange(-1, 1);
    ui->customplot->replot();

}

void MainWindow::on_pushButton_clicked()
{

    /**************************** Getting Inputs Strings ***********************************/
    QString x_min,x_max;
    x_min = ui->x_min->text();
    x_max = ui->x_max->text();

    QString y_min,y_max;
    y_min = ui->y_min->text();
    y_max = ui->y_max->text();

    QString equation;
    equation = ui->equation->text();

    /******************************** Validations ***********************************/

    if(equation.isEmpty()){
        displayMessage("You didn't enter the function!");
        return;
    }

    bool emptyinput = 1;
    for ( int equation_index = 0 ; equation_index < equation.length() ; equation_index++ )
    {
        if(equation[equation_index].isNumber() || equation[equation_index].isLetter())
        {
            emptyinput = 0; // if ther's any number or letter then equation not empty
        }
        /* throw error if there's no operation between number and x */
        if(equation.length() - equation_index >=2 && equation[equation_index].isNumber() && equation[equation_index+1].isLetter())
        {
            displayMessage("You must include ' * ' character between the number & x in multiplication");
        }
    }

    if(emptyinput){
        displayMessage("your input is only white spaces!");
    }

    if(x_min.isEmpty()){
        displayMessage("You didn't enter x_min!");
        return;
    }
    if(x_max.isEmpty()){
        displayMessage("You didn't enter x_min!");
        return;
    }
    if(y_min.isEmpty()){
        displayMessage("You didn't enter y_min!");
        return;
    }
    if(y_max.isEmpty()){
        displayMessage("You didn't enter y_max!");
        return;
    }

    /* Check if the inputs of the ranges contains letters */
    for ( int digit_index = 0 ; digit_index < x_min.length() ; digit_index++)
    {
        if(!(x_min[digit_index].isDigit() || x_min[digit_index]=='.' || x_min[digit_index] == '-' || x_min[digit_index]=='+'))
        {
            displayMessage("x_min is invalid!  Enter Only numbers");
            return;
        }
    }

    for ( int digit_index = 0 ; digit_index < y_min.length() ; digit_index++)
    {
        if(!(y_min[digit_index].isDigit() || y_min[digit_index]=='.' || y_min[digit_index] == '-' || y_min[digit_index]=='+'))
        {
            displayMessage("y_min is invalid!  Enter Only numbers");
            return;
        }
    }
    for ( int digit_index = 0 ; digit_index < x_max.length() ; digit_index++)
    {
        if(!(x_max[digit_index].isDigit() || x_max[digit_index]=='.' || x_max[digit_index] == '-' || x_max[digit_index]=='+' ))
        {
            displayMessage("x_max is invalid!  Enter Only numbers");
            return;
        }
    }
    for ( int digit_index = 0 ; digit_index < y_max.length() ; digit_index++)
    {
        if(!(y_max[digit_index].isDigit() || y_max[digit_index]=='.' || y_max[digit_index] == '-' || y_max[digit_index]=='+'))
        {
            displayMessage("y_max is invalid!  Enter Only numbers");
            return;
        }
    }


    /********************** Convert the inputs to proper form ******************************/
    double x_min_d, x_max_d = 0;
    x_min_d = x_min.toDouble();
    x_max_d = x_max.toDouble();

    double y_min_d, y_max_d = 0;
    y_min_d = y_min.toDouble();
    y_max_d = y_max.toDouble();

    // Getting equation string
    equation = equation.toLower();


    /********************** Parsing the equation ****************************/

    // Convert the string to chars array because of the mathmatical parser library
    QByteArray chararray = equation.toLocal8Bit(); // string -> qbytearray
    const char* expression = chararray.data(); // qbytearray -> char*


    double x; // The x variable in f(x)

    // Store variable names and pointers.
    te_variable vars[] = { {"x", &x}};

    int err; // the error index

    // Compile the expression with variable
    // te_compile params -> (pointer of chars array , pointer of the vars 2d  array , int count of varaibles , error pointer)
    te_expr* expr = te_compile(expression, vars,1, &err);

    //Initial the vectors
    //precision is 100
    QVector<double> x_arr((x_max_d+abs(x_min_d))*100 + 1);
    QVector<double> y_arr((x_max_d+abs(x_min_d))*100 + 1);


    if (expr) {
        int arr_index = 0;
        for (float i=x_min_d; i<x_max_d; i+=0.01)
        {
            x = i;

            x_arr[arr_index]=x;

            double y = te_eval(expr); /* Returns 5. */
            y_arr[arr_index]=y;
            arr_index++;

        }
        te_free(expr);
    }

    else {
        QMessageBox msgBox;
        QString errormsg = "Error at character " + QString::number(err);
        if(equation[err-1].isLetter() && equation[err-1] != 'x')
        {
            errormsg += "\t \n you must use x as a variable only.  y = f(x) \t";
        }
        else if (equation[err-2].isSpace())
        {
            errormsg += "\t \n you should insert any operation in this space \t";
        }
        msgBox.setText(errormsg);
        msgBox.exec();
    }


    // create graph and assign data to it:
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(x_arr, y_arr);
    // set axes ranges, so we see all data:
    ui->customplot->xAxis->setRange(x_min_d, x_max_d);
    ui->customplot->yAxis->setRange(y_min_d, y_max_d);
    ui->customplot->replot();
}


void MainWindow::on_customplot_customContextMenuRequested(const QPoint &pos)
{

}

