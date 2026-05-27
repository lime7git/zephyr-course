#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(board, LOG_LEVEL_INF);

void board_early_init_hook(void)
{
    LOG_INF("Board Initialized");
}