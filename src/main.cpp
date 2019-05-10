#include <list>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool quit = false;
SDL_Event in;
const int SCR_W = 640; // Largura da janela será fixa
const int SCR_H = 480; // Altura da janea será fixa

// Classe que define cada linha do fractal de Koch
class Line
{
    public:

    /*  Os atributos da linha são:
    *   x       -   Define o ponto x de início da linha na janela
    *   y       -   Define o ponto y de início da linha na janela
    *   length  -   Define o comprimento da linha
    *   angle   -   Define o ângulo de inclinação da linha
    */
    double x, y, length, angle;

    // Construtor da linha
    Line(double x, double y, double length, double angle) : x(x), y(y), length(length), angle(angle) {}

    // Determina o ponto x da segunda extremidade da linha
    double getX2()
    {
        return x + cos(angle * (M_PI / 180.0)) * length;
    }

    // Determina o ponto y da segunda extremidade da linha
    double getY2()
    {
        return y + sin(angle * (M_PI / 180.0)) * length;
    }

    // Exibe a linha na janela
    void draw()
    {
        // Define a cor da linha
        SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);

        // Desenha a linha
        SDL_RenderDrawLine(renderer, x, y, getX2(), getY2());

        // Reseta a cor
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
};

// Define uma lista de ponteiros para linhas
std::list<Line*> lines;

void kochFractal(std::list<Line*>& lines)
{
    // Armazenará as novas linhas de cada iteração
    std::list<Line*> newLines;

    // Armazenará as linhas que serão deletadas após cada iteração
    std::list<Line*> delLines;

    // Itera sobre a lista de linhas e define os parâmetros das novas linhas sobre cada uma delas
    for (auto itr = lines.begin(); itr != lines.end(); itr++)
    {
        double x_l1 = (*itr)->x;                // Define o x da primeira linha
        double y_l1 = (*itr)->y;                // Define o y da primeira linha
        double len_l1 = (*itr)->length / 3.0;   // Define o comprimento da primeira linha (em escala)
        double ang_l1 = (*itr)->angle;          // Define o ângulo de inclinação da primeira linha

        double x_l2 = (*itr)->x + (cos((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 1.5); // Define o x da segunda linha
        double y_l2 = (*itr)->y + (sin((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 1.5); // Define o y da segunda linha
        double len_l2 = (*itr)->length / 3.0;                                                   // Define o comprimento da segunda linha (em escala)
        double ang_l2 = (*itr)->angle;                                                          // Define o ângulo de inclinação da segunda linha

        double x_l3 = (*itr)->x + (cos((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 3.0); // Define o x da terceira linha
        double y_l3 = (*itr)->y + (sin((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 3.0); // Define o y da terceira linha 
        double len_l3 = (*itr)->length / 3.0;                                                   // Define o comprimento da terceira linha
        double ang_l3 = (*itr)->angle - 300.0;                                                  // Define o ângulo de inclinação da terceira linha

        double x_l4 = (*itr)->x + (cos((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 1.5); // Define o x da quarta linha
        double y_l4 = (*itr)->y + (sin((*itr)->angle * (M_PI / 180.0)) * (*itr)->length / 1.5); // Define o y da quarta linha
        double len_l4 = (*itr)->length / 3.0;                                                   // Define o comprimento da quarta linha (em escala)     
        double ang_l4 = (*itr)->angle - 240.0;                                                  // Define o ângulo de inclinação da quarta linha
    
        // Ajustando a orientação de formação do triângulo
        x_l4 += cos(ang_l4 * (M_PI / 180.0)) * len_l4;
        y_l4 += sin(ang_l4 * (M_PI / 180.0)) * len_l4;
        ang_l4 -= 180.0;

        // Cada linha definida acima é adicionada à lista de novas linhas
        newLines.push_back(new Line(x_l1, y_l1, len_l1, ang_l1));
        newLines.push_back(new Line(x_l2, y_l2, len_l2, ang_l2));
        newLines.push_back(new Line(x_l3, y_l3, len_l3, ang_l3));
        newLines.push_back(new Line(x_l4, y_l4, len_l4, ang_l4));

        // A linha atual é adicionada à lista de linhas a serem deletadas
        delLines.push_back((*itr));
    }

    // Adiciona às novas linhas ao vetor de linhas
    for (auto itr = newLines.begin(); itr != newLines.end(); ++itr)
        lines.push_back((*itr));

    // Itera sobre as linhas a serem deletadas, removendo-as da lista de linhas
    for (auto itr = delLines.begin(); itr != delLines.end(); ++itr)
    {
        lines.remove((*itr));   // Remove a linha
        delete (*itr);          // Desaloca o espaço na memória
    }
}
