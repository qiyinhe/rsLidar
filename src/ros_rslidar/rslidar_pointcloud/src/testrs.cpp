#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <string>
#include <sstream>

int k=0;//点云数计数器

std::string pcdName(int i){
    std::string si;
    std::stringstream st;
	st<<i;
	st>>si;
	return "/home/qiyinhe/rsData/"+si+".pcd";
}

void rslidarCallback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(*msg,pcl_pc2);
    pcl::PointCloud<pcl::PointXYZI>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);
    pcl::io::savePCDFileASCII(pcdName(++k),*temp_cloud);
    std::cout<<k<<"\n";
    /*std::cout<<"width:"<<temp_cloud->width<<" height:"<<temp_cloud->height<<"width*height:"<<temp_cloud->width * temp_cloud->height;
    for(int i=0;i<=temp_cloud->size();++i){
        std::cout<<"point i:"<<i<<"\n";
        std::cout<<"x="<<temp_cloud->points[i].x<<"\n";
        std::cout<<"y="<<temp_cloud->points[i].y<<"\n";
        std::cout<<"z="<<temp_cloud->points[i].z<<"\n";
    }*/
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "testrs");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("rslidar_points", 10, rslidarCallback);
    ros::spin();
    return 0;
}
