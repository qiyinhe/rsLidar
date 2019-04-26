/*
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** @file

    This ROS nodelet converts raw RSLIDAR 3D LIDAR packets to a
    PointCloud2.

*/

#include <ros/ros.h>
#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

#include "convert.h"

namespace rslidar_pointcloud
{
class CloudNodelet : public nodelet::Nodelet
{
public:
  CloudNodelet()
    :cloud_viewer_ (new pcl::visualization::PCLVisualizer ("PCL Cloud")),
    color_handler ("intensity")
    {
      cloud_viewer_->addCoordinateSystem (3.0);//添加坐标轴
      cloud_viewer_->setBackgroundColor (0, 0, 0);//设置背景颜色
      cloud_viewer_->initCameraParameters ();//初始化摄像头参数
      cloud_viewer_->setCameraPosition (0.0, 0.0, 30.0, 0.0, 1.0, 0.0, 0);//在指定的viewport中设置摄像头参数，前三个参数为位置，后三个为视向
      cloud_viewer_->setCameraClipDistances (0.0, 50.0);

    }
  ~CloudNodelet()
  {}

private:
  virtual void onInit();
  boost::shared_ptr<Convert> conv_;

  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;//定义一个PCLVisualizer类的共享指针
  pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler;

};

/** @brief Nodelet initialization. */
void CloudNodelet::onInit()
{
  conv_.reset(
          new Convert(getNodeHandle(),
              getPrivateNodeHandle(),
              cloud_viewer_,
              color_handler));
}

}  // namespace velodyne_pointcloud

// Register this plugin with pluginlib.  Names must match nodelets.xml.
//
// parameters: class type, base class type
PLUGINLIB_EXPORT_CLASS(rslidar_pointcloud::CloudNodelet, nodelet::Nodelet)
