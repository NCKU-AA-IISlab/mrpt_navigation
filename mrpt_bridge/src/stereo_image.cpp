//
// Created by raghavender on 21/08/17.
//

#include "mrpt_bridge/stereo_image.h"



#include "ros/ros.h"
#include "mrpt_bridge/image.h"
#include <mrpt/utils.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

using namespace ros;
using namespace sensor_msgs;
using namespace cv;
using namespace mrpt::utils;
using namespace cv_bridge;


namespace mrpt_bridge
{
    namespace stereo_image
    {
        /*bool ros2mrpt(const sensor_msgs::Image &msg,  CObservationImage &obj)
        {
            CvImage *frame1 = cv_bridge::toCvCopy(msg, "bgr8").get(); //CvShare(msg,"bgr8").image;

        }
*/
        /************************************************************************
        *						mrpt2ros    							        *
        ************************************************************************/
         bool mrpt2ros(const CObservationStereoImages &obj,const std_msgs::Header &msg_header,
                      sensor_msgs::Image &left, sensor_msgs::Image &right,
                      stereo_msgs::DisparityImage &disparity)
        {

            /// left image
            CImage temp_img = obj.imageLeft;
            Mat cvImg = cv::cvarrToMat(temp_img.getAs<IplImage>());
            cv_bridge::CvImage img_bridge;
            img_bridge = CvImage(left.header, sensor_msgs::image_encodings::BGR8, cvImg);
            img_bridge.toImageMsg(left);
            left.encoding = "bgr8";
            left.header = msg_header;
            left.height = (int) obj.imageLeft.getHeight();
            left.width = (int) obj.imageRight.getWidth();

            /// right image
            CImage temp_img2 = obj.imageRight;
            Mat cvImg2 = cv::cvarrToMat(temp_img2.getAs<IplImage>());
            cv_bridge::CvImage img_bridge2;
            img_bridge2 = CvImage(right.header, sensor_msgs::image_encodings::BGR8, cvImg2);
            img_bridge2.toImageMsg(right);
            right.encoding = "bgr8";
            right.header = msg_header;
            right.height = (int) obj.imageLeft.getHeight();
            right.width = (int) obj.imageRight.getWidth();

            if(obj.hasImageDisparity)
            {
                CImage temp_disp = obj.imageDisparity;
                Mat cvImg3 = cv::cvarrToMat(temp_disp.getAs<IplImage>());
                cv_bridge::CvImage img_bridge3;
                img_bridge3 = CvImage(disparity.header, sensor_msgs::image_encodings::BGR8, cvImg3);
                img_bridge3.toImageMsg(disparity.image);
                disparity.image.encoding = "bgr8";
                disparity.image.header = msg_header;
                disparity.image.height = (int) obj.imageDisparity.getHeight();
                disparity.image.width = (int) obj.imageDisparity.getWidth();
            }
            return true;
        }
    }
}

//
/*
std_msgs/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
 */