# Editor de imagens
 - todos os códigos aqui utilizados foram inspirados na disciplina IDJ (Introdução ao desenvolvimento de jogos) da UnB e utilizaram uma boa parte dos códigos feitos durante a disciplina.
 - mini editor de imagens feito em cpp.
 - usa a biblioteca SDL2.
 - feito para para praticar o que estudei, como orientação a objetos, segmentação de códigos, etc.
 - para rodar basta baixar as bibliotecas do SDL2, junto com a parte de imagem, mixer, gerenciador de textos.
 - a pasta do SDL2 deve estar em C:\ enquanto as dlls de image, mixer, ttf e SDL2 devem ficar na pasta do programa.


Para rodar o programa pelo terminal devemos navegar para a pasta em questão, daí precisamos executar o comando mingw32-make
 - o compilador g++ foi utilizado com minGW, o makefile presente cria um executável com o nome "EDITOR", que pode ser alterado dentro do arquivo makefile.
 - logo depois de executar o comando via terminal, pode-se usar o executável para editar imagens que estão na pasta \Recursos\img, ou criar uma nova.
