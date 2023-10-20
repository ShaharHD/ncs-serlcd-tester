#include <string.h>
#include <zephyr/device.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(auxdisplay_sample, LOG_LEVEL_DBG);

int main(void)
{
    const struct device *const dev = DEVICE_DT_GET(DT_NODELABEL(serlcd_0));

    uint8_t data[64];

    k_sleep(K_MSEC(500));

    if (!device_is_ready(dev)) {
        LOG_ERR("Auxdisplay device not ready");
        return 0;
    }

    int rc = auxdisplay_cursor_set_enabled(dev, true);

    if (rc != 0) {
        LOG_ERR("Cursor enable failed: %d", rc);
    }

    auxdisplay_cursor_position_set(dev, AUXDISPLAY_POSITION_ABSOLUTE, 0, 0);
    snprintk(data, sizeof(data), "Board: %s", CONFIG_BOARD);
    rc = auxdisplay_write(dev, data, strlen(data));

    if (rc != 0) {
        LOG_ERR("Write failed: %d", rc);
    }

    int counter = 1;

    for (;;) {
        snprintk(data, sizeof(data), "Count: %i", counter);
        auxdisplay_cursor_position_set(dev, AUXDISPLAY_POSITION_ABSOLUTE, 0, 1);
        auxdisplay_write(dev, data, strlen(data));
        k_sleep(K_MSEC(1000));
        ++counter;
    }
    return 0;
}