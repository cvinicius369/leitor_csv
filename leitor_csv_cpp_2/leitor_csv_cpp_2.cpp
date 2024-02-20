/*
    Projeto: Automação de edição de arquivos csv
    By:      Caio Vinicius de Almeida Faguette
    e-mail:  vinicius182102@gmail.com
    Desrcição: 
        O projeto foi feito para a realização de atividade extencionária da faculdade onde o objetivo
        é desenvolver um software para uma instituição a fim de auxiliar as atividades da empresa.
*/
// Inclui as bibliotecas necessárias
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// Funcao que realiza a leitura do arquivo readme que for especificado para instruir o usuario
void leitura(){
    // Abre o arquivo .txt para leitura
    ifstream txt_file("temp.txt");
    if (txt_file.is_open()) {
        string line;                                              // Cria uma string para armazenar cada linha do txt
        while (getline(txt_file, line)) { cout << line << "\n"; } // Lê cada linha do arquivo e imprime no cmd
        txt_file.close();                                         // Fecha o arquivo
    }
    // Mostra uma mensagem de erro se o arquivo .txt não for encontrado
    else { cout << "Não foi possível abrir o arquivo .txt\n"; }
}

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
    string telefone;       // telefone principal
};

// Define uma função para remover os acentos de uma string
// Recebe uma string com acentos e retorna uma string sem acentos
std::string RemoveAccents (std::string text) {
    std::string comAcentos = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
    std::string semAcentos = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";
    for (int i = 0; i < comAcentos.length(); i++) {
        size_t pos = text.find(comAcentos[i]);                           // Encontra a posição do caractere com acento na string
        if (pos != std::string::npos) {                                  // Verifica se a posição é válida
            size_t pos2 = semAcentos.find(comAcentos[i]);                // Encontra a posição do caractere sem acento na string
            if (pos2 < semAcentos.length()) {                            // Verifica se a posição é válida
                text = text.replace(pos, 1, semAcentos.substr(pos2, 1)); // Substitui o caractere com acento pelo sem acento
            }
        }
    }
    return text;
}

// Define uma função para remover as aspas de uma string
// Recebe uma string com aspas e retorna uma string sem aspas
std::string removerAspas (std::string text) {
    size_t pos = text.find("\"");                 // Encontra a posição da primeira aspa na string
    while (pos != std::string::npos) {            // Enquanto houver aspas na string
        text = text.replace(pos, 1, "");          // Substitui a aspa por uma string vazia
        pos = text.find("\"");                    // Encontra a posição da próxima aspa na string
    }
    return text;                                  // Retorna a string sem aspas
}

// Define uma função para remover os espaços em branco do início e do fim de uma string
// Recebe uma string e retorna uma string sem os espaços em branco
std::string trim (std::string text) {
    size_t start = text.find_first_not_of(" ");         // Encontra a posição do primeiro caractere que não é espaço
    size_t end = text.find_last_not_of(" ");            // Encontra a posição do último caractere que não é espaço
    return text.substr(start, end - start + 1);         // Retorna a substring entre as posições encontradas
}

// Define uma função para converter todos os caracteres de uma string para maiúsculas
// Recebe uma string e retorna uma string com todos os caracteres em maiúsculas
std::string toupper (std::string text) {
    for (char& c : text) {             // Percorre cada caractere da string
        c = std::toupper(c);           // Converte o caractere para maiúscula
    }
    return text;                       // Retorna a string convertida
}

// Define uma função para converter todos os caracteres de uma string para minúsculas
// Recebe uma string e retorna uma string com todos os caracteres em minúsculas
std::string tolower (std::string text) {
    for (char& c : text) {            // Percorre cada caractere da string
        c = std::tolower(c);          // Converte o caractere para minúscula
    }
    return text;                      // Retorna a string convertida
}

// Define uma função para ler um arquivo csv e retornar um vetor de dados
vector<Dados> ler_csv(string nome_arquivo) {
    char sep = ';';
    vector<Dados> dados;                       // Vetor para armazenar os dados
    ifstream arquivo(nome_arquivo);            // Abre o arquivo para leitura
    if (arquivo.is_open()) {                   // Verifica se o arquivo foi aberto com sucesso
        string linha;                          // String para armazenar cada linha do arquivo
        getline(arquivo, linha);               // Ignora a primeira linha (cabeçalho)
        while (getline(arquivo, linha)) {      // Lê cada linha do arquivo
            Dados d;                           // Cria um objeto da estrutura Dados
            stringstream ss(linha);            // Cria um stringstream com a linha
            string campo;                      // String para armazenar cada campo da linha
            getline(ss, campo, sep);           // Lê o primeiro campo usando o separador
            // Atribui o campo ao nome do cliente sem aspas, acentos, espaços e em minúsculas
            d.Cliente = trim(toupper(RemoveAccents(removerAspas(campo))));
            getline(ss, campo, sep);           // Lê o segundo campo usando o separador
            d.CPF_CNPJ = campo;                // Atribui o campo ao cpf ou cnpj do cliente
            getline(ss, campo, sep);           // Lê o terceiro campo usando o separador
            d.Titulo = campo;                  // Atribui o campo ao titulo do cliente
            getline(ss, campo, sep);           // Lê o quarto campo usando o separador
            d.Doc = campo;                     // Atribui o campo ao Documento do cliente
            getline(ss, campo, sep);           // Lê o quinto campo usando o separador
            d.Parc = campo;                    // Atribui o campo à parcela
            getline(ss, campo, sep);           // Lê o sexto campo usando o separador
            d.Vlr = campo;                     // Atribui o campo ao Valor
            getline(ss, campo, sep);           // Lê o sétimo campo usando o separador
            d.Venc = campo;                    // Atribui o campo ao Vencimento
            getline(ss, campo, sep);           // Lê o oitavo campo usando o separador
            d.cdTipoCondicao = campo;          // Atribui o campo ao código do tipo de condição
            getline(ss, campo, sep);           // lê o nono capo usando o separador
            d.telefone = campo;                // atribui o campo ao telefone
            dados.push_back(d);                // Adiciona o objeto d ao vetor de dados
        }
        arquivo.close();                       // Fecha o arquivo
    }
    else {                                                          // Se o arquivo não foi aberto com sucesso
        cout << "Erro ao abrir o arquivo " << nome_arquivo << endl; // Imprime uma mensagem de erro
    }
    return dados;                                                   // Retorna o vetor de dados
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
        return d.cdTipoCondicao == "AT";             // Retorna verdadeiro se o código do tipo de condição for 'AT'
        }), dados.end());                            // Remove os elementos que satisfazem a condição
}

