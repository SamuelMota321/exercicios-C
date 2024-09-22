program TesteComentarios;

(* Este é um comentário de bloco *)
begin
    { Este é um comentário com chaves }
    writeln('Teste de comentários em microPascal');
    
    writeln('Este código deve ser executado');

    (* Comentário de bloco com
       múltiplas linhas *)
    writeln('Os comentários não devem interferir no código');

    { Outro exemplo de comentário com
      várias linhas dentro de chaves }

    writeln('Fim do teste');

    (* Comentário vazio: {} *)

    { Comentário vazio: { } }

    (* Comentário de bloco que deve ser ignorado *)
    (* 
       Este é um bloco que deve ser 
       completamente ignorado pelo analisador 
    *)

    { Comentário de linha que não deve afetar 
      a execução do programa }

end.
