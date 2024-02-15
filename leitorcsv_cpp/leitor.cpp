// Inclui as bibliotecas necessárias
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Define uma estrutura para armazenar os dados de cada linha do arquivo csv
struct Dados {
    string Cliente;        // Nome do cliente
    string CPF_CNPJ;       // CPF_CNPJ
    string Titulo;         // Titulo do cliente
    string Doc;            // Documento do cliente
    string Parc;           // Parcela
    string Vlr;            // Valor da Parcela
    string Venc;           // Vencimento da parcela 
    string cdTipoCondicao; // Código do tipo de condição
};

// Define uma função para ler um arquivo csv e retornar um vetor de dados
vector<Dados> ler_csv(string nome_arquivo) {
    vector<Dados> dados;                       // Vetor para armazenar os dados
    ifstream arquivo(nome_arquivo);            // Abre o arquivo para leitura
    if (arquivo.is_open()) {                   // Verifica se o arquivo foi aberto com sucesso
        string linha;                          // String para armazenar cada linha do arquivo
        getline(arquivo, linha);               // Ignora a primeira linha (cabeçalho)
        while (getline(arquivo, linha)) {      // Lê cada linha do arquivo
            Dados d;                           // Cria um objeto da estrutura Dados
            size_t pos = 0;                    // Posição do separador (vírgula)
            pos = linha.find(",");             // Encontra a primeira vírgula
            d.Cliente = linha.substr(0, pos);  // Extrai o nome do cliente
            linha.erase(0, pos + 1);           // Remove o nome e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.CPF_CNPJ = linha.substr(0, pos); // Extrai o cpf ou cnpj do cliente
            linha.erase(0, pos + 1);           // Remove o cpf ou cnpj e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.Titulo = linha.substr(0, pos);   // Extrai o titulo do cliente
            linha.erase(0, pos + 1);           // Remove o titulo e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.Doc = linha.substr(0, pos);      // Extrai o Documento do cliente
            linha.erase(0, pos + 1);           // Remove o Documento e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.Parc = linha.substr(0, pos);     // Extrai a parcela
            linha.erase(0, pos + 1);           // Remove a parcela e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.Vlr = linha.substr(0, pos);      // Extrai o Valor
            linha.erase(0, pos + 1);           // Remove o Valor e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.Venc = linha.substr(0, pos);     // Extrai o Vencimento
            linha.erase(0, pos + 1);           // Remove o Vencimento e a vírgula da linha
            pos = linha.find(",");             // Encontra a segunda vírgula
            d.cdTipoCondicao = linha.substr(0, pos); // Extrai o código do tipo de condição
            linha.erase(0, pos + 1);                 // Remove o código e a vírgula da linha
            dados.push_back(d);                      // Adiciona o objeto d ao vetor de dados
        }
        arquivo.close();                             // Fecha o arquivo
    } else {                                                // Se o arquivo não foi aberto com sucesso
cout << "Erro ao abrir o arquivo " << nome_arquivo << endl; // Imprime uma mensagem de erro
}
return dados;// Retorna o vetor de dados
}

// Define uma função para mostrar os dados em formato de tabela
void mostrar_tabela(vector<Dados> dados) {
    cout << "Nome\tCpfCnpj\tTitulo\tDoc\tParc\tVlr\tVenc\tcdTipoCondicao\n"; // Imprime o cabeçalho da tabela
    for (auto d : dados) {                                                   // Percorre o vetor de dados
        cout << d.Cliente << "\t"                                            // Imprime os dados
        << d.CPF_CNPJ << "\t" 
        << d.Titulo << "\t" 
        << d.Doc << "\t" 
        << d.Parc << "\t" 
        << d.Vlr << "\t" 
        << d.Venc << "\t" 
        << d.cdTipoCondicao << "\t";

        cout << "\n";                                                         // Quebra a linha
    }
}