// Define uma função para remover os clientes que estão no segundo arquivo do primeiro arquivo
void remover_clientes(vector<Dados>& dados1, vector<Dados> dados2) {
    dados1.erase(remove_if(dados1.begin(), dados1.end(), [&dados2](Dados d1) {
        return any_of(dados2.begin(), dados2.end(), [d1](Dados d2) {
            return trim(toupper(RemoveAccents(removerAspas(d1.Cliente)))) == trim(toupper(RemoveAccents(removerAspas(d2.Cliente))));     // Retorna verdadeiro se o nome do cliente sem aspas, acentos, espaços e em minúsculas for igual
        });                                          // Retorna verdadeiro se algum elemento do segundo vetor satisfazer a condição
    }), dados1.end());                               // Remove os elementos que satisfazem a condição
}

// Define uma função para criar um novo arquivo csv com a solução da operação
void criar_csv(vector<Dados> dados, string nome_arquivo) {
    ofstream arquivo(nome_arquivo);                                                             // Abre o arquivo para escrita
    if (arquivo.is_open()) {                                                                    // Verifica se o arquivo foi aberto com sucesso
        arquivo << "Nome;CPF_CNPJ;Titulo;Documento;Parcela;Valor;Vencimento;cdTipoCondicao\n";  // Escreve o cabeçalho do arquivo
        for (auto d : dados) {                                                                  // Percorre o vetor de dados
            arquivo << d.Cliente << ";"
                << d.CPF_CNPJ << ";"
                << d.Titulo << ";"
                << d.Doc << ";"
                << d.Parc << ";"
                << d.Vlr << ";"
                << d.Venc << ";"
                << d.cdTipoCondicao << ";";
            arquivo << "\n"; // Quebra a linha
        }
        arquivo.close();     // Fecha o arquivo
    }
    else {                                                          // Se o arquivo não foi aberto com sucesso
        cout << "Erro ao criar o arquivo " << nome_arquivo << endl; // Imprime uma mensagem de erro
    }
}

// Funcao somente para tornar a interacao com o software mais facil de entender
void Style(){
    cout << "----------------------------------------------------------------------------------" << endl;
}

void LeitorCsv(){
    string nome_arquivo1;                         // Nome do primeiro arquivo csv
    string nome_arquivo2;                         // Nome do segundo arquivo csv
    string nome_arquivo3 = "solucao.csv";         // Nome do novo arquivo csv
    string caminho_arquivo3;                      // caminho que será salvo o novo arquivo

    cout << "Nome do Relatorio: ";           cin >> nome_arquivo1;
    cout << "Nome da Lista: ";               cin >> nome_arquivo2;
    cout << "Caminho do diretorio: ";        cin >> caminho_arquivo3;
    Style();

    vector<Dados> dados1 = ler_csv(nome_arquivo1); // Lê o primeiro arquivo csv e armazena os dados em um vetor
    vector<Dados> dados2 = ler_csv(nome_arquivo2); // Lê o segundo arquivo csv e armazena os dados em outro vetor

    cout << "Dados do primeiro arquivo antes da operacao:\n"; // Imprime uma mensagem
    mostrar_tabela(dados1);                                   // Mostra os dados do primeiro arquivo em formato de tabela
    remover_AT(dados1);                                       // Remove as linhas onde a coluna cdTipoCondicao é 'AT'
    remover_clientes(dados1, dados2);                         // Remove os clientes que estão no segundo arquivo do primeiro arquivo
    Style();

    cout << "Dados do primeiro arquivo depois da operacao:\n"; // Imprime outra mensagem
    mostrar_tabela(dados1);                                    // Mostra os dados do primeiro arquivo em formato de tabela
    criar_csv(dados1, caminho_arquivo3 + "/" + nome_arquivo3); // Cria um novo arquivo csv com a solução da operação
    Style();

    // Imprime uma mensagem de confirmação// Imprime uma mensagem de confirmação
    cout << "Novo arquivo csv criado com sucesso: " << caminho_arquivo3 + "/" + nome_arquivo3 << endl;
}

// Função principal do programa
int main() {
    int action;                                   // Acao do usuario

    cout << "[1] - Iniciar Procedimento \n[2] - Instrucoes \n-> ";  cin >> action;
    Style();

    if (action == 1){ LeitorCsv(); }            // Abrindo leitor de CSV
    else if (action == 2){ leitura(); }         // Abrindo tutorial
    else { cout << "Acao invalida!" << endl;}   // Imprimindo mensagem de erro

    system("pause");
    return 0; // Encerra o programa
}
// Copyright © 2024, Caio Vinicius de Almeida Faguette