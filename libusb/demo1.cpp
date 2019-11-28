#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libusb.h"
 
static int LIBUSB_CALL
usb_arrived_callback(struct libusb_context *ctx, struct libusb_device *dev,
    libusb_hotplug_event event, void *userdata)
{
    struct libusb_device_handle *handle;
    struct libusb_device_descriptor desc;
    unsigned char buf[512];
    int rc;
 
    libusb_get_device_descriptor(dev, &desc);
    printf("Add usb device: \n");
    printf("\tCLASS(0x%x) SUBCLASS(0x%x) PROTOCOL(0x%x)\n",
        desc.bDeviceClass, desc.bDeviceSubClass, desc.bDeviceProtocol);
    printf("\tVENDOR(0x%x) PRODUCT(0x%x)\n", desc.idVendor, desc.idProduct);
    rc = libusb_open(dev, &handle);
    if (LIBUSB_SUCCESS != rc) {
        printf("Could not open USB device\n");
        return 0;
    }
 
    memset(buf, 0, sizeof(buf));
    rc = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, buf, sizeof(buf));
    if (rc < 0) {
        printf("Get Manufacturer failed\n");
    } else {
        printf("\tManufacturer: %s\n", buf);
    }
 
    memset(buf, 0, sizeof(buf));
    rc = libusb_get_string_descriptor_ascii(handle, desc.iProduct, buf, sizeof(buf));
    if (rc < 0) {
        printf("Get Product failed\n");
    } else {
        printf("\tProduct: %s\n", buf);
    }
 
    memset(buf, 0, sizeof(buf));
    rc = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, buf, sizeof(buf));
    if (rc < 0) {
        printf("Get SerialNumber failed\n");
    } else {
        printf("\tSerialNumber: %s\n", buf);
    }
    libusb_close(handle);
 
    return 0;
}
 
static int LIBUSB_CALL
usb_left_callback(struct libusb_context *ctx, struct libusb_device *dev,
    libusb_hotplug_event event, void *userdata)
{
    struct libusb_device_descriptor desc;
 
    libusb_get_device_descriptor(dev, &desc);
    printf("Remove usb device: CLASS(0x%x) SUBCLASS(0x%x) iSerialNumber(0x%x)\n",
        desc.bDeviceClass, desc.bDeviceSubClass, desc.iSerialNumber);
 
    return 0;
}
 
int main(int argc, char **argv)
{
    libusb_hotplug_callback_handle usb_arrived_handle;
    libusb_hotplug_callback_handle usb_left_handle;
    libusb_context *ctx;
    int rc;
 
    libusb_init(&ctx);
    rc = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
        LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
        LIBUSB_HOTPLUG_MATCH_ANY, usb_arrived_callback, NULL, &usb_arrived_handle);
    if (LIBUSB_SUCCESS != rc) {
        printf("Error to register usb arrived callback\n");
        goto failure;
    }
 
    rc = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
        LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
        LIBUSB_HOTPLUG_MATCH_ANY, usb_left_callback, NULL, &usb_left_handle);
    if (LIBUSB_SUCCESS != rc) {
        printf("Error to register usb left callback\n");
        goto failure;
    }
 
    while (1) {
        libusb_handle_events_completed(ctx, NULL);
        usleep(1000);
    }
 
    libusb_hotplug_deregister_callback(ctx, usb_arrived_handle);
    libusb_hotplug_deregister_callback(ctx, usb_left_handle);
    libusb_exit(ctx);
 
    return 0;
 
failure:
    libusb_exit(ctx);
    return EXIT_FAILURE;
}
