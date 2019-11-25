# Projeto: Desenho com primitivas gráficas em C

### Autores

Alice Maria

Rodrigo Rocha

### Sobre o Programa

O programa tem como objetivo possibilitar ao usuário uma ferramenta para a criação de artes digitais. Desse modo, os desenhos são criados a partir de comandos - sendo eles save, image, color, clear, line, open, polygon, circle, rect, fill, repeat_line, repeat_polygon, copy_polygon - e seus parâmetros, para os casos que necessitam.

Inicialmente, o usuário deve acessar o arquivo “input.txt” e utilizar o comando “image”para criar uma nova imagem  e definir os parâmetros na qual deseja fazer o desenho. 

Em seguida, é necessário o uso do comando “clear” para limpar e mudar as cores da imagem para as cores especificadas nos parâmetros. Em sequência, o usuário deve declarar os demais comandos para realizar o desenho desejado como os comandos “ polygon”, “circle”, “rect”,  “fill” dentre outros. 

Por fim, o usuário tem a possibilidades de salvar seu projeto com o comando “save” e especificando o nome e a extensão “.ppm”.

Além disso, é possível abrir uma imagem já existente para que possa ser editada a partir do comando “open” e o nome e do arquivo com a extensão “.ppm”

### Primitivas:

Instruções para os comandos presentes que podem ser utilizados:

O comando “color” deve possuir três parâmetros que definirão a cor da forma que será declarada em sequência. O color deve possuir o formato “color 0 164 255”, por exemplo, seguindo o sistema RGB no qual o primeiro parâmetro é a intensidade da cor vermelha, o segundo da cor verde e o terceiro da cor azul.

o comando “fill” como o color deve possuir três parâmetros que definirão a cor desejada, o diferencial do fill é que ele preencherá o interior da “figura” ou o espaço selecionado até os limites da imagem ou de outra figura. O fill possui o formato “fill 255 255 255”, por exemplo.

O comando “line” possui quatro parâmetros sendo eles os pares ordenado que definirão o início e fim da linha. O formato do comando line deve possuir o padrão “line 100 100 200 100”, por exemplo. Contudo, é importante ressaltar que os parâmetros não devem ultrapassar as dimensões totais da imagem.

O comando “polygon” é composto do primeiro parâmetro que deve ser a quantidade de vértices do polígono, os parâmetros seguintes serão os pares ordenados que definem a posição de cada vértice. Dessa maneira, o formato a ser seguido deve ser “polygon 3 0 359 50 359 0 309” com mais parâmetros, tendo em vista que a menor quantidade de vértices para um polígono são três pontos.

O comando “rect” recebe quatro parâmetros, sendo eles o par ordenado onde será desenhado o retângulo e suas dimensões de largura e altura. Assim, o comando terá o seguinte formato “rect 50 110 100 120”, por exemplo.

O comando “circle” possui três parâmetros os quais são o par ordenado e o raio da circunferência. Sendo assim, o padrão a ser seguido pelo usuário deve ser como o exemplificado a seguir “circle 100 120 50”.

O comando “repeat_line” basicamente repete o comando line anterior e os parâmetros são definidos pela quantidade de vezes que a linha será repetida, a distância entres os pares ordenados iniciais e finais que serão repetidos. Portanto,  o comando terá o seguinte formato “repeat-line 1 0 50 0 -50”, por exemplo.

O comando “repeat_polygon” recebe como parâmetro a quantidade de vezes que o polígono será repetido e a distância entre eles. Desse modo, o formato a ser seguido deve ser “repeat-polygon 25 5 -5”, por exemplo.

O comando “copy_polygon” mantém as dimensões, ou seja o formato, do polígono chamado anteriormente e o copia para local indicado nos parâmetros. Assim, o comando copy_polygon deve seguir o exemplo a seguir “copy-polygon 100 150”.

Note que existem ações as quais podem ocasionar erros na execução como os exemplos a seguir:

Coordenadas que passem dos limites da imagem, como supracitado no comando “line”, causam erro na execução do programa. Ademais, esse cuidado deve ser seguido para os demais comandos.

Imagens com dimensões grandes pode ocasionar um risco para a execução do programa. tendo em vista que recursos como o comando “fill” utilizam recursão e exigem um grande quantidade de memória.

Além dos fatores anteriores, cuidados devem ser tomados na hora de escrever os comandos no arquivo “input.txt” como por exemplo parâmetros errados, parâmetros a mais ou a menos que o desejado e espaços a mais entre os parâmetros.

### Compilando o programa

O programa contêm os arquivos já compilados, mas caso houver alguma modificação a ser compilada, segui o processo abaixo:

