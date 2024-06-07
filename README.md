# aggressive_rectangles
- Joguinho simples feito em C com a biblioteca Allegro, na disciplina de Programação 2 (ainda em desenvolvimento).
- Baseado no "Aggressive Squares" do Prof. Vinicius Fülber-Garcia, feito para se aprender a programar com a biblioteca Allegro.

## Plataformas suportadas
- Linux x86_64.

## Plataformas testadas
- Debian 12 (bookworm).
- openSUSE Tumbleweed.

## Dependências
- GCC (instale com o gerenciador de pacotes da sua distribuição Linux (e.g. "sudo zypper install gcc" para distribuições openSUSE)).
- Make (mesma coisa do GCC).
- Allegro: https://github.com/liballeg/allegro_wiki/wiki/Quickstart

## Clonando, compilando e executando
- git clone https://github.com/Aushiffer/aggressive_rectangles.git
- cd aggressive_rectangles/
- make (compilar).
- make run (executar.)

## Limpando arquivos de compilação
- make clean (limpa apenas os arquivos-objeto (*.o)).
- make purge (limpa todos os arquivos de compilação, incluindo o executável).
