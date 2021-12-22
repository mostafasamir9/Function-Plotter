#include "bits/stdc++.h"
#include "functions.h"
#include <QMainWindow>
#include "QMessageBox"
void displayMessage(QString msg){
QMessageBox msgBox;
QString errormsg = msg;
msgBox.setText(errormsg);
msgBox.exec();
}