Para compilar e executar o projeto o usuário, a priori, deve compilar cada um dos módulos separadamente, conforme abaixo:

```
gcc -c programa.c
gcc -c primitivas.c
gcc -c funcoes.c
```
Após cada módulo ter sido compilado, o usuário deve compilar todos os arquivos juntos para gerar um executável:

```
gcc programa.o primitivas.o funcoes.o Desenho.c -o desenho
```

### Executando o programa

Por fim, após compilados, podemos executar dessa forma:
```
./desenho
```

É possível pular a etapa da compilação e simplesmente executar como acima.

Alguns processos podem variar caso esteja executando no windows, possívelmente gerando um exe que deve ser executado de forma diferente e que não está descrito nessa documentação.

### Usando o Valgrind para diagnosticar o acesso a memória do projeto:

O Valgrind é uma ferramenta que possibilita o diagnóstico de problemas relacionados ao acesso de memória pelo programa.

Para podermos utilizá-lo, é necessário instalá-lo.

No linux, é possível instalar usando o comando abaixo:

```
sudo apt-get install valgrind
```

Depois de instalador, podemos realizar o diagnóstico do projeto executando o valgrind com o arquivo compilado do projeto, como abaixo:

Comando para executar:

```
valgrind ./desenho
```
Saída: 

```
==19427== Memcheck, a memory error detector
==19427== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19427== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==19427== Command: ./desenho
==19427== 
==19427== Conditional jump or move depends on uninitialised value(s)
==19427==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==19427==    by 0x10977D: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B95E: main (Desenho.c:9)
==19427== 
==19427== Conditional jump or move depends on uninitialised value(s)
==19427==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==19427==    by 0x1097FB: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==19427==    by 0x10B95E: main (Desenho.c:9)
==19427== 
==19427== 
==19427== HEAP SUMMARY:
==19427==     in use at exit: 0 bytes in 0 blocks
==19427==   total heap usage: 259,931 allocs, 259,931 frees, 5,203,732 bytes allocated
==19427== 
==19427== All heap blocks were freed -- no leaks are possible
==19427== 
==19427== For counts of detected and suppressed errors, rerun with: -v
==19427== Use --track-origins=yes to see where uninitialised values come from
==19427== ERROR SUMMARY: 129958 errors from 2 contexts (suppressed: 0 from 0)
```

Com essa saída, podemos afirmar que o programa não contêm memory leaks, isto é, toda a memória alocada é liberada no final da execução do programa. Porém, existem erros referentes ao uso de valores não inicializados no programa. Ao executar usando o comando abaixo, temos maiores detalhes obre esses erros:

Comando:

```
valgrind --track-origins=yes ./desenho
```

Saída:

```
==20057== Memcheck, a memory error detector
==20057== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20057== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==20057== Command: ./desenho
==20057== 
==20057== Conditional jump or move depends on uninitialised value(s)
==20057==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==20057==    by 0x10977D: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B95E: main (Desenho.c:9)
==20057==  Uninitialised value was created by a heap allocation
==20057==    at 0x483AD4B: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==20057==    by 0x109722: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B95E: main (Desenho.c:9)
==20057== 
==20057== Conditional jump or move depends on uninitialised value(s)
==20057==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==20057==    by 0x1097FB: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B95E: main (Desenho.c:9)
==20057==  Uninitialised value was created by a heap allocation
==20057==    at 0x483AD4B: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==20057==    by 0x10977D: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==20057==    by 0x10B95E: main (Desenho.c:9)
==20057== 
==20057== 
==20057== HEAP SUMMARY:
==20057==     in use at exit: 0 bytes in 0 blocks
==20057==   total heap usage: 259,931 allocs, 259,931 frees, 5,203,732 bytes allocated
==20057== 
==20057== All heap blocks were freed -- no leaks are possible
==20057== 
==20057== For counts of detected and suppressed errors, rerun with: -v
==20057== ERROR SUMMARY: 129958 errors from 2 contexts (suppressed: 0 from 0)
```

Ao tentar usar o programa para abrir uma imagem retangular, isto é, com altura e largura diferentes, o que atualmente gera um erro no programa, temos essa saída:

