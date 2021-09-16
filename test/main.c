#include <stdio.h>
#include <librippr.h>

int main(int argc, char** argv) {
    rippr_screencap_t* cap = RIPPR_screenshot();

    if (!cap) {
        printf("librippr error %d\n", RIPPR_get_error());
        return -1;
    }

    printf("%dx%d\n", cap->width, cap->height);

    FILE* fp = fopen("screenshot.bgra", "w+");

    if (!fp) {
        printf("fopen failed\n");
        RIPPR_free_screenshot(cap);
        
        return -2;
    }

    fwrite(cap->img_data, cap->img_data_size, 1, fp);
    fclose(fp);

    RIPPR_free_screenshot(cap);

    return 0;
}