#include <ros/subscriber.h>
#include <ros/timer.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include <nist_gear/Order.h>
#include <nist_gear/LogicalCameraImage.h>

#include <string>
#include <array>
#include <vector>

class AgilityChallenger
{
protected:
    tf2_ros::Buffer tf_buffer;
    tf2_ros::TransformListener tf_listener;

    ros::Subscriber orders_subs;
    ros::Subscriber logical_camera_bins0_sub;
    ros::Subscriber logical_camera_bins1_sub;
    std::array<ros::Subscriber, 4> quality_control_sensor_subs;
    ros::Timer watch_for_blackouts_tmr;
    ros::Timer watch_for_order_parts_tmr;

    std::string current_product0_type;
    std::string current_product1_type;
    std::array<std::vector<std::string>, 2> current_parts_found;
    bool current_all_parts_found;
    bool sensors_started;
    bool in_sensor_blackout;

    bool announced_part_frames;

    void help_logical_camera_image_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg, const int bin_idx);
    void help_quality_control_sensor_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg, const int agv_idx);
    bool evaluate_if_all_parts_found(const int bin_idx);

    void annouce_world_tf(const std::string part_name, const std::string frame);
    void order_callback(const nist_gear::Order::ConstPtr& msg);
    void logical_camera_image0_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void logical_camera_image1_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void quality_control_sensor0_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void quality_control_sensor1_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void quality_control_sensor2_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void quality_control_sensor3_callback(const nist_gear::LogicalCameraImage::ConstPtr& msg);
    void sensor_blackout_detected_callback(const ros::TimerEvent& evt);
    void handle_check_for_order_parts(const ros::TimerEvent& evt);

public:
    AgilityChallenger(ros::NodeHandle* const nh);
    ~AgilityChallenger();
};