// Define uma função para remover as linhas onde a coluna cdTipoCondicao é 'AT'
void remover_AT(vector<Dados>& dados) {
    dados.erase(remove_if(dados.begin(), dados.end(), [](Dados d) {
        return d.cdTipoCondicao == "AT"; // Retorna verdadeiro se o código do tipo de condição for 'AT'
    }), dados.end());                    // Remove os elementos que satisfazem a condição
}

// Define uma função para remover os clientes que estão no segundo arquivo do primeiro arquivo
void remover_clientes(vector<Dados>& dados1, vector<Dados> dados2) {
    dados1.erase(remove_if(dados1.begin(), dados1.end(), [&dados2](Dados d1) {
        return any_of(dados2.begin(), dados2.end(), [d1](Dados d2) {
            return d1.Cliente == d2.Cliente; // Retorna verdadeiro se o nome do cliente for igual
        });                                  // Retorna verdadeiro se algum elemento do segundo vetor satisfazer a condição
    }), dados1.end());                       // Remove os elementos que satisfazem a condição
}

// Define uma função para criar um novo arquivo csv com a solução da operação
void criar_csv(vector<Dados> dados, string nome_arquivo) {
    ofstream arquivo(nome_arquivo);                                                                  // Abre o arquivo para escrita
    if (arquivo.is_open()) {                                                                         // Verifica se o arquivo foi aberto com sucesso
        arquivo << "Nome,CPF_CNPJ\tTitulo\tDocumento\tParcela\tValor\tVencimento\tcdTipoCondicao\n"; // Escreve o cabeçalho do arquivo
        for (auto d : dados) {                                                                       // Percorre o vetor de dados
            arquivo << d.Cliente << "|"  
            << d.CPF_CNPJ << "|" 
            << d.Titulo << "|" 
            << d.Doc << "|"
            << d.Parc << "|" 
            << d.Vlr << "|" 
            << d.Venc << "|"
            << "|" << d.cdTipoCondicao << ",";
            arquivo << "\n"; // Quebra a linha
        }
        arquivo.close(); // Fecha o arquivo
    } else {                                                        // Se o arquivo não foi aberto com sucesso
        cout << "Erro ao criar o arquivo " << nome_arquivo << endl; // Imprime uma mensagem de erro
    }
}

// Função principal do programa
int main() {
    string nome_arquivo1;                 // Nome do primeiro arquivo csv
    string nome_arquivo2;                 // Nome do segundo arquivo csv
    string nome_arquivo3 = "solucao.csv"; // Nome do novo arquivo csv

    cout << "Nome do Relatório: "; cin >> nome_arquivo1;
    cout << "Nome da Lista: ";     cin >> nome_arquivo2;

    vector<Dados> dados1 = ler_csv(nome_arquivo1); // Lê o primeiro arquivo csv e armazena os dados em um vetor
    vector<Dados> dados2 = ler_csv(nome_arquivo2); // Lê o segundo arquivo csv e armazena os dados em outro vetor
    
    cout << "Dados do primeiro arquivo antes da operação:\n"; // Imprime uma mensagem
    mostrar_tabela(dados1);           // Mostra os dados do primeiro arquivo em formato de tabela
    remover_AT(dados1);               // Remove as linhas onde a coluna cdTipoCondicao é 'AT'
    remover_clientes(dados1, dados2); // Remove os clientes que estão no segundo arquivo do primeiro arquivo
    
    cout << "Dados do primeiro arquivo depois da operação:\n"; // Imprime outra mensagem
    mostrar_tabela(dados1);           // Mostra os dados do primeiro arquivo em formato de tabela
    criar_csv(dados1, nome_arquivo3); // Cria um novo arquivo csv com a solução da operação
    
    cout << "Novo arquivo csv criado com sucesso: " << nome_arquivo3 << endl; // Imprime uma mensagem de confirmação
    system("pause");
    return 0; // Encerra o programa
}