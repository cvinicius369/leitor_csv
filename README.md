# Leitor de CSV

Software para leitura, manipulação e edição de arquivos CSV

## Funcionamento
1. O software lê o primeiro arquivo, identifica colunas especificas, são elas:
    - Cliente:
        - Nome completo do cliente
    - CPF_CNPJ:
        - CPF ou CNPJ
    - Titulo:
        - Titulo/documento de identificação do contrato
    - Doc:
        - Documento do contrato
    - Parc:
        - Parcela
    - Vlr:
        - Valor da parcela
    - Venc:
        - Vencimento da parcela
    - cdTipoCondicao:
        - Condiçao de pagamento

2. Após realizada a leitura e identificação das colunas, o software cria uma tabela no CMD para melhor visualização dos dados

3. O software realiza a leitura de um outro arquivo csv e imprime uma tabela no CMD também

4. O Software compara os clientes do segundo arquivo com os do primeiro arquivo, e então remove do primeiro arquivo, aqueles que estiverem no segundo arquivo.

5. O Software cria um novo arquivo csv com as mesmas colunas

## Instruções de Uso
### Extração dos Arquivos
1. Extraia o primeiro arquivo em formato csv separado com ponto e virgula (;) com as seguintes colunas:
    - Cliente
    - CPF_CNPJ
    - Titulo
    - Documento
    - Parcela
    - Valor
    - Vencimento
    - CondPagamento/Condiçao de pagamento
2. Feita a extração do primeiro arquivo, extraia o segundo arquivo no mesmo formato (csv separado com ponto e virgula ";")
3. Se necessário, edite-o para que a coluna de clientes seja a primeira, para que o leitor identifique
4. Abra o leitor e informe o caminho do primeiro arquivo csv, segue exemplo:
    ```
    c://caminho/do/arquivo/arquivo.csv
    ```
4. Da mesma  forma faça com o segundo arquivo
5. Informe o nome e o caminho do arquivo solução, segue exemplo:
    ```
    Nome da Planilha resultante: exemplo.csv
    Caminho do diretório: c://caminho/do/arquivo
    ```
6. Agora o leitor fará o trabalho e salvar o novo arquivo no diretório informado.

## Requisitos
- Ambos os arquivos deverão ser impressos em CSV separado com ponto e virgula(;)

- A planilha não deve conter a data de registro antes da coluna de clientes

- A coluna de clientes deve sempre ser a primeira (recomenda-se que as demais também estejam em ordem)

- Caso os arquivos csv não esteja na mesma pasta que o software, ao informar o arquivo, informe o caminho completo, por exemplo:
    ```
    c://caminho/do/arquivo/arquivo.csv
    ```
- O nome do novo arquivo deve ser informado juntamente com o caminho para o carquivo, por exemplo:
    ```
    c://caminho/do/arquivo/arquivo.csv
    ```

License
Copyright © 2024, Caio Vinicius de Almeida Faguette. Released under the MIT License.
