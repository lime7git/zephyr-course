#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#define SLEEP_TIME_MS 250

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(led0)
#define LED_NODE1 DT_ALIAS(led1)
#define LED_NODE2 DT_ALIAS(led2)
//#define LED_NODE3 DT_ALIAS(led3)

static const struct device * driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED_NODE1, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED_NODE2, gpios);
//static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED_NODE3, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;
    if (!gpio_is_ready_dt(&led1)) return 0;
    if (!gpio_is_ready_dt(&led2)) return 0;
    //if (!gpio_is_ready_dt(&led3)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    if (gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    //if (gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        //if (gpio_pin_toggle_dt(&led) < 0) return 0;
        if (gpio_pin_toggle_dt(&led1) < 0) return 0;
        //if (gpio_pin_toggle_dt(&led2) < 0) return 0;
        //if (gpio_pin_toggle_dt(&led3) < 0) return 0;

        if(led_state) sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, NULL);
        else sensor_sample_fetch(driver);

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
