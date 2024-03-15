# Leitor de CSV

Software para leitura, manipulação e edição de arquivos CSV. Utiliza: 

<img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=blue&color=black"/><img src="https://img.shields.io/badge/Csharp-00599C?style=for-the-badge&logo=csharp&logoColor=purple&color=black"/><img src="https://img.shields.io/badge/.NET-512BD4?style=for-the-badge&logo=dotnet&logoColor=641f5e&color=black"/><img loading="lazy" src="https://img.shields.io/badge/GNU%20Bash-4EAA25?style=for-the-badge&logo=GNU%20Bash&logoColor=green&color=black">

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
1. Extraia o primeiro arquivo em formato csv separado com ponto e virgula (;) e no formato UTF-8 com as seguintes colunas:
    - Cliente
    - CPF_CNPJ
    - Titulo
    - Documento
    - Parcela
    - Valor
    - Vencimento
    - CondPagamento/Condiçao de pagamento
    - Telefone

### Formatação dos Arquivos
1. Feita a extração do primeiro arquivo, extraia o segundo arquivo no mesmo formato (csv UTF-8 separado com ponto e virgula ";")

2. Abra ambos os arquivos e retire:
    - acentos 
    - aspas duplas nos nomes nos clientes 
    - espaços no final e no inicio do nome

3. Em seguida remova ou mova quaisquer colunas que estejam antes da coluna de clientes, para que fique no formato mais compreensivo, deixeo na ordem mensionada no primeiro passo.

### Leitura pelo software
1. Abra o leitor e informe o caminho do primeiro arquivo csv, segue exemplo:
    ```
    c://caminho/do/arquivo/arquivo.csv
    ```
2. Da mesma  forma faça com o segundo arquivo

3. Informe o nome e o caminho do arquivo solução, segue exemplo:
    ```
    Nome da Planilha resultante: exemplo.csv
    Caminho do diretório: c://caminho/do/arquivo
    ```
5. Agora o leitor fará o trabalho e salvar o novo arquivo no diretório informado.

### Nota
O leitor criará o arquivo resultante com o nome de solução, mas o mesmo pode ser renomeado posteriormente.

## Requisitos
- Ambos os arquivos deverão ser impressos em CSV separado com ponto e virgula(;) e compátivel com UTF-8.

- A planilha não deve conter outras colunas antes da coluna de clientes

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
