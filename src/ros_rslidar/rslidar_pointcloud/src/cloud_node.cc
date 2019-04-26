/*
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2016 Robosense, Tony Zhang
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** \file

    This ROS node converts raw RSLIDAR LIDAR packets to PointCloud2.

*/
#include "convert.h"

/** Main node entry point. */
int main(int argc, char** argv)
{
  ros::init(argc, argv, "cloud_node");
  ros::NodeHandle node;
  ros::NodeHandle priv_nh("~");

  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_(new pcl::visualization::PCLVisualizer ("PCL Cloud"));//定义一个PCLVisualizer类的共享指针
  pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler ("intensity");

  cloud_viewer_->addCoordinateSystem (3.0);//添加坐标轴
  cloud_viewer_->setBackgroundColor (0, 0, 0);//设置背景颜色
  cloud_viewer_->initCameraParameters ();//初始化摄像头参数
  cloud_viewer_->setCameraPosition (0.0, 0.0, 30.0, 0.0, 1.0, 0.0, 0);//在指定的viewport中设置摄像头参数，前三个参数为位置，后三个为视向
  cloud_viewer_->setCameraClipDistances (0.0, 50.0);

  // create conversion class, which subscribes to raw data
  rslidar_pointcloud::Convert conv(node,
          priv_nh,
          cloud_viewer_,
          color_handler);

  // handle callbacks until shut down
  ros::spin();

  return 0;
}
