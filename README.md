# Controle da Matrix de Leds com botões

## Circuito no Wokwi

No circuito, foram empregados, 2 push-buttons, Matriz de Leds 5x5 e um microcontrolador Raspberry Pi Pico W.

## Funcionamento

- Um led pisca em vermelho 5 vezes por segundo, independentemente do resto das funcionalidades.
- A matriz 5x5 apresenta um número de 0 à 9. 
- Ao apertar o botão "A", é somado um ao número mostrado na matriz.
- Ao apertar o botão "B", é subtraido um do número mostrado na matriz. 
- Caso o número na matriz seja 0, ele permanecéra em 0 ao ser subtraido. 
- Caso o número na matriz seja 9, ele permanecéra em 9 ao ser somado. 

# Código

No código foram utilizados interrupções, debouncers via software e 2 máquinas de estado de um PIO para controle do led vermelho que pisca 5 vezes por segundo e da fita de led que compõe a matriz 5x5.

## Ferramentas Utilizadas no Desenvolvimento

- VS Code
- Wokwi
- Linguagem C
- Kit de desenvolvimento de Software Pico (Pico SDK)

## Vídeo de Apresentação

A seguir o vídeo apresentando o circuito em funcionamento.

## Execução do projeto

Para executar o projeto é necessário: 
- baixar os arquivos deste repositório
- Utilizando a extensão do Wokwi para VS Code é possível simular o circuito
- Ou, utilizando a extensão Pi Pico para VS Code é possível compilar e carregar o circuito em um microcontrolador Pi Pico W
