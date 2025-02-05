#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/time.h"

#define LED_BLUE 12
#define LED_RED 13
#define LED_GREEN 11
#define BUTTON 5

volatile bool botao_press = false;
volatile bool sequence_exec = false;

// Callback para desligar o último LED e liberar o botão
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    sequence_exec = false; 
    return 0;
}

// Callback para ligar apenas um LED
int64_t turn_on_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 1);
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    return 0;
}

// Callback para ligar dois LEDs
int64_t turn_on_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 1);
    add_alarm_in_ms(3000, turn_on_green_callback, NULL, false);
    return 0;
}

// Callback inicial para ligar todos os LEDs
int64_t turn_on_all_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_RED, 1);
    gpio_put(LED_GREEN, 1);
    add_alarm_in_ms(3000, turn_on_red_callback, NULL, false);
    return 0;
}

// Função de interrupção do botão com debounce
void button_callback(uint gpio, uint32_t events) {
    if (!sequence_exec) {
        // Debounce do botão
        if (!gpio_get(BUTTON)) {

            // Aguarda 50ms para garantir que o botão tenha estabilizado
            sleep_ms(50);

            // Verifica o estado do botão após o delay
            if (!gpio_get(BUTTON)) {
                sequence_exec = true;
                add_alarm_in_ms(0, turn_on_all_callback, NULL, false);
            }
        }
    }
}

int main() {
    stdio_init_all();
    
    // Configuração dos pinos
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);
    
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        sleep_ms(100);
    }
}
