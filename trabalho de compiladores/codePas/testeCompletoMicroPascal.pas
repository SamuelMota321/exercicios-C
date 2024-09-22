program TesteCompiladorLexico;

var
    a, b, resultado: integer;
    x, y: real;
    condicao: boolean;

function SomaInteiros(i, j: integer): integer;
begin
    SomaInteiros := i + j;
end;

procedure MostraResultado(r: integer);
begin
    writeln('O resultado inteiro e: ', r);
end;

procedure MostraResultadoReal(r: real);
begin
    writeln('O resultado real e: ', r:0:2);
end;

begin
    a := 10;
    b := 20;
    x := 15.5;
    y := 25.75;
    condicao := true;

    resultado := a + b;
    MostraResultado(resultado);  

    resultado := a * (b - 5);
    MostraResultado(resultado);  

    y := x / 2.0;
    MostraResultadoReal(y);  

    if a > b then
        writeln('A e maior que B')
    else
        writeln('A e menor ou igual a B');

    while a < 15 do
    begin
        a := a + 1;
        writeln('Valor de A: ', a);
    end;

    resultado := SomaInteiros(a, b);
    MostraResultado(resultado);  

    condicao := (a = b);
    if condicao then
        writeln('A e igual a B')
    else
        writeln('A e diferente de B');

    if (a mod 2 = 0) then
        writeln('A e par')
    else
        writeln('A e impar');
        
end.
