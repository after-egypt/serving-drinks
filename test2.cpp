#include <k4a/k4a.h>

int main(int argc, char const *argv[]) {
    // Initialize the Azure Kinect sensor and configure it
    k4a_device_t device = NULL;
    k4a_device_open(0, &device);

    k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
    config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
    config.color_resolution = K4A_COLOR_RESOLUTION_720P;
    config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
    config.camera_fps = K4A_FRAMES_PER_SECOND_30;

    k4a_device_start_cameras(device, &config);

    // Capture a frame from the sensor
    k4a_capture_t capture = NULL;
    k4a_device_get_capture(device, &capture, K4A_WAIT_INFINITE);

    // Convert the color image to an OpenCV matrix
    k4a_image_t color_image = k4a_capture_get_color_image(capture);
    cv::Mat color_mat(k4a_image_get_height_pixels(color_image), k4a_image_get_width_pixels(color_image),
                        CV_8UC4, k4a_image_get_buffer(color_image), cv::Mat::AUTO_STEP);

    // Convert the depth image to an OpenCV matrix
    k4a_image_t depth_image = k4a_capture_get_depth_image(capture);
    cv::Mat depth_mat(k4a_image_get_height_pixels(depth_image), k4a_image_get_width_pixels(depth_image),
                        CV_16UC1, k4a_image_get_buffer(depth_image), cv::Mat::AUTO_STEP);

    // Convert the 2D point to a depth value
    cv::Point2i point(320, 240);  // Example 2D point
    uint16_t depth_value = depth_mat.at<uint16_t>(point);

    // Map the depth value to 3D world coordinates
    k4a_float3_t point_3d;
    k4a_calibration_t calibration;
    k4a_device_get_calibration(device, config.depth_mode, config.color_resolution, &calibration);
    k4a_calibration_2d_to_3d(&calibration, &(k4a_float2_t){ point.x, point.y }, depth_value, K4A_CALIBRATION_TYPE_DEPTH,
                                K4A_CALIBRATION_TYPE_DEPTH, &point_3d, NULL);
    return 0;
}
