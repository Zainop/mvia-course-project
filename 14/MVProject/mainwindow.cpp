#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "asmOpenCV.h"

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

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

bool MainWindow::loadFile(const QString &fileName)  //打开图片
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    /*const QImage*/
    image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        iv.imageLabel->setPixmap(QPixmap());
        iv.imageLabel->adjustSize();
        return false;
    }

      iv.imageLabel->setPixmap(QPixmap::fromImage(image));
       iv.scaleFactor = 1.0;
//       printAct->setEnabled(true);
       iv.fitToWindowAct->setEnabled(true);
       iv.updateActions();
       if(!iv.fitToWindowAct->isCheckable())
           iv.imageLabel->adjustSize();
       setWindowFilePath(fileName);

       iv.show();
    return true;
}


bool MainWindow::loadVideo(const QString &fileName) //打开视频
{
    Mat cimg; //定义Mat类
    Mat zy = cv::Mat::zeros(800,800,CV_8UC3); //定义一个800*800 黑色板
    using namespace cv;
    using namespace std;
    VideoCapture video(fileName.toStdString()); //视频导入
    int frameNum = -1;
    if (!video.isOpened()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        iv.imageLabel->setPixmap(QPixmap());
        iv.imageLabel->adjustSize();
        return false;
    }
    video >>frame; //流操作
    ++frameNum;
    image = ASM::cvMatToQImage(frame);

      iv.imageLabel->setPixmap(QPixmap::fromImage(image));
       iv.scaleFactor = 1.0;
       iv.fitToWindowAct->setEnabled(true);
       iv.updateActions();
       if(!iv.fitToWindowAct->isCheckable())

       setWindowFilePath(fileName);

       medianBlur(frame, frame, 5); //对第一帧图像进行处理
       cvtColor(frame,cimg,COLOR_BGR2GRAY);
      GaussianBlur(cimg, cimg, Size(9, 9), 2, 2);
       cvtColor(frame,cimg,COLOR_BGR2GRAY);
       vector<Vec3f> circles;
         HoughCircles(cimg, circles, HOUGH_GRADIENT, 1, 30,100, 30, 10, 120  );//霍夫圆形检测

          for (size_t i = 0; i < circles.size(); i++)
           {
                   Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //圆形坐标点
                   int radius = cvRound(circles[i][2]); //半径
                  circle(frame, center, 0, CV_RGB(255,0,0), 2, 8, 0); //画圆心
                  circle(frame, center, radius , Scalar(0, 0, 255), 3, 8, 0);//圆轮廓

                    circle(zy, center, 0, CV_RGB(255,0,0), 2, 8, 0); //实时显示轨迹（圆心坐标）

       cout << "圆心坐标：" << "X:"<<center.x<<" "<<"Y:"<< center.y<<endl; //实时显示圆心坐标
            }
iv.show();
       while(1){
           video >>frame; //对每一帧进行操作
           if (frame.empty()) //视频导入结束
           {
               cout << " < < <  Game over!  > > > ";
               break;
           }

           ++frameNum;
           image = ASM::cvMatToQImage(frame);

             iv.imageLabel->setPixmap(QPixmap::fromImage(image));
              iv.scaleFactor = 1.0;

              iv.fitToWindowAct->setEnabled(true);
              iv.updateActions();
              if(!iv.fitToWindowAct->isCheckable())
                  iv.imageLabel->adjustSize();
              setWindowFilePath(fileName);
              medianBlur(frame, frame, 5); //图像处理
              cvtColor(frame,cimg,COLOR_BGR2GRAY);
             GaussianBlur(cimg, cimg, Size(9, 9), 2, 2);
              cvtColor(frame,cimg,COLOR_BGR2GRAY);
              vector<Vec3f> circles;

                HoughCircles(cimg, circles, HOUGH_GRADIENT, 1, 30,100, 30, 10, 120  );

                 for (size_t i = 0; i < circles.size(); i++)
                  {
                          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                          int radius = cvRound(circles[i][2]);
                          circle(frame, center, 0, CV_RGB(255,0,0), 2, 8, 0);
                                                    circle(frame, center, radius , Scalar(0, 0, 255), 3, 8, 0);
                          circle(zy, center, 0, CV_RGB(255,0,0), 2, 8, 0);
  imshow("轨迹",zy);

              cout << "圆心坐标：" << "X:"<<center.x<<" "<<"Y:"<< center.y<<endl ;
                   }

        char c = (char)waitKey(20);


}

   return true;


}

