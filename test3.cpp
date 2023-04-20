#include <k4a/k4a.h>
#include <k4abt.h>

int main() {
    // Initialize device
    k4a_device_t device = NULL;
    k4a_device_configuration_t device_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
    device_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
    k4a_device_open(0, &device);

    // Initialize tracker
    k4abt_tracker_t tracker = NULL;
    k4abt_tracker_configuration_t tracker_config = K4ABT_TRACKER_CONFIG_DEFAULT;
    k4abt_tracker_create(&device_config, tracker_config, &tracker);

    while (true) {
        // Get capture and enqueue
        k4a_capture_t capture = NULL;
        k4a_device_get_capture(device, &capture, K4A_WAIT_INFINITE);
        k4abt_tracker_enqueue_capture(tracker, capture, K4A_WAIT_INFINITE);
        k4a_capture_release(capture);

        // Pop result and get skeleton
        k4abt_frame_t body_frame = NULL;
        k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);
        size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
        for (size_t i = 0; i < num_bodies; i++) {
            k4abt_skeleton_t skeleton;
            k4abt_frame_get_body_skeleton(body_frame, i, &skeleton);
            // Process skeleton data here
            
        }
        k4abt_frame_release(body_frame);
    }

    // Clean up
    k4abt_tracker_destroy(tracker);
    k4a_device_close(device);
    return 0;
}