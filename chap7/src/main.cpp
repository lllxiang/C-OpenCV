#include <opencv2/opencv.hpp>
#include <stdio.h>
#include<iostream>
/*
 * remap() map_x and map_y是两个同输入输出图片相同shape的mat
 * map_x = [0,1,2,3,4,...]
 * 	   [0,1,2,3,4,...]
 * 	   [0,1,2,3,4,...]
 *map_y = [480,480,480,...]
 *	  [479,479,479,...]
 * 	  [478,478,478,...]
 * 表示将a图像的(m,n)位置的像素点，映射至b图像的(map_x(m,b),map_y(m,n))
 * 位置点
 */
int main(){
  cv::Mat srcImage, dstImage;
  cv::Mat map_x, map_y;
  srcImage = cv::imread( "/home/lx/data/demo.jpg", 1 );
  cv::resize(srcImage, srcImage, cv::Size(640, 480));
  if(!srcImage.data ) 
  { 
    printf("read error!\n"); 
    return false; 
  }  
  cv::imshow("src",srcImage);
  dstImage.create( srcImage.size(), srcImage.type());
  map_x.create( srcImage.size(), CV_32FC1 );
  map_y.create( srcImage.size(), CV_32FC1 );
  for( int j = 0; j < srcImage.rows;j++) //hang 
  { 
    for( int i = 0; i < srcImage.cols;i++)
    {
      map_x.at<float>(j,i) = static_cast<float>(i);
      map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
    }
  }
  cv::Mat roi_mapx  = map_x(cv::Rect(0,0,5,5));
  cv::Mat roi_mapy = map_y(cv::Rect(0,0,5,5));
  std::cout<<roi_mapx<<std::endl;
  std::cout<<roi_mapy<<std::endl;

  cv::remap( srcImage, dstImage, map_x, map_y, cv::INTER_LINEAR, 
	     cv::BORDER_CONSTANT, cv::Scalar(0,0, 0) );
  cv::imshow( "dst", dstImage);
  cv::waitKey();
  return 0;
}