bool MainWindow::go() //形状识别函数
{
      Mat zy3=imread("轨迹.jpg"); //读取摄像头识别后的轨迹图
     vector<vector<Point>> contours; //定义vector类
     ifstream circle; //读取轨迹坐标点，存入vector<Point>类中
     vector<Point> points;
     Point temp;
     double temp1=0,temp2=0;
     circle.open("轨迹点.txt");
     for(int i=0;!circle.eof();i++)
{
         circle>>temp1>>temp2;
         temp.x=temp1;
         temp.y=temp2;
         points.push_back(temp);

}
     contours.push_back(points);//将坐标点存入contours
     Mat zy2 = cv::Mat::zeros(1000,1000,CV_8UC3); // 创建1000*1000黑色画板

     vector<Point> zy; //定义vector类
     vector<vector<Point>> zy1;

    for (int t = 0; t < contours.size(); t++) //将轨迹点进行多边形拟合
    {

        int epsilon =0.1 * arcLength(contours[t], true);
        approxPolyDP(contours[t], zy, epsilon, true);

    }
        zy1.push_back(zy); //将拟合后的点存入zy1中
for (int t = 0; t < contours.size(); t++) //在画板中画出拟合后的图形
    {

        drawContours(zy2, zy1, -1, Scalar(0, 0, 255), 2, 8, Mat(), 0, Point());

    }

   imshow("轨迹",zy3); //展示轨迹点图
 if (zy.size() == 4) //通过拟合后点的个数判断运动轨迹形状
        {
            imshow("Rect", zy2);
            cout << "形状：" << "rect" <<endl;
            cout << "点的数目：" << zy.size() << endl;
                                                    }
if (zy.size() == 3)
        {
             imshow("Triangle", zy2);
             cout << "形状：" << "triangle" << endl;
             cout << "点的数目：" << zy.size() << endl;
                                                     }

 if (zy.size() >=5)
        {
              imshow("Circle", zy2);
              cout << "形状：" << "circle" <<endl;
              cout << "点的数目：" << zy.size() << endl;
                                                    }

  if (zy.size() ==2)
         {
             double k=( zy[0].y- zy[1].y)/(zy[0].x - zy[1].x);//通过斜率判断水平线或垂直线

             if((k>=-1)&&(k<=1))
             {
                 cout << "形状：" << "水平线" <<endl;
                 cout << "点的数目：" << zy.size() << endl;
                 imshow("Line", zy2);
                                        }
                else
             {

               imshow("Line", zy2);
               cout << "形状：" << "垂直线" <<endl;
                cout << "点的数目：" << zy.size() << endl;
             }
}
              waitKey(0);
              return 0;
}






bool MainWindow::OpenCamera() //打开摄像头并进行霍夫圆检测，得到轨迹点。
{

     Mat frame; //定义Mat类
     VideoCapture cap(0);//打开摄像头
     Mat cimg2;
     Mat zy2 = cv::Mat::zeros(800,800,CV_8UC3);//定义800*800黑色画板
     using namespace cv;

     using namespace std;
     char c=0;
     remove("轨迹点.txt"); //删除之前存放的轨迹点txt文件

        while(1)
        {
               cap >>frame; //处理摄像头每一帧图形

               medianBlur(frame, frame, 5);
               cvtColor(frame,cimg2,COLOR_BGR2GRAY);
               GaussianBlur(cimg2, cimg2, Size(9, 9), 2, 2);

              fstream fout; //创建 轨迹点.txt文件用于存放识别的到的坐标点
              fout.open("轨迹点.txt",ios::app);

               vector<Vec3f> circles; //定义vector类

               vector<Point2d> pt1;

               HoughCircles(cimg2, circles, HOUGH_GRADIENT, 1, 10,100, 40, 5, 50  ); // 对每一帧进行霍夫圆检测

                  for (size_t i = 0; i < circles.size(); i++)
                   {
                           Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //圆心
                           int radius = cvRound(circles[i][2]);//半径
                           circle(frame, center, 0, CV_RGB(255,255,0), 2, 8, 0);//画出识别圆心
                           circle(frame, center, radius , Scalar(0, 0, 255), 3, 8, 0);//画出识别的圆
                           line(zy2,cvPoint(center.x,center.y),cvPoint(center.x,center.y),CV_RGB(255,0,0),3,CV_AA,0);//在画板画出轨迹图
                           pt1.push_back(Point2d(cvRound(circles[i][0]),cvRound(circles[i][1])));//将圆心轨迹点存入pt1中

                           cout<<pt1[i]<<endl; //显示轨迹坐标
                          fout << center.x<<' '<< center.y << endl;//存放轨迹点

                    }
 fout.close();//关闭 轨迹点.txt文件

                  namedWindow("轨迹"); //定义名为 轨迹 窗口
                  imshow("轨迹",zy2); //实时显示 轨迹
                  namedWindow("摄像头"); //显示摄像头影像
                  imshow("摄像头",frame);


         char c = (char)waitKey(20); //按下Esc 保存轨迹图，关闭摄像头，关闭实时轨迹图
         if (c ==27)
         {
             imwrite("轨迹.jpg",zy2);
             destroyWindow( "摄像头");
             destroyWindow( "轨迹");
             cap.release();
             break;
         }

        }

     return 0;
 }
void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_openimage_clicked()
{  QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName,QImageReader::supportedMimeTypes())
    mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                      picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}


void MainWindow::on_pushButton_openvideo_clicked()
{
    QStringList mimeTypeFilters;
//    foreach (const QByteArray &mimeTypeName,QImageReader::supportedMimeTypes())
    mimeTypeFilters.append("video/avi");
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                      picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("video/avi");

    while (dialog.exec() == QDialog::Accepted && !loadVideo(dialog.selectedFiles().first())) {}

}

void MainWindow::on_pushButton_opencamera_clicked()
{
    OpenCamera();
}



void MainWindow::on_go_clicked()
{
    go();
}
