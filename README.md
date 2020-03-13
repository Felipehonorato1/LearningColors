# LearningColors
Projeto para disciplina de Derzu, O maia.
Gente, foi estruturado do jeito q falei pra vcs. O mecanismo de selecionar imagens aleatórias e tudo tá funcionando. Quando vcs rodarem, vao perceber que algumas imagens tao muito grandes e outras muito pequenas, temos q tratar isso dps. A primeira imagem que aparece quando vcs rodarem é a que é selecionada pra ir no meio e as q vem qnd vcs fecharem essa são as que irão no canto.
PRA COMPILAR: 
TEM Q TA NA PASTA PELO TERMINAL AI MANDA
    $ g++ -ggdb generate.cpp -o tst `pkg-config --cflags --libs opencv4`
E DEPOIS 
./tst ou o nome que vcs colocarem dps do -o.
