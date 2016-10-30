#include <stdio.h>
#include <stdlib.h>
#include <usb.h>

int main(int argc, char *args[]){
    char *e;
    int base;

    struct usb_bus *bus;
    struct usb_device *dev;
    usb_dev_handle *dh;
    int VENDOR_ID = strtol(getenv("KEYBOARD_VID"), &e, base);
    int PRODUCT_ID = strtol(getenv("KEYBOARD_PID"), &e, base);

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for(bus = usb_get_busses(); bus; bus = bus->next){
        for (dev = bus->devices; dev; dev = dev->next){
            if(dev->descriptor.idVendor == VENDOR_ID && dev->descriptor.idProduct == PRODUCT_ID){
                goto device_found;
            }
        }
    }

    fprintf(stderr, "Device not found.\n");
    exit(1);

    device_found:
    printf("Device Found!\n");

    /* USB Open */
    dh = usb_open(dev);
    if((dh=usb_open(dev))==NULL){
        printf("usb_open Error.(%s)\n", usb_strerror());
        exit(1);
    }

    usb_close(dh);

    return 0;
}
