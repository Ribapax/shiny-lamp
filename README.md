# shiny-lamp
Trabalho 2 da disciplina de programação 2 da UFPR
Itens a serem feitos:

    Executar no Linux, em uma janela gráfica
    Interagir com o usuário através do teclado e/ou mouse
    Usar imagens coloridas (sprites), não somente formas geométricas (pode usar figuras prontas obtidas na Internet)
    Tocar sons nos principais eventos (pode usar sons prontos da Internet)
    Suportar ao menos três níveis com mapas, ações e/ou objetos diferentes
    Calcular a pontuação do jogador e manter um score persistente (salvo em disco) das melhores pontuações obtidas, apresentado ao usuário ao finalizar o jogo
    As teclas h ou F1 abrem uma tela de ajuda com as instruções do jogo, nome do autor e outras informações
    Ter um Easter Egg ou um cheat code (como o Código Konami)
    Executar a 60 FPS (frames per second)

Requisitos do código:

    Ser desenvolvido em C padrão C99 (-std=c99, -std=gnu99 ou -std=gnu11)
    Usar a biblioteca gráfica Allegro 5 2)
    Separar o código em vários arquivos .c e .h separados, respeitando as regras de organização de código
    Usar alocação de memória dinâmica
    Usar estruturas
    Compilar com o flag -Wall sem erros nem avisos
    Usar o sistema Make para compilação, com ao menos os seguintes alvos:
        all: compila e gera o executável
        clean: remove os arquivos temporários (mantém o executável)
        purge: remove tudo, deixando somente os fontes
    Todos os arquivos que não forem código-fonte (imagens, sons, fontes, mapas, …) devem ser colocados em um subdiretório resources/ dentro do diretório do código.

Critérios de avaliação

    cumprimento dos requisitos acima
    fidelidade ao jogo original
    qualidade do código (estrutura, clareza, comentários, endentação)
