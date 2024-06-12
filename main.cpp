#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <locale.h>
#include <queue>
#include <windows.h>

using namespace std;

#define CHAO 0
#define PAREDE 1
#define LIMPARTELA "cls"

int coluna_jogador1 = 1, linha_jogador1 = 1;
int contador1 = 0;

queue<char> movimentos_jogador1;

// Mapas de labirinto
int mapa1[10][10] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

int mapa2[20][20] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};


// Função template para desenhar qualquer mapa
template<size_t linhas, size_t colunas>
void desenhar_mapa(int (&mapa)[linhas][colunas]) {
    for (size_t linha = 0; linha < linhas; linha++) {
        for (size_t coluna = 0; coluna < colunas; coluna++) {
            if ((linha == linha_jogador1) && (coluna == coluna_jogador1)) {
                cout << "1"; // Jogador 1
            } else if (mapa[linha][coluna] == CHAO) {
                cout << " ";
            } else if (mapa[linha][coluna] == PAREDE) {
                cout << "#";
            }
        }
        cout << endl;
    }
}

void LimpaLinhaColuna() {
    coluna_jogador1 = 1;
    linha_jogador1 = 1;
    contador1 = 0;
    while (!movimentos_jogador1.empty()) movimentos_jogador1.pop();
}

// Função genérica para mover o jogador em qualquer mapa
template<size_t linhas, size_t colunas>
void mover_jogador1(char movimento, int (&mapa)[linhas][colunas]) {
    if (movimento == 'w' || movimento == 'W') {
        linha_jogador1--;
        if (mapa[linha_jogador1][coluna_jogador1] == PAREDE) {
            linha_jogador1++;
        } else {
            contador1++;
        }
    } else if (movimento == 's' || movimento == 'S') {
        linha_jogador1++;
        if (mapa[linha_jogador1][coluna_jogador1] == PAREDE) {
            linha_jogador1--;
        } else {
            contador1++;
        }
    } else if (movimento == 'a' || movimento == 'A') {
       coluna_jogador1--;
        if (mapa[linha_jogador1][coluna_jogador1] == PAREDE) {
            coluna_jogador1++;
        } else {
            contador1++;
        }
    } else if (movimento == 'd' || movimento == 'D') {
        coluna_jogador1++;
        if (mapa[linha_jogador1][coluna_jogador1] == PAREDE) {
            coluna_jogador1--;
        } else {
            contador1++;
        }
    }
    movimentos_jogador1.push(movimento);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char escolha;
    do {
        system(LIMPARTELA);
        
        cout << "Iniciar Jogo:\n";
        cout << "          \n";
        cout << "Modo Fácil (a)\n";
        cout << "Modo Difícil (b)\n";
        cin >> escolha;
    } while (escolha != 'a' && escolha != 'b');

    bool saiu = false;
    switch (escolha) {
    	case 'b': {
            LimpaLinhaColuna();
            char movimento1;
            while (!(linha_jogador1 == 19 && coluna_jogador1 == 18)) { 
                system(LIMPARTELA);
                desenhar_mapa(mapa2);
                cout << "  " << endl;
                cout << "Comandos do jogo:" << endl;
                cout << "  " << endl;
                cout << "  (w) Cima " << endl;
                cout << "(a) (d) Esquerda/Direita" << endl;
                cout << "  (s) Baixo" << endl;
                cout << "  " << endl;
                cout << "Controles:" << endl;
                cout << "P - Pausar, R - Reiniciar, T - Sair" << endl;

                movimento1 = getch();
                if (movimento1 == 'P' || movimento1 == 'p') {
                    cout << "Jogo pausado. Pressione qualquer tecla para continuar...";
                    getch();
                    continue;
                } else if (movimento1 == 'R' || movimento1 == 'r') {
                    LimpaLinhaColuna();
                    continue;
                } else if (movimento1 == 'T' || movimento1 == 't') {
                    saiu = true;
                    break;
                }

                mover_jogador1(movimento1, mapa2);
                cout << "Posição atual: (" << linha_jogador1 << ", " << coluna_jogador1 << ")" << endl;
            }
            saiu = true;
            break;
        }
        case 'a': {
            LimpaLinhaColuna();
            char movimento1;
            while (!(linha_jogador1 == 9 && coluna_jogador1 == 8)) { 
                system(LIMPARTELA);
                desenhar_mapa(mapa1);
                cout << "  " << endl;
                cout << "Comandos do jogo:" << endl;
                cout << "  " << endl;
                cout << "  (w) Cima " << endl;
                cout << "(a) (d) Esquerda/Direita" << endl;
                cout << "  (s) Baixo" << endl;
                cout << "  " << endl;
                cout << "Controles:" << endl;
                cout << "P - Pausar, R - Reiniciar, T - Sair" << endl;
                

                movimento1 = getch();
                if (movimento1 == 'P' || movimento1 == 'p') {
                    cout << "Jogo pausado. Pressione qualquer tecla para continuar...";
                    getch();
                    continue;
                } else if (movimento1 == 'R' || movimento1 == 'r') {
                    LimpaLinhaColuna();
                    continue;
                } else if (movimento1 == 'T' || movimento1 == 't') {
                    saiu = true;
                    break;
                }

                mover_jogador1(movimento1, mapa1);
                cout << "Posição atual: (" << linha_jogador1 << ", " << coluna_jogador1 << ")" << endl;
            }
            saiu = true;
            break;
        }
        default:
            cout << "Escolha inválida!" << endl;
            break;
    }

   if (saiu) {
    cout << "Voltando ao menu inicial..." << endl;
    LimpaLinhaColuna(); 
    main(); 
}
    return 0;
}
       

