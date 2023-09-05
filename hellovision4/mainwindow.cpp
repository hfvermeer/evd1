#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
}

MainWindow::~MainWindow()
{
   delete ui;
}

using namespace cv;


void MainWindow::on_pbFile_clicked()
{
   Mat src;

   src = imread("c:\\circles.bmp",IMREAD_GRAYSCALE);
   if(!src.data) {
      ui->statusBar->showMessage(QString("Could not open image!"),0);
   }
   else {

      int height = src.rows, width = src.cols;
      QString info;

      // Get the image data
      info.append(QString("Image info: "));
      info.append(QString("height=%1 ").arg(height));
      info.append(QString("width=%1 ").arg(width));

      ui->statusBar->showMessage(info);

      // Create a window
      namedWindow("Original image", WINDOW_AUTOSIZE);
      moveWindow("Original image", 100, 100);


      // Show the image
      imshow("Original image",src);


      // Create bit image
      Mat dst(width,height,CV_8UC1,1);

      // Threshold
      threshold(src,dst,254,0,THRESH_TOZERO_INV);
      Mat cpy(width,height,CV_8UC1,1);

      multiply(src,dst,cpy);

      // Create a window
      namedWindow("Threshold", WINDOW_AUTOSIZE);
      moveWindow("Threshold", 450, 100);

      // Show the image
      imshow("Threshold",cpy);
   }
}

void MainWindow::on_pbSnapShot_clicked()
{
   QString info;
   VideoCapture Img;
   Img.open(0);

   if (!Img.isOpened()) {
      info.append(QString("Could not take a snapshot, probably no camera connected!"));
      ui->statusBar->showMessage(info,0);
   }
   else {

      Mat Cam;
      // Take first snapshot
      Img >> Cam;
      int height = Cam.rows, width = Cam.cols;
      // there is no frame
      if (!Cam.data) {
         info.append(QString("Snapshot taken but could not be converted to image!"));
         ui->statusBar->showMessage(info,0);
      }
      else {
         for (int i=0;i<100;i++) {
            // Create images
            Mat src(width,height,CV_8UC1,1);
            Mat dst(width,height,CV_8UC1,1);
            Mat Edge(width,height,CV_8UC1,1);

            // Take snapshot
            Img >> Cam;
            // Convert to grayscale
            cvtColor(Cam,src,COLOR_BGR2GRAY);
            // Threshold
            threshold(src,dst,130,255,THRESH_BINARY);
            // Edge detection
            Canny(src,Edge,150,255,3);

            // Create Windows
            namedWindow("Snapshot",WINDOW_AUTOSIZE);
            moveWindow("Snapshot",100,5);
            namedWindow("GrayScale",WINDOW_AUTOSIZE);
            moveWindow("GrayScale",650,5);
            namedWindow("Threshold",WINDOW_AUTOSIZE);
            moveWindow("Threshold",100,500);
            namedWindow("Edge",WINDOW_AUTOSIZE);
            moveWindow("Edge",650,500);

            // Show images
            imshow("Snapshot",Cam);
            imshow("GrayScale", src);
            imshow("Threshold",dst);
            imshow("Edge",Edge);
            QCoreApplication::processEvents();
         }
      }
   }

}
