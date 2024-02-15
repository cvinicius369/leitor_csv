# Leitor de CSV

Software para leitura, manipulação e edição de arquivos CSV

## Funcionamento
1. O software lê o primeiro arquivo, identifica colunas especificas, são elas:
    1. Cliente:
        - Nome completo do cliente
    2. CPF_CNPJ:
        - CPF ou CNPJ
    3. Titulo:
        - Titulo/documento de identificação do contrato
    4. Doc:
        - Documento do contrato
    5. Parc:
        - Parcela
    6. Vlr:
        - Valor da parcela
    7. Venc:
        - Vencimento da parcela
    8. cdTipoCondicao:
        - Condiçao de pagamento

2. Após realizada a leitura e identificação das colunas, o software cria uma tabela no CMD para melhor visualização dos dados

3. O software realiza a leitura de um outro arquivo csv e imprime uma tabela no CMD também

4. O Software compara os clientes do segundo arquivo com os do primeiro arquivo, e então remove do primeiro arquivo, aqueles que estiverem no segundo arquivo.

5. O Software cria um novo arquivo csv com as mesmas colunas

## Instruções de Uso

## Requisitos