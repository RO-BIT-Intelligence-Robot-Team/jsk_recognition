// -*- mode: C++ -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, Yuto Inagaki and JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the JSK Lab nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef __JSK_PCL_ROS_OCTREE_CHANGE_PUBLISHER_H__
#define __JSK_PCL_ROS_OCTREE_CHANGE_PUBLISHER_H__

// ros
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <dynamic_reconfigure/server.h>
#include <jsk_pcl_ros/OctreeChangePublisherConfig.h>
#include <pcl_conversions/pcl_conversions.h>

// pcl
#include <pcl_ros/pcl_nodelet.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/octree/octree.h>
#include <jsk_topic_tools/connection_based_nodelet.h>

namespace jsk_pcl_ros
{
  /**
   * @brief
   * Realtime change detection of pointcloud using octree. See paper below:
   *
   @INPROCEEDINGS{6224647, 
   author={Kammerl, J. and Blodow, N. and Rusu, R.B. and Gedikli, S. and Beetz, M. and Steinbach, E.}, 
   booktitle={Robotics and Automation (ICRA), 2012 IEEE International Conference on}, 
   title={Real-time compression of point cloud streams}, 
   year={2012}, 
   pages={778-785}, 
   keywords={cloud computing;data compression;tree data structures;coding complexity;coding precision;novel lossy compression approach;octree data structures;point cloud streams;real-time compression;spatial decomposition;temporal redundancy;Decoding;Encoding;Entropy;Octrees;Real time systems;Sensors}, 
   doi={10.1109/ICRA.2012.6224647}, 
   ISSN={1050-4729}, 
   month={May},}
   */
  class OctreeChangePublisher: public jsk_topic_tools::ConnectionBasedNodelet
  {
  public:
    typedef OctreeChangePublisherConfig Config;
  protected:
    int counter_;
    int noise_filter_;
    double resolution_;
    boost::mutex mtx_;

    ros::Subscriber sub_;
    ros::Publisher diff_pub_;
    pcl::octree::OctreePointCloudChangeDetector<pcl::PointXYZRGB> *octree_;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered_cloud;
    boost::shared_ptr <dynamic_reconfigure::Server<Config> > srv_;

    virtual void
    cloud_cb (const sensor_msgs::PointCloud2 &pc);
    virtual void subscribe();
    virtual void unsubscribe();
    virtual void config_callback(Config &config, uint32_t level);
  private:
    virtual void onInit();
  };
}

#endif
