#ifndef __LIBRIPPR_H
#define __LIBRIPPR_H

#include <stdint.h>
#include <stddef.h>

#define RIPPR_E_SUCCESS         0x00 /* All fine and dandy */
#define RIPPR_E_XCB_CONNECTION  0x01 /* Unable to establish connection to the X server */
#define RIPPR_E_XCB_SETUPDATA   0x02 /* Unable to retrieve setup data from XCB */
#define RIPPR_E_XCB_GEOMETRY    0x03 /* Unable to retrieve screen geometry data from XCB */
#define RIPPR_E_XCB_IMAGE_REPLY 0x04 /* Unable to retrieve screen image reply from XCB */
#define RIPPR_E_XCB_IMAGE_DATA  0x05 /* Unable to retrieve screen image data from XCB */
#define RIPPR_E_OUT_OF_MEMORY   0x06 /* Unable to allocate memory for screencap data */

typedef char rippr_error_t;

typedef struct {
    uint16_t width;
    uint16_t height;

    uint8_t* img_data;
    size_t img_data_size;
} rippr_screencap_t;

rippr_screencap_t* RIPPR_screenshot(void);
void RIPPR_free_screenshot(rippr_screencap_t*);
rippr_error_t RIPPR_get_error(void);

#endif // __LIBRIPPR_H