#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <chrono>
#include <cstdlib>

#include "other_functions.cpp"
#include "buscas.cpp"

#define N 134217728 // Number of elements

int main( int argc, char * argv[] )
{
    // teste é a variável que guarda o código que será testado
    // teste == 0 -> busca linear iterativa ... teste == 5 -> busca ternária recursiva
    auto teste(-1), ocorrencia(0), situacao(-1), key(0), ordenado(0), keyposition(0), fim(1);
    std::string tst="valores.txt";
    std::ofstream outfile;
    std::vector< float > resultados_buscas( 100 );

    // ponteiro para funções
    // pfunc[0] = BuscaSequencialIterativa
    // ...
    // pfunc[5] = BuscaTernariaRecursiva
    long int (*pfunc[])( std::vector<long int> &, long int, long int, long int, int) = 
    {
        BuscaSequencialIterativa, BuscaSequencialRecursiva, BuscaBinariaIterativa,
        BuscaBinariaRecursiva, BuscaTernariaIterativa, BuscaTernariaRecursiva,
        SearchWrapper, BSearchWrapper
    };

    auto arrSz( 0ul );

    if ( argc > 1 )
    {
        std::stringstream( argv[1] ) >> arrSz;
    }
    else
    {
        arrSz = N;
    }

    std::cout << ">>> Required array size is: " << arrSz << std::endl;

    // Store the data.
    std::cout << ">>> Alocando vetor.\n";
    std::vector< long int > V( arrSz ); // 2^27 = 134217728
    std::cout << ">>> Vetor alocado.\n";
    
    // Seed with a real random value, if available.
    std::random_device r;
    
    // Fill it up with random integers.
    std::cout << ">>> Preenchendo vetor...\n";
    randomFill( V, -134217728, 134217728, 1 );
    
    //Printint out the array, just to make sure we've got random integers.    
    /*std::cout << ">>> Vet = [ ";
    for( const auto &e : V )
        std::cout << e << " ";
    std::cout << "]\n";*/
    std::cout << ">>> Vetor preenchido.\n";

    std::cout << "\nVetor ordenado? (1/0) ";
    std::cin >> ordenado;  

    if (ordenado==1)
    {
        std::cout << ">>> Ordenando vetor...\n";
        std::sort (V.begin(), V.end());
        std::cout << ">>> Vetor ordenado.\n";

        /*std::cout << ">>> Vet = [ ";
        for( const auto &e : V )
            std::cout << e << " ";
        std::cout << "]\n";*/
    }    

    while(fim == 1){
        while ( teste < 0 || teste > 7 )
        {
            std::cout << "\nTABELA:\n";
            std::cout << "0 : SEQUENCIAL  ITERATIVA\n";
            std::cout << "1 : SEQUENCIAL  RECURSIVA\n";
            std::cout << "2 : BINÁRIA     ITERATIVA\n";
            std::cout << "3 : BINÁRIA     RECURSIVA\n";
            std::cout << "4 : TERNÁRIA    ITERATIVA\n";
            std::cout << "5 : TERNÁRIA    RECURSIVA\n";
            std::cout << "6 : SEQUENCIAL (STD::SEARCH)\n";
            std::cout << "7 : BINÁRIA   (STD::BSEARCH)\n\n";        
            std::cout << "Digite o codigo a testar: ";
            std::cin >> teste;
        }
        std::cout << "\n";


        switch(teste)
        {
            case 0:
                tst="valores_bsi.txt";
                break;
            case 1:
                tst="valores_bsr.txt";
                break;
            case 2:
                tst="valores_bbi.txt";
                break;
            case 3:
                tst="valores_bbr.txt";
                break;
            case 4:
                tst="valores_bti.txt";
                break;
            case 5:
                tst="valores_btr.txt";
                break;
            case 6:
                tst="valores_bsic.txt";
                break;
            case 7:
                tst="valores_bbic.txt";
                break;
        }

        outfile.open(tst);              

        while ( situacao < 0 || situacao > 2 )
        {
            std::cout << "TABELA:\n";
            std::cout << "0 : K NÃO ESTÁ NO VETOR\n";
            std::cout << "1 : K ESTÁ A 3/4 DO INÍCIO DO VETOR\n";
            std::cout << "2 : O TERCEIRO K, SE EXISTIR, É PROCURADO\n\n";    
            std::cout << "Digite a situação do teste: ";
            std::cin >> situacao;
        }
        std::cout << "\n";  

        std::cout << ">>> Iniciando testes...\n";
        // i é a variável que vai variar o tamanho do vetor a cada 100 testes
        for ( auto i(4u); i <= arrSz ; i *= 2){     
            // Variável para contagem dos 100 testes	
            auto testes(0);

            switch (situacao)
            {
                case 0:
                    key = 134217729; // Valor qualquer não presente no vetor.
                    ocorrencia = 0;
                    break;
                case 1:
                    keyposition = (3 * (i-1))/4;
                    //std::cout << ">>> Key position: " << keyposition << std::endl;
                    key = V[keyposition];
                    ocorrencia = 0;
                    //std::cout << key << std::endl;
                    break;
                case 2:
                    key = 134200700;
                    ocorrencia=3;
                    //std::cout << ">>> RANDOM KEY: " << key << std::endl;
                    break;
            }

            // Fazendo 100 testes para um vetor de tamanho i até arrSz com variações de i*2       
            while (testes < 100)
            {
                //std::cout << ">>> Fazendo busca... " << testes << " de " << 99 << ".\n";
                auto start = std::chrono::steady_clock::now();
                //=====================================================//

                /*std::cout << */pfunc[teste](V,key,0,i,ocorrencia);

                //=====================================================//
                auto end = std::chrono::steady_clock::now();

                //Store the time difference between start and end
                auto diff = end - start;

                resultados_buscas[testes] =  std::chrono::duration <double, std::milli> (diff).count();
                testes++;
            }
            std::cout << ">>> Testes finalizados.\n";
            std::cout << ">>> Calculando média e gravando em arquivo...\n";
            auto media = media_instantanea(resultados_buscas, 100);      

            if (outfile.is_open() && outfile.good())
            {
                outfile << i << " " << media << std::endl;
            }
            std::cout << ">>> Média das execuções para " << i << " elementos: " << media << ".\n";
        }

        std::cout << ">>> Saindo...\n";
        outfile.close();
        std::cout << "Deseja refazer teste com outra configuração? (1/0)";
        std::cin >> fim;
        teste=-1;
        situacao=-1;
    }
    return EXIT_SUCCESS;
}