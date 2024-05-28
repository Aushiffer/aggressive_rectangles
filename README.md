# agressive_rectangles
- Joguinho simples feito em C com a biblioteca Allegro, na disciplina de Programação 2.

## Plataformas suportadas
- Linux x86_64.

## Compilação e execução
- gcc main.c rect.c joystick.c -o agressive_rectangles $(pkg-config allegro-5 allegro_main-5 allegro_primitives-5 --libs --cflags)
- ./aggressive_rectangles
