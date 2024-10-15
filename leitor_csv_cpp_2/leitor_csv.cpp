/*
    Projeto: Automação de edição de arquivos csv
    By:      Caio Vinicius de Almeida Faguette
    e-mail:  vinicius182102@gmail.com
    Descrição: 
        O projeto foi feito para a realização de atividade extensionária da faculdade onde o objetivo
        é desenvolver um software para uma instituição a fim de auxiliar as atividades da empresa.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
struct Dados {
    string Cliente; string CPF_CNPJ; string Titulo; string Doc; string Parc; 
    string Vlr; string Venc; string cdTipoCondicao; string telefone;
};
// Função para remover os acentos de uma string
string RemoveAccents(const string& text) {
    const string comAcentos = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
    const string semAcentos = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";
    string result = text;
    for (size_t i = 0; i < comAcentos.size(); ++i) {
        size_t pos;
        while ((pos = result.find(comAcentos[i])) != string::npos) { result.replace(pos, 1, 1, semAcentos[i]); }
    }
    return result;
}
// Função para remover as aspas de uma string
string removerAspas(const string& text) {
    string result = text; size_t pos;
    while ((pos = result.find("\"")) != string::npos) { result.erase(pos, 1); }
    return result;
}
// Função para remover espaços em branco do início e do fim de uma string
string trim(const string& text) {
    size_t start = text.find_first_not_of(" "); size_t end = text.find_last_not_of(" ");
    return (start == string::npos || end == string::npos) ? "" : text.substr(start, end - start + 1);
}
// Função para converter todos os caracteres de uma string para maiúsculas
string to_upper(const string& text) {
    string result = text; transform(result.begin(), result.end(), result.begin(), ::toupper); return result;
}
// Função para converter todos os caracteres de uma string para minúsculas
string to_lower(const string& text) {
    string result = text; transform(result.begin(), result.end(), result.begin(), ::tolower); return result;
}

// Função para ler um arquivo csv e retornar um vetor de dados
vector<Dados> ler_csv(const string& nome_arquivo) {
    const char sep = ';'; vector<Dados> dados; ifstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        string linha;
        getline(arquivo, linha); // Ignora a primeira linha (cabeçalho)
        while (getline(arquivo, linha)) {
            Dados d; stringstream ss(linha); string campo; getline(ss, campo, sep);
            d.Cliente = trim(to_upper(RemoveAccents(removerAspas(campo)))); getline(ss, campo, sep);
            size_t pos = campo.find("CPF: ");
            if (pos != string::npos) { campo.erase(pos, 5);/* Romove o CPF */ }
            d.CPF_CNPJ = campo; getline(ss, campo, sep); d.Titulo = campo; getline(ss, campo, sep);
            pos = campo.find("CT."); if (pos != string::npos) { campo.erase(pos, 3); /* Remove CT */ }
            d.Doc = campo; getline(ss, campo, sep);
            d.Parc = campo; getline(ss, campo, sep); d.Vlr = campo; getline(ss, campo, sep);
            d.Venc = campo; getline(ss, campo, sep);
            d.cdTipoCondicao = campo; getline(ss, campo, sep);
            d.telefone = campo; dados.push_back(d);
        } arquivo.close();
    } else { cout << "Erro ao abrir o arquivo " << nome_arquivo << endl; }
    return dados;
}
// Função para mostrar os dados em formato de tabela
void mostrar_tabela(const vector<Dados>& dados) {
    cout << "Nome\tCpfCnpj\tTitulo\tDoc\tParc\tVlr\tVenc\tcdTipoCondicao\n";
    for (const auto& d : dados) {
        cout << d.Cliente << "\t" << d.CPF_CNPJ << "\t" << d.Titulo << "\t" << d.Doc << "\t"
             << d.Parc << "\t" << d.Vlr << "\t" << d.Venc << "\t" << d.cdTipoCondicao << "\n";
    }
}
// Função para remover as linhas onde a coluna cdTipoCondicao é 'AT'
void remover_AT(vector<Dados>& dados) {
    dados.erase(remove_if(dados.begin(), dados.end(), [](const Dados& d) { return d.cdTipoCondicao == "AT"; }), dados.end());
}
// Função para remover os clientes que estão no segundo arquivo do primeiro arquivo
void remover_clientes(vector<Dados>& dados1, const vector<Dados>& dados2) {
    dados1.erase(remove_if(dados1.begin(), dados1.end(), [&dados2](const Dados& d1) {
        return any_of(dados2.begin(), dados2.end(), [&d1](const Dados& d2) { return d1.CPF_CNPJ == d2.CPF_CNPJ; });
    }), dados1.end());
}
// Função para criar um novo arquivo csv com a solução da operação
void criar_csv(const vector<Dados>& dados, const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        arquivo << "Nome;CPF_CNPJ;Titulo;Documento;Parcela;Valor;Vencimento;cdTipoCondicao;Telefone\n";
        for (const auto& d : dados) {
            arquivo << d.Cliente << ";" << d.CPF_CNPJ << ";" << d.Titulo << ";" << d.Doc << ";"
                    << d.Parc << ";" << d.Vlr << ";" << d.Venc << ";" << d.cdTipoCondicao << ";" << d.telefone << "\n";
        }
        arquivo.close();
    } else { cout << "Erro ao criar o arquivo " << nome_arquivo << endl; }
}
// Função para tornar a interação com o software mais fácil de entender
void style() { cout << "----------------------------------------------------------------------------------" << endl; }
void leitor_csv() {
    string nome_arquivo1; string nome_arquivo2; string nome_arquivo3 = "solucao.csv"; string caminho_arquivo3;
    cout << "Nome do Relatorio: "; cin >> nome_arquivo1; cout << "Nome da Lista: "; cin >> nome_arquivo2; cout << "Caminho do diretorio: ";
    cin >> caminho_arquivo3; style();
    vector<Dados> dados1 = ler_csv(nome_arquivo1); vector<Dados> dados2 = ler_csv(nome_arquivo2);
    cout << "Dados do primeiro arquivo antes da operacao:\n";
    mostrar_tabela(dados1); remover_AT(dados1); remover_clientes(dados1, dados2); style();
    cout << "Dados do primeiro arquivo depois da operacao:\n"; mostrar_tabela(dados1); criar_csv(dados1, caminho_arquivo3 + "/" + nome_arquivo3); 
    style(); cout << "Novo arquivo csv criado com sucesso: " << caminho_arquivo3 + "/" + nome_arquivo3 << endl; style();
}
// Função principal do programa
int main() {
    int action;
    cout << "[1] - Iniciar Procedimento \n[2] - Sair \n-> ";
    cin >> action; style();
    if (action == 1) { leitor_csv(); } 
    else if (action == 2) { cout << "Saindo . . . " << endl; } 
    else { cout << "Acao invalida!" << endl; }
    system("pause"); return 0;
}
// Copyright © 2024, Caio Vinicius de Almeida Faguette

/*
    Commands {
        cd leitor_csv_cpp_2
        g++ leitor_csv.cpp -o LCC2
        ./LCC2
    }
*/
