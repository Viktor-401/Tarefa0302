#include "pico/stdlib.h"
#include "hardware/pio.h"

#define LED_COUNT 25

const int translated_indexes[LED_COUNT][2] = {
    {4,4},
    {4,3},
    {4,2},
    {4,1},
    {4,0},
    {3,0},
    {3,1},
    {3,2},
    {3,3},
    {3,4},
    {2,4},
    {2,3},
    {2,2},
    {2,1},
    {2,0},
    {1,0},
    {1,1},
    {1,2},
    {1,3},
    {1,4},
    {0,4},
    {0,3},
    {0,2},
    {0,1},
    {0,0}
    };

void matriz_update(PIO pio, uint sm, const int matriz[5][5])
{
    for (int k = 0; k < LED_COUNT; k++)
    {
        int i = translated_indexes[k][0];
        int j = translated_indexes[k][1];
        pio_sm_put_blocking(pio, sm, matriz[i][j]);
        pio_sm_put_blocking(pio, sm, matriz[i][j]);
        pio_sm_put_blocking(pio, sm, matriz[i][j]);
    }
}