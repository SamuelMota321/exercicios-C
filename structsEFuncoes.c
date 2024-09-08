#include <stdio.h>

struct horario
{
    int
        horas,
        minutos,
        segundos;
} agora = {10, 34, 40};

struct horario teste(struct horario horario)
{
    printf("%i:%i:%i\n", horario.horas, horario.minutos, horario.segundos);

    horario.horas = 15;
    horario.minutos = 55;
    horario.segundos = 56;
    return horario;
}

int main(void)
{
    struct horario proximo = teste(agora);
    printf("%i:%i:%i\n", proximo.horas, proximo.minutos, proximo.segundos);

    return 0;
}