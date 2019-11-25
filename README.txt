O programa tem como objetivo possibilitar ao usuário uma ferramenta para a criação de artes digitais. Desse modo, os desenhos são criados a partir de comandos - sendo eles save, image, color, clear, line, open, polygon, circle, rect, fill, repeat_line, repeat_polygon, copy_polygon - e seus parâmetros, para os casos que necessitam.
Inicialmente, o usuário deve acessar o arquivo “input.txt” e utilizar o comando “image”para criar uma nova imagem  e definir os parâmetros na qual deseja fazer o desenho.
Em seguida, é necessário o uso do comando “clear” para limpar e mudar as cores da imagem para as cores especificadas nos 
parâmetros. 
Em sequência, o usuário deve declarar os demais comandos para realizar o desenho desejado como os comandos “ polygon”, “circle”, “rect”,  “fill” dentre outros. Por fim, o usuário tem a possibilidades de salvar seu projeto com o comando “save” e especificando o nome e a extensão “.ppm”. Além disso, é possível abrir uma imagem já existente para que possa ser editada a partir do comando “open” e o nome e a extensão “.ppm”

Instruções para os comandos presentes que podem ser utilizados:

O comando “color” deve possuir três parâmetros que definirão a cor da forma que será declarada em sequência. O color deve possuir o formato “color 0 164 255”, por exemplo, seguindo o sistema RGB no qual o primeiro parâmetro é a intensidade da cor vermelha, o segundo da cor verde e o terceiro da cor azul.

o comando “fill” como o color deve possuir três parâmetros que definirão a cor desejada, o diferencial do fill é que ele preencherá o interior da “figura” ou o espaço selecionado até os limites da imagem ou de outra figura. O fill possui o formato “fill 255 255 255”, por exemplo.

O comando “line” possui quatro parâmetros sendo eles os pares ordenado que definirão o início e fim da linha. O formato do comando line deve possuir o padrão “line 100 100 200 100”, por exemplo. Contudo, é importante ressaltar que os parâmetros não devem ultrapassar as dimensões totais da imagem.

O comando “polygon” é composto do primeiro parâmetro que deve ser a quantidade de vértices do polígono, os parâmetros seguintes serão os pares ordenados que definem a posição de cada vértice. Dessa maneira, o formato a ser seguido deve ser “polygon 3 0 359 50 359 0 309” com mais parâmetros, tendo em vista que a menor quantidade de vértices para um polígono são três pontos.

O comando “rect” recebe quatro parâmetros, sendo eles o par ordenado onde será desenhado o retângulo e suas dimensões de largura e altura. Assim, o comando terá o seguinte formato “rect 50 110 100 120”, por exemplo.

O comando “circle” possui três parâmetros os quais são o par ordenado e o raio da circunferência. Sendo assim, o padrão a ser seguido pelo usuário deve ser como o exemplificado a seguir “circle 100 120 50”.

O comando “repeat_line” basicamente repete o comando line anterior e os parâmetros são definidos pela quantidade de vezes que a linha será repetida, a distância que a as linhas serão repetidas e as direções. Portanto,  o comando terá o seguinte formato “repeat-line 1 0 50 0 -50”, por exemplo.

O comando “repeat_polygon”, analogamente ao comando repeat_line, o repeat_polygon recebe como parâmetro a quantidade de vezes que a linha será repetida, a distância que a as linhas serão repetidas e as direções. Desse modo, o formato a ser seguido deve ser “repeat-polygon 25 5 -5”, por exemplo.

O comando “copy_polygon” mantém as dimensões, ou seja o formato, do polígono chamado anteriormente e o copia para local indicado nos parâmetros. Assim, o comando copy_polygon deve seguir o exemplo a seguir “copy-polygon 100 150”.

Ações que podem causar erro:

Coordenadas que passem dos limites da imagem, como supracitado no comando “line”, causam erro na execução do programa. Ademais, esse cuidado deve ser seguido para os demais comandos.

Imagens com dimensões grandes pode ocasionar um risco para a execução do programa. tendo em vista que recursos como o comando “fill” utilizam recursão e exigem um grande quantidade de memória.

Além dos fatores anteriores, cuidados devem ser tomados na hora de escrever os comandos no arquivo “imput.txt” como por exemplo parâmetros errados, parâmetros a mais ou a menos que o desejado e espaços a mais entre os parâmetros.