```
==23602== Memcheck, a memory error detector
==23602== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==23602== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==23602== Command: ./desenho
==23602== 
==23602== Conditional jump or move depends on uninitialised value(s)
==23602==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==23602==    by 0x10977D: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B95E: main (Desenho.c:9)
==23602== 
==23602== Conditional jump or move depends on uninitialised value(s)
==23602==    at 0x483ACF8: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==23602==    by 0x1097FB: realocar_matriz (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B0AC: image (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B128: interpretar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B789: executar (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==    by 0x10B95E: main (Desenho.c:9)
==23602== 
==23602== Warning: client switching stacks?  SP change: 0x1ffeffef50 --> 0x1ffedef9c0
==23602==          to suppress, use: --max-stackframe=2160016 or greater
==23602== Warning: client switching stacks?  SP change: 0x1ffedef9c0 --> 0x1ffe55a580
==23602==          to suppress, use: --max-stackframe=9000000 or greater
==23602== Invalid write of size 8
==23602==    at 0x10AEF9: open (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==  Address 0x1ffe55a578 is on thread 1's stack
==23602== 
==23602== 
==23602== Process terminating with default action of signal 11 (SIGSEGV)
==23602==  Access not within mapped region at address 0x1FFE55A578
==23602==    at 0x10AEF9: open (in /home/rodrigo/Documentos/Cprogramming/projeto-desenho/desenho)
==23602==  If you believe this happened as a result of a stack
==23602==  overflow in your program's main thread (unlikely but
==23602==  possible), you can try to increase the size of the
==23602==  main thread stack using the --main-stacksize= flag.
==23602==  The main thread stack size used in this run was 8388608.
==23602== Invalid write of size 8
==23602==    at 0x482E110: _vgnU_freeres (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_core-amd64-linux.so)
==23602==  Address 0x1ffe55a570 is on thread 1's stack
==23602== 
==23602== 
==23602== Process terminating with default action of signal 11 (SIGSEGV)
==23602==  Access not within mapped region at address 0x1FFE55A570
==23602==    at 0x482E110: _vgnU_freeres (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_core-amd64-linux.so)
==23602==  If you believe this happened as a result of a stack
==23602==  overflow in your program's main thread (unlikely but
==23602==  possible), you can try to increase the size of the
==23602==  main thread stack using the --main-stacksize= flag.
==23602==  The main thread stack size used in this run was 8388608.
==23602== 
==23602== HEAP SUMMARY:
==23602==     in use at exit: 1,210,896 bytes in 60,205 blocks
==23602==   total heap usage: 120,411 allocs, 60,206 frees, 2,417,172 bytes allocated
==23602== 
==23602== LEAK SUMMARY:
==23602==    definitely lost: 0 bytes in 0 blocks
==23602==    indirectly lost: 0 bytes in 0 blocks
==23602==      possibly lost: 0 bytes in 0 blocks
==23602==    still reachable: 1,210,896 bytes in 60,205 blocks
==23602==         suppressed: 0 bytes in 0 blocks
==23602== Reachable blocks (those to which a pointer was found) are not shown.
==23602== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==23602== 
==23602== For counts of detected and suppressed errors, rerun with: -v
==23602== Use --track-origins=yes to see where uninitialised values come from
==23602== ERROR SUMMARY: 60200 errors from 4 contexts (suppressed: 0 from 0)
Falha de segmentação (imagem do núcleo gravada)
```

De acordo com a saída, temos que durante a execução o programa acessou uma posição não mapeada, causando a falha de segmentação.

### Usando Doxygen para gerar documentação:

O doxygen permite a geração automática de documentação através de um padrão de comentário no código.

para usar o doxygen, é necessário instalá-lo. 

No linux, o processo é o seguinte:

clonamos o repositório usando git e podemos usá-lo.

```
git clone https://github.com/doxygen/doxygen.git
```

Após clonar o repositório, entramos na pasta e geramos o arquivo de configuração com o comando abaixo:

```
doxygen -g deconfig
```

Após isso criamos uma pasta para colocar a documentação. No nosso caso, a pasta documentos.

Com tudo isso criado, editamos o arquivo de configuração da seguinte forma, para gerar a documentação da forma que foi gerado para esse projeto.

Alterar:

```
PROJECT_NAME para "Desenho com Primitivas"
OUTPUT_DIRECTORY para /documentos
SOURCE_BROWNSER para YES
INLINE_SOURCES para YES
```

Com tudo configurado, temos que realizar a documentação do código através de comentário, como está na [documentação](http://www.doxygen.nl/manual/docblocks.html).

Após isso, para gerarmos a documentação, executamos o comando abaixo:

```
doxygen deconfig-tmp
```

Após isso, a documentação foi gerada. Podemos acessar a versão html através do arquivo index na pasta html. Para a versão pdf, caso um arquivo pdf não tenha sido gerado automaticamente dentro da pasta latex, execute o seguinte comando dentro da pasta latex:

```
make
```

caso dê um erro de comando não encontrado, teremos que fazer as instalações conforme o esse [link](https://gist.github.com/rain1024/98dd5e2c6c8c28f9ea9d).


