//Comparação de 2 valores (BSearch)
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

//Media instantanea de um vetor
float media_instantanea( std::vector <float> valores, int m)
{
    int k = 1;
    float media = 0;
    for ( auto i(0) ; m != k ; i++ ){
        media = media + (valores[i]-media)/k;
        k++;
    }
    return media;
}

//Fill a vector with random numbers in the range [lower, upper]
void randomFill( std::vector<long int> &V, const long int lower, const long int upper, const unsigned int seed) {

    //use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<long double> distr(lower, upper);

    for( auto &elem : V){
        elem = distr(eng);
    }
}