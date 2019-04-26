/* -*- mode: C++ -*- */
/*
 *  Copyright (C) 2009, 2010 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2011 Jesse Vera
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2017 Robosense, Tony Zhang
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** @file

    This class converts raw Robosense 3D LIDAR packets to PointCloud2.

*/
#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <sensor_msgs/PointCloud2.h>
#include <dynamic_reconfigure/server.h>
#include <rslidar_pointcloud/CloudNodeConfig.h>
#include "rawdata.h"
#include <pcl/filters/filter.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>//点云类定义头文件
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <string>
#include <sstream>
using namespace std;

namespace rslidar_pointcloud
{
class Convert
{
public:
  Convert(ros::NodeHandle node,
          ros::NodeHandle private_nh,
          boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_,
          pcl::visualization::PointCloudColorHandler<pcl::PointXYZI> &handler
          );

  ~Convert()
  {
  }

private:
  void callback(rslidar_pointcloud::CloudNodeConfig& config, uint32_t level);
  void processScan(const rslidar_msgs::rslidarScan::ConstPtr& scanMsg);
  void ros2pcl(sensor_msgs::PointCloud2& msg);
  void view();
  void processCloud(sensor_msgs::PointCloud2& msg);
  /// Pointer to dynamic reconfigure service srv_
  boost::shared_ptr<dynamic_reconfigure::Server<rslidar_pointcloud::CloudNodeConfig> > srv_;

  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_;
  int k;//the counter of pcl::PointCloud
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_;//定义一个PCLVisualizer类的共享指针
  pcl::visualization::PointCloudColorHandler<pcl::PointXYZI> &handler_;//定义点云颜色处理器

  boost::shared_ptr<rslidar_rawdata::RawData> data_;
  ros::Subscriber rslidar_scan_;
  ros::Publisher output_;
};

}  // namespace rslidar_pointcloud
#endif
