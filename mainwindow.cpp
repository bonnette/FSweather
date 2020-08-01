#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this); // set up timer
    connect(timer,SIGNAL(timeout()),this,SLOT(getWeather()));
    timer->start(30000); // Starting the 30 second timer
    getWeather(); // Get weather from weather station for the first time
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getWeather() // This function will get kicked off when timer times out
{
    QDate date = QDate::currentDate();
    ui->date_lbl->setText(date.toString("MMM-dd-yyyy"));
    QTime time = QTime::currentTime();
    ui->time_lbl->setText(time.toString("h:mm AP t")); //formats time to HH:MM in AM/PM and time Zone

    // Network
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("http://192.168.0.196/wthrdata.dat") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll(); // strReply holds the full data stream from weather station

        //qDebug() << strReply;

        //ui->incomingtxtlbl->setText(strReply); // Places all of the weather station text into a large label.

        //qDebug() << strReply.data()[20]; // 20th char is outdoor temperature

        QString ODtemp = ""; //Out Door Temperature
        for (int i = 20; i <=23; ++i) {
            ODtemp.append(strReply.data()[i]);
        }
        double tempNum = ODtemp.toDouble();  //Convert  string to double
        tempNum = (tempNum * 1.8) + 32; //Conver 'C' to 'F'
        QString nODtemp = QString::number(tempNum, 'f', 1);  //Convert double to string to display in label
        ui-> temp_lbl ->setText(nODtemp + " F");

        QString humid = "";
         for (int i = 25; i <=28; ++i) {
             humid.append(strReply.data()[i]);
         }
         ui->humid_lbl->setText(humid + " %");

         QString dir = ""; // Current wind direction
         for (int i = 60; i <=64; ++i) {
             dir.append(strReply.data()[i]);
         }
         //qDebug() << dir;

         double bdir = dir.toDouble();
         // bdir = 68;
         //qDebug() << bdir;

         if (bdir >= 0 && bdir < 22){
             ui->dir_lbl->setText("North");
         }
         else if (bdir >= 22 && bdir < 45){
             ui->dir_lbl->setText("NNE");
         }
         else if (bdir >= 45 && bdir < 67){
             ui->dir_lbl->setText("NE");
         }
         else if (bdir >= 67 && bdir < 90){
             ui->dir_lbl->setText("ENE");
         }
         else if (bdir >= 90 && bdir < 112){
             ui->dir_lbl->setText("East");
         }
         else if (bdir >= 112 && bdir < 135){
             ui->dir_lbl->setText("ESE");
         }
         else if (bdir >= 135 && bdir < 157){
             ui->dir_lbl->setText("SE");
         }
         else if (bdir >= 157 && bdir < 180){
             ui->dir_lbl->setText("SSE");
         }
         else if (bdir >= 180 && bdir < 202){
             ui->dir_lbl->setText("South");
         }
         else if (bdir >= 202 && bdir < 225){
             ui->dir_lbl->setText("SSW");
         }
         else if (bdir >= 225 && bdir < 247){
             ui->dir_lbl->setText("SW");
         }
         else if (bdir >= 247 && bdir < 270){
             ui->dir_lbl->setText("WSW");
         }
         else if (bdir >= 270 && bdir < 292){
             ui->dir_lbl->setText("West");
         }
         else if (bdir >= 292 && bdir < 315){
             ui->dir_lbl->setText("WNW");
         }
         else if (bdir >= 315 && bdir < 337){
             ui->dir_lbl->setText("NW");
         }
         else if (bdir >= 337 && bdir < 359){
             ui->dir_lbl->setText("NNW");
         }

         QString speed = ""; // Current wind speed
         for (int i = 50; i <=53; ++i) {
             speed.append(strReply.data()[i]);
         }
         double bspeed = speed.toDouble();  //Convert  string to double
         bspeed = bspeed * 0.62137119223733; //Convert kph to mph
         QString nspeed = QString::number(bspeed,'f',1);  //Convert double to string to display in label the "(num,'f',2)" formats for 2 decimal places only.

         ui->speed_lbl->setText(nspeed + " MPH");

         QString gust = ""; // Current wind gust
         for (int i = 55; i <=58; ++i) {
             gust.append(strReply.data()[i]);
         }
         double bgust = gust.toDouble();  //Convert  string to double
         bgust = bgust * 0.62137119223733; //Convert kph to mph and round out the number
         QString ngust = QString::number(bgust,'f',1);  //Convert double to string to display in label the "(num,'f',2)" formats for 2 decimal places only.

         ui->gust_lbl->setText("Gust " + ngust);

         QString press = ""; // Barometric pressure in milibars
         for (int i = 35; i <=42; ++i) {
             press.append(strReply.data()[i]);
         }
         //qDebug() << press;
         double bpress = press.toDouble();  //Convert  string to double
         bpress = (bpress * 0.029530) / 100; //Convert milibar to inches of mercury
         QString npress = QString::number(bpress,'f',2);  //Convert double to string to display in label the "(num,'f',2)" formats for 2 decimal places only.

         ui->press_lbl->setText(npress);
}
}

