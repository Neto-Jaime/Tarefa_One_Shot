# Tarefa_One_Shot
# Projeto: Sequência de LEDs com Botão no RP2040

Este projeto implementa um sistema de controle de LEDs utilizando um botão no microcontrolador RP2040. Quando o botão é pressionado, inicia-se uma sequência de ativação dos LEDs em diferentes estágios, cada um durando 3 segundos.

## Descrição

- **LED Azul** (GPIO 12): Primeiro LED a ser ativado.
- **LED Vermelho** (GPIO 13): Ativado após o LED Azul.
- **LED Verde** (GPIO 11): Último LED da sequência.
- **Botão** (GPIO 5): Quando pressionado, inicia a sequência dos LEDs.

A lógica do código utiliza timers e callbacks para alternar os LEDs de forma automática, garantindo a temporização correta de cada estágio da sequência.

## Hardware

- **RP2040** (Placa Raspberry Pi Pico ou similar)
- **LEDs** conectados aos seguintes pinos:
  - LED Azul: GPIO 12
  - LED Vermelho: GPIO 13
  - LED Verde: GPIO 11
- **Botão** conectado ao GPIO 5

## Funcionalidade

1. O código inicia com todos os LEDs desligados.
2. Quando o botão (GPIO 5) é pressionado, a sequência de LEDs começa:
   - **Passo 1**: Todos os LEDs acendem por 3 segundos.
   - **Passo 2**: Apenas o LED Azul é apagado, permanecendo o LED Vermelho e o LED Verde acesos por mais 3 segundos.
   - **Passo 3**: O LED Vermelho é apagado, permanecendo apenas o LED Verde aceso por 3 segundos.
   - **Passo 4**: O LED Verde é apagado, finalizando a sequência.
3. Após a finalização, o sistema aguarda uma nova pressão do botão para reiniciar a sequência.

## Como Compilar e Executar

1. **Instalar Dependências**:
   - Certifique-se de que o SDK do Raspberry Pi Pico está configurado no seu ambiente de desenvolvimento.

2. **Compilar o Código**:
   - Utilize a ferramenta `CMake` para compilar o código.

3. **Carregar o Código**:
   - Faça o upload do código compilado para a sua placa RP2040.

4. **Executar**:
   - Após carregar o código na placa, pressione o botão para iniciar a sequência de LEDs.

## Estrutura do Código

- **Função `button_callback`**: Interrupção acionada quando o botão é pressionado, iniciando a sequência de LEDs.
- **Função `turn_on_all_callback`**: Acende todos os LEDs e inicia a sequência.
- **Função `turn_on_red_callback`**: Apaga o LED Azul e mantém os demais.
- **Função `turn_on_green_callback`**: Apaga o LED Vermelho e mantém apenas o Verde.
- **Função `turn_off_callback`**: Apaga todos os LEDs e libera o sistema para uma nova ativação.
- **Função `main`**: Configura os pinos dos LEDs e do botão, e mantém o loop principal ativo.

## Exemplo de Funcionamento

1. Usuário pressiona o botão → LEDs Azul, Vermelho e Verde acendem.
2. Após 3 segundos → Apenas LED Vermelho e Verde permanecem acesos.
3. Após mais 3 segundos → Apenas LED Verde permanece aceso.
4. Após mais 3 segundos → Todos os LEDs são apagados.
5. Sistema aguarda nova pressão do botão para reiniciar o processo.

