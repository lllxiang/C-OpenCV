#include <opencv2/opencv.hpp>
#include <stdio.h>
#include<iostream>

int main(){
  cv::Mat srcImage, dstImage;
  cv::Mat map_x, map_y;
  srcImage = cv::imread( "/home/lx/data/1.jpg", 1 );
    if(!srcImage.data ) 
  { 
    printf("read error!\n"); 
    return false; 
  }  
  cv::imshow("src",srcImage);
  
  cv::Mat camera_matrixa = (cv::Mat_<double>(3, 3) << 541.1788, 0.0, 644.1565, 0,
			    539.5916, 502.7171, 0, 0, 1); 
  
  cv::Mat dst_camera_matrixa = (cv::Mat_<double>(3, 3) << 541.1788*0.5, 0.0, 644.1565, 0,
			    539.5916*0.5, 502.7171, 0, 0, 1); 
  
  cv::Mat distortion_coefficientsa=(cv::Mat_<double >(1,4)<<-0.07071596,-0.0031326,
				    -0.00692476,0.00191935);
  cv::Size img_size = srcImage.size();
  cv::fisheye::initUndistortRectifyMap(camera_matrixa,distortion_coefficientsa,cv::Mat(),
    dst_camera_matrixa, img_size, CV_32FC1, map_x, map_y);
  map_x.convertTo(map_x, CV_16UC1, 1, 0);
  map_y.convertTo(map_y, CV_16UC1, 1, 0);
  map_x.convertTo(map_x, CV_32FC1, 1, 0);
  map_y.convertTo(map_y, CV_32FC1, 1, 0);
  
  std::vector<cv::Mat> mapx_c;
  cv::split(map_x, mapx_c);
  cv::Mat mapx_1 = mapx_c.at(0);


  cv::Mat inv_mapx;
  cv::Mat inv_mapy;
  cv::Mat inv_dst;
  inv_mapx = cv::Mat::zeros(map_x.size(), CV_32FC1);
  inv_mapy = cv::Mat::zeros(map_y.size(), CV_32FC1);
  
  for(int i=0; i<480;i++)
  {
    for(int j=0;j<640;j++)
    {
      int x = int(map_x.at<float>(i,j));
      int y = int(map_y.at<float>(i,j));
      inv_mapx.at<float>(y,x) = j;
      inv_mapy.at<float>(y,x) = i;
    }
  }

  //std::cout<<inv_mapx.at<float>(1,1)<<std::endl;
  //std::cout<<"inv_mapx"<<inv_mapx(cv::Rect(0,0,5,5))<<std::endl;
  //std::cout<<"inv_mapy"<<inv_mapy(cv::Rect(0,0,5,5))<<std::endl;
  
  
  cv::Mat roi_mapx1 = mapx_1(cv::Rect(0,0,5,5));
  //cv::Mat roi_mapx2 = mapx_2(cv::Rect(0,0,5,5));
  cv::Mat roi_mapy = map_y(cv::Rect(0,0,5,5));
 
  std::cout<<"roi_mapx1"<<roi_mapx1<<std::endl;
  //std::cout<<"roi_mapx2"<<roi_mapx2<<std::endl;
  std::cout<<"roi_mapy"<<roi_mapy<<std::endl;
  
  cv::remap(srcImage, dstImage, map_x, map_y, cv::INTER_LINEAR, 
	     cv::BORDER_CONSTANT, cv::Scalar(0,0, 0));
  
  cv::remap(dstImage, inv_dst, inv_mapx, inv_mapy, cv::INTER_LINEAR, 
	     cv::BORDER_CONSTANT, cv::Scalar(0,0, 0));
  cv::imshow( "dst", dstImage);
  cv::imshow( "inv_dst", inv_dst);
  cv::waitKey();
  return 0;
}










