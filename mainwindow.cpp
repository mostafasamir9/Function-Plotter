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
    ui->customplot->xAxis->setRange(-5, 5);
    ui->customplot->yAxis->setRange(-5, 5);
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

    // if the expression is empty
    if(equation.isEmpty()){
        displayMessage("You didn't enter the function!");
        return;
    }
    // if the expression is begin with x and /
    if (equation[0] == '*' ||equation[0] == '/')
    {
        displayMessage("You can't begin the expression with multiply and divison!");
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
            return;
        }
    }

    if(emptyinput){
        displayMessage("You didn't enter an expression!");
        return;
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


    /********************* ranges validation *************************/
    if(x_max_d<x_min_d){
        displayMessage("x_min can't be bigger than x_max!");
        return;
    }

    if(y_max_d<y_min_d){
        displayMessage("y_min can't be bigger than y_max!");
        return;
    }

    // Getting equation string
    equation = equation.toLower();


    /********************** Parsing the equation ****************************/

    // Convert the string to chars array because of the mathmatical parser library
    QByteArray chararray = equation.toLocal8Bit(); // string -> qbytearray
    char* expression = chararray.data(); // qbytearray -> char*

    //Initial the vectors
    //precision is 100
    QVector<double> x_arr((x_max_d+abs(x_min_d))*PRECISION + 1);
    QVector<double> y_arr((x_max_d+abs(x_min_d))*PRECISION + 1);

    // call the parsing function
    parseEquation(expression, equation, x_arr, y_arr, x_min_d , x_max_d);

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
    //todo
}

