#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>   
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "blink.pio.h"
#include "ws2818b.pio.h"
#include "ws2818b_interface.c" //Interface criada pelo autor, para facilitar a utilização da matriz
#include "numbers.c" //Matrizes correspontentes aos números de 0 a 9
#include <math.h>
#include "hardware/pwm.h"

#define RED_LED_PIN 13
#define BUTTON_A 5
#define BUTTON_B 6
#define MATRIZ_PIN 7

//Função debounce, para retirar ruidos ao pressionar o botão
bool debounce();
//Função para piscar o led vermelho utilizando PIO
void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq);
//Callback da interrupção do botão
void button_press(uint gpio, uint32_t events); 
void configure_pwm(uint gpio);

PIO pio = pio0;
//Index das states machines
uint sm_blink = 0;
uint sm_ws = 1;
//Número mostrado na matriz
int displayed_number = 0;
//Última vez que o botão foi pressionado, usado na função de debounce
absolute_time_t last_press = {0};

int main()
{
    stdio_init_all();

    //Inicialização do programa de piscar o led vermelho no PIO
    uint offset_blink = pio_add_program(pio, &blink_program);
    blink_pin_forever(pio, sm_blink, offset_blink, RED_LED_PIN, 5);

    //Inicialização dos botões
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    //Habilitação das interrupções acionadas pelos botões, ativam em borda de descida
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_press);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_press);

    //Inicialização do programa da matriz de leds
    uint offset_ws = pio_add_program(pio0, &ws2818b_program);
    ws2818b_program_init(pio, sm_ws, offset_ws, MATRIZ_PIN, 800000.f);

    //A matriz de leds mostra zero inicialmente
    matriz_update(pio, sm_ws, zero);

    while (true)
    {
        //Mantém o programa rodando
        tight_loop_contents();
    }
}
//Compara o tempo atual com o tempo em que o botão foi pressionado pela última vez e determina se o sinal deve ser aceito
bool debounce()
{
    absolute_time_t time = get_absolute_time();

    if (absolute_time_diff_us(last_press, time) >= 200000) 
    {
        last_press = time;
        return true;
    }
    return false;
}

//Função para piscar o led vermelho utilizando PIO
void blink_pin_forever(PIO pio, uint sm_blink, uint offset, uint pin, uint freq) 
{
    blink_program_init(pio, sm_blink, offset, pin);
    pio_sm_set_enabled(pio, sm_blink, true);
    pio->txf[sm_blink] = (125000000 / (2 * freq)) - 3;
}

//Callback da interrupção do botão
void button_press(uint gpio, uint32_t events)
{
    //Determina qual botão foi pressionado, e então realiza a ação correspondente
    if (gpio == BUTTON_A && debounce())
    {
        displayed_number++;
        printf("Added one\n");
    }
    else if (gpio == BUTTON_B && debounce())
    {
        displayed_number--;
        printf("Subtracting one\n");
    }

    //Limita o número mostrado entre 0 e 9
    if(displayed_number > 9)
    {
        displayed_number = 9;
    }
    else if(displayed_number < 0)
    {
        displayed_number = 0;
    }
    printf("Number: %d\n", displayed_number);

    //Atualiza a matriz de leds com o número correspondente
    switch (displayed_number)
        {
        case 0:
            matriz_update(pio, sm_ws, zero);
            break;
        case 1:
            matriz_update(pio, sm_ws, one);
            break;
        case 2:
            matriz_update(pio, sm_ws, two);
            break;
        case 3:
            matriz_update(pio, sm_ws, three);
            break;
        case 4: 
            matriz_update(pio, sm_ws, four);
            break;
        case 5:
            matriz_update(pio, sm_ws, five);
            break;
        case 6:
            matriz_update(pio, sm_ws, six);
            break;
        case 7:
            matriz_update(pio, sm_ws, seven);
            break;
        case 8:
            matriz_update(pio, sm_ws, eight);
            break;
        case 9:
            matriz_update(pio, sm_ws, nine);
            break;
        }
}