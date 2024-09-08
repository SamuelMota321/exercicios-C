#include <stdio.h>

int main(void)
{
    const int bimestres = 4;
    const int numeroDeAlunos = 4;
    float notasAlunos[numeroDeAlunos][bimestres];
    float mediasAlunos[numeroDeAlunos];
    float media = 0;

    for (int aluno = 0; aluno < numeroDeAlunos; aluno++)
    {
        printf("Insira as 4 notas do aluno %i \n", aluno + 1);

        for (int nota = 0; nota < bimestres; nota++)
        {
            printf("Insira a nota %i ", nota + 1);
            scanf("%f", &notasAlunos[aluno][nota]);
            media += notasAlunos[aluno][nota];
        }
        mediasAlunos[aluno] = media / bimestres;
        media = 0;
    }

    for (int aluno = 0; aluno < numeroDeAlunos; aluno++)
    {
        printf("A media do aluno %i foi de %.2f \n", aluno + 1 ,mediasAlunos[aluno]);
    }

    return 0;
}