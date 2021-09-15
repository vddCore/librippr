#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>

#include "librippr.h"

static rippr_error_t g_current_error;

rippr_screencap_t* RIPPR_screenshot(void) {
    rippr_screencap_t* ret_val = NULL;

    xcb_connection_t* x_connection = xcb_connect(NULL, NULL);

    if (!x_connection) {
        g_current_error = RIPPR_E_XCB_CONNECTION;
        goto __exit;
    }

    const xcb_setup_t* setup = xcb_get_setup(x_connection);

    if (!setup) {
        g_current_error = RIPPR_E_XCB_SETUPDATA;
        goto __exit;
    }

    xcb_screen_iterator_t screen_iterator = xcb_setup_roots_iterator(setup);
    xcb_window_t root = screen_iterator.data->root;

    xcb_get_geometry_reply_t* geometry_reply = xcb_get_geometry_reply(
        x_connection, 
        xcb_get_geometry(x_connection, root),
        NULL
    );

    if (!geometry_reply) {
        g_current_error = RIPPR_E_XCB_GEOMETRY;
        goto __exit;
    }

    xcb_get_image_reply_t* image_reply = xcb_get_image_reply(
        x_connection,
        xcb_get_image(
            x_connection,
            XCB_IMAGE_FORMAT_Z_PIXMAP,
            root,
            0,
            0,
            geometry_reply->width,
            geometry_reply->height,
            (uint32_t)0xFFFFFFFFU
        ),
        NULL
    );

    if (!image_reply) {
        g_current_error = RIPPR_E_XCB_IMAGE_REPLY;
        goto __exit;
    }

    uint8_t* image_data = xcb_get_image_data(image_reply);

    if (!image_data) {
        g_current_error = RIPPR_E_XCB_IMAGE_DATA;
        goto __exit;
    }

    size_t image_data_len = xcb_get_image_data_length(image_reply);

    ret_val = (rippr_screencap_t*)malloc(sizeof(rippr_screencap_t));

    if (!ret_val) {
        g_current_error = RIPPR_E_OUT_OF_MEMORY;
        goto __exit;
    }

    ret_val->width = geometry_reply->width;
    ret_val->height = geometry_reply->height;
    ret_val->img_data_size = image_data_len;
    ret_val->img_data = (uint8_t*)malloc(image_data_len);

    if (!ret_val->img_data) {
        g_current_error = RIPPR_E_OUT_OF_MEMORY;
        free(ret_val);

        goto __exit;
    }

    memcpy(ret_val->img_data, image_data, image_data_len);

__exit:
    if (image_reply) {
        free(image_reply);
        image_reply = NULL;
    }

    if (geometry_reply) {
        free(geometry_reply);
        geometry_reply = NULL;
    }

    if (x_connection) {
        xcb_disconnect(x_connection);
        x_connection = NULL;
    }

    g_current_error = RIPPR_E_SUCCESS;
    return ret_val;
}

void RIPPR_free_screenshot(rippr_screencap_t* screencap) {
    if (!screencap) {
        return;
    }

    if (screencap->img_data) {
        free(screencap->img_data);
    }

    free(screencap);
}

rippr_error_t RIPPR_get_error(void) {
    return g_current_error;
}