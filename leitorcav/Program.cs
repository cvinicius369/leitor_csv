using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Digite o caminho completo para o relatorio CSV: ");
        string arquivo1 = Console.ReadLine();

        Console.Write("Digite o caminho completo para a lista CSV: ");
        string arquivo2 = Console.ReadLine();

        var data1 = File.ReadAllLines(arquivo1)
                        .Select(line => line.Split(','))
                        .ToList();

        var data2 = File.ReadAllLines(arquivo2)
                        .Select(line => line.Split(';'))
                        .ToList();

        // Imprimir os dados do primeiro arquivo CSV antes da edição
        Console.WriteLine("\nDados do primeiro arquivo CSV antes da edição:");
        Console.WriteLine(new string('-', 5 * data1[0].Length));
        foreach (var row in data1)
        {
            Console.WriteLine("|" + String.Join("|", row.Select(col => col.PadRight(5))) + "|");
            Console.WriteLine(new string('-', 5 * row.Length));
        }

        // Imprimir os dados do segundo arquivo CSV antes da edição
        Console.WriteLine("\nDados do segundo arquivo CSV antes da edição:");
        Console.WriteLine(new string('-', 5 * data2[0].Length));
        foreach (var row in data2)
        {
            Console.WriteLine("|" + String.Join("|", row.Select(col => col.PadRight(5))) + "|");
            Console.WriteLine(new string('-', 5 * row.Length));
        }

        // Remover as linhas onde a coluna cdTipoCondicao é 'AT'
        data1 = data1.Where(row => row[7] != "AT").ToList();

        // Remover do primeiro arquivo os clientes que estão no segundo arquivo
        data1 = data1.Where(row1 => !data2.Any(row2 => row1[0] == row2[1])).ToList();

        Console.Write("Digite o caminho da pasta onde o novo arquivo CSV será criado: ");
        string pasta = Console.ReadLine();
        string novoArquivo = Path.Combine(pasta, "novo_arquivo.csv");

        // Escrever os dados resultantes no novo arquivo CSV
        File.WriteAllLines(novoArquivo, data1.Select(row => string.Join(",", row)));

        // Imprimir os dados em formato de tabela no console
        Console.WriteLine(new string('-', 5 * data1[0].Length));
        foreach (var row in data1)
        {
            Console.WriteLine("|" + String.Join("|", row.Select(col => col.PadRight(5))) + "|");
            Console.WriteLine(new string('-', 5 * row.Length));
        }
    }
}