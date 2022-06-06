#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
// v4l includes
#include <linux/videodev2.h>

#include <iostream>

int main() {
    int count = 0;
    char device[20];
    int fd = -1;
    bool found = false;
    struct v4l2_capability cap;
    for (int n = 0; n < 64; n++) {
        sprintf(device, "/dev/video%d", n);
        if ((fd = open(device, O_RDONLY)) != -1) {
            // query device capabilities and make sure this is a video capture device
            if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0 ||
                    !(cap.device_caps & V4L2_CAP_VIDEO_CAPTURE)) {
                close(fd);
                continue;
            }
            count++;
            char cameraName[64];

            char deviceNameUTF8[256] = {0};
            int deviceNameLength = sizeof (deviceNameUTF8);

            char deviceUniqueIdUTF8[256] = {0};
            int deviceUniqueIdUTF8Length = sizeof (deviceUniqueIdUTF8);
            memset(deviceNameUTF8, 0, deviceNameLength);
            memcpy(cameraName, cap.card, sizeof(cap.card));

            if (deviceNameLength > strlen(cameraName)) {
                memcpy(deviceNameUTF8, cameraName, strlen(cameraName));
            } else {
                std::cout << "buffer passed is too small" << std::endl;
                continue;
            }

            if (cap.bus_info[0] != 0)  // may not available in all drivers
            {
                // copy device id
                if (deviceUniqueIdUTF8Length > strlen((const char*)cap.bus_info)) {
                    memset(deviceUniqueIdUTF8, 0, deviceUniqueIdUTF8Length);
                    memcpy(deviceUniqueIdUTF8, cap.bus_info,
                            strlen((const char*)cap.bus_info));
                } else {
                    std::cout << "buffer passed is too small";
                    continue;
                }
            }
            std::cout << "/dev/video" << n << ": "
                        << "deviceNameUTF8: " << deviceNameUTF8 << ", "
                        << "deviceUniqueIdUTF8: " << deviceUniqueIdUTF8 << ". " << std::endl;
            close(fd);
        }
    }

    return 0;
}
