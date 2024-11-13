#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

struct Produto
{
    string nome;
    int quantidadeVendida;
    double preco;
    string dataVenda;
};

void bubbleSort(vector<Produto> &registros)
{
    int n = registros.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (registros[j].preco < registros[j + 1].preco)
            {
                swap(registros[j], registros[j + 1]);
            }
        }
    }
}

void insertionSort(vector<Produto> &registros)
{
    int n = registros.size();
    for (int i = 1; i < n; i++)
    {
        Produto key = registros[i];
        int j = i - 1;
        while (j >= 0 && registros[j].preco < key.preco)
        {
            registros[j + 1] = registros[j];
            j = j - 1;
        }
        registros[j + 1] = key;
    }
}

void selectionSort(vector<Produto> &registros)
{
    int n = registros.size();
    for (int i = 0; i < n - 1; i++)
    {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (registros[j].preco > registros[maxIdx].preco)
            {
                maxIdx = j;
            }
        }
        swap(registros[maxIdx], registros[i]);
    }
}

void shellSort(vector<Produto> &registros)
{
    int n = registros.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            Produto temp = registros[i];
            int j;
            for (j = i; j >= gap && registros[j - gap].preco < temp.preco; j -= gap)
            {
                registros[j] = registros[j - gap];
            }
            registros[j] = temp;
        }
    }
}

int partition(vector<Produto> &registros, int low, int high)
{
    double pivot = registros[high].preco;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (registros[j].preco > pivot)
        {
            i++;
            swap(registros[i], registros[j]);
        }
    }
    swap(registros[i + 1], registros[high]);
    return i + 1;
}

void quickSort(vector<Produto> &registros, int low, int high)
{
    if (low < high)
    {
        int pi = partition(registros, low, high);
        quickSort(registros, low, pi - 1);
        quickSort(registros, pi + 1, high);
    }
}

void countingSort(vector<Produto> &registros)
{
    int n = registros.size();

    int maxPreco = 0;
    for (const auto &produto : registros)
    {
        maxPreco = max(maxPreco, static_cast<int>(produto.preco));
    }

    vector<int> count(maxPreco + 1, 0);
    vector<Produto> output(n);

    for (int i = 0; i < n; i++)
    {
        count[static_cast<int>(registros[i].preco)]++;
    }

    for (int i = maxPreco - 1; i >= 0; i--)
    {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < n; i++)
    {
        int precoInt = static_cast<int>(registros[i].preco);
        output[--count[precoInt]] = registros[i];
    }

    registros = output;
}

void gerarDados(vector<Produto> &registros, int numRegistros)
{
    for (int i = 0; i < numRegistros; i++)
    {
        Produto p;
        p.nome = "Produto_" + to_string(i + 1);
        p.quantidadeVendida = rand() % 100 + 1;
        p.preco = rand() % 10000 / 100.0;
        p.dataVenda = "01/10/2024";
        registros.push_back(p);
    }
}


int main()
{
    int cenarios[] = {1000, 100000, 1000000};

    for (int numRegistros : cenarios)
    {
        cout << "\nCenario com " << numRegistros << " registros:\n";

        vector<Produto> registros;
        gerarDados(registros, numRegistros);

        auto inicio = chrono::high_resolution_clock::now();
        bubbleSort(registros);
        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim - inicio;
        cout << "Tempo de execucao (Bubble Sort): " << duracao.count() << " segundos" << endl;

        registros.clear();
        gerarDados(registros, numRegistros);

        inicio = chrono::high_resolution_clock::now();
        insertionSort(registros);
        fim = chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "Tempo de execucao (Insertion Sort): " << duracao.count() << " segundos" << endl;

        registros.clear();
        gerarDados(registros, numRegistros);

        inicio = chrono::high_resolution_clock::now();
        selectionSort(registros);
        fim = chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "Tempo de execucao (Selection Sort): " << duracao.count() << " segundos" << endl;

        registros.clear();
        gerarDados(registros, numRegistros);

        inicio = chrono::high_resolution_clock::now();
        shellSort(registros);
        fim = chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "Tempo de execucao (Shell Sort): " << duracao.count() << " segundos" << endl;

        registros.clear();
        gerarDados(registros, numRegistros);

        inicio = chrono::high_resolution_clock::now();
        quickSort(registros, 0, registros.size() - 1);
        fim = chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "Tempo de execucao (Quicksort): " << duracao.count() << " segundos" << endl;

        registros.clear();
        gerarDados(registros, numRegistros);

        inicio = chrono::high_resolution_clock::now();
        countingSort(registros);
        fim = chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "Tempo de execucao (Counting Sort): " << duracao.count() << " segundos" << endl;
    }

    return 0;
}