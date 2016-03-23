// #1 //
long int BuscaSequencialIterativa( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	for ( auto i = left ; i < right ; i ++ ){
		if ( k == A[i] ){
			if ( ocorrencia==1 || ocorrencia == 0 ) return i;
			ocorrencia--;
		}
	}
	return -1;
}

// #2 //
long int BuscaSequencialRecursiva( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	if ( left > right ) return -1;
	else{
		if( k == A[left] && (ocorrencia == 1 || ocorrencia == 0) ) return left;
	 	else if ( k==A[left] ) return BuscaSequencialRecursiva( A, k, left+1, right, ocorrencia-1 );
	 	else return BuscaSequencialRecursiva( A, k, left+1, right, ocorrencia );
	}
}

// #3 //
long int BuscaBinariaIterativa( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	long int middle;
	while ( right >= left ){
		middle = ( left + right ) / 2;
		if ( k == A[middle] ){
			if ( ocorrencia >= 1 ){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle-1] == k ){
					while ( A[middle-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle-i+ocorrencia;
					else return -1;
				}
				else return middle;
			}
			return middle;
		}
		else if ( k < A[middle] ) right = middle-1;
		else left = middle + 1;
	}
	return -1;
}

// #4 //
long int BuscaBinariaRecursiva ( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	long int middle = 0;
	if ( left > right ) return -1;
	else{
		middle = ( left + right ) / 2;
		if ( k == A[middle] ){
			if ( ocorrencia >= 1 ){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle-1] == k ){
					while ( A[middle-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle-i+ocorrencia;
					else return -1;
				}
				else return middle;
			}
			return middle;
		}
		else if ( k < A[middle] ) return BuscaBinariaRecursiva( A, k, left, middle-1, ocorrencia );
		else return BuscaBinariaRecursiva( A, k, middle+1, right, ocorrencia );
	}
}

// #5 //
long int BuscaTernariaIterativa( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	long int middle1, middle2;
	while ( left <= right ){
		middle1 = ( 2*left + right ) / 3; // forma simplificada de ::: middle1 = left + (right - left) * 1 / 3;
		middle2 =  ( left + 2*right ) / 3; // forma simplificada de ::: middle2 = left + (right - left) * 2 / 3;

		// Achando os valores
		if ( k == A[middle1] ){
			if ( ocorrencia >= 1 ){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle1-1] == k ){
					while ( A[middle1-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle1+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle1-i+ocorrencia;
					else return -1;
				}
				else return middle1;
			}
			return middle1;			
		}
		if ( k == A[middle2] ){
			if ( ocorrencia >= 1 ){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle2-1] == k ){
					while ( A[middle2-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle2+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle2-i+ocorrencia;
					else return -1;
				}
				else return middle2;
			}
			return middle2;			
		}

		// Valor está do lado esquerdo
		if ( k < A[middle1] ) right = middle1 - 1;

		// Valor está no meio
		if ( k > A[middle1] && k < A[middle2] ) left = middle1 + 1, right = middle2 - 1;

		// Valor está no lado direito
		if ( k > A[middle2] ) left = middle2 + 1;
	}
	return -1;
}

// #6 //
long int BuscaTernariaRecursiva( std::vector<long int> & A, long int k, long int left, long int right, int ocorrencia ){
	long int middle1, middle2;
	if ( left > right ) return -1;
	else{
		middle1 = (2*left + right)/3;
		middle2 = (left + 2*right)/3;	

		if( k == A[middle1] ){
			if ( ocorrencia >= 1 ){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle1-1] == k ){
					while ( A[middle1-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle1+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle1-i+ocorrencia;
					else return -1;
				}
				else return middle1;
			}
			return middle1;				
		}

		else if( k == A[middle2] ){
			if (ocorrencia >= 1){
				auto i(1);				
				// Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.
				if( A[middle2-1] == k ){
					while ( A[middle2-i] == k ){ // Vai contar quantos valores tem antes, o resultado é i-1.
						i++;
					}
					// Se tiver um valor ocorrencia-1 na frente igual ao k, ele retorna a posição, se não houver, -1.
					if( A[middle2+ocorrencia-i] == k ) // simplificou de > middle-i+1+ocorrencia-1 <
						return middle2-i+ocorrencia;
					else return -1;
				}
				else return middle2;
			}
			return middle2;				
		}

		else if ( k < A[middle1] ) return BuscaTernariaRecursiva( A, k, left, middle1 - 1, ocorrencia );
		else if ( k > A[middle1] && k < A[middle2] ) return BuscaTernariaRecursiva( A, k, middle1 + 1, middle2 - 1, ocorrencia );
		else return BuscaTernariaRecursiva( A, k, middle2 + 1, right, ocorrencia );
	}
}

// #7 //
long int SearchWrapper( std::vector <long int> &A, long int key, long int left, long int right, int ocorrencia ){
	long int needle[1] = { key };
	std::vector< long int >::iterator it;
	it = std::search ( A.begin(), A.begin()+right, needle, needle+1 );
    /// A.end() ->>>> A.begin() + right porque o nosso fim não é o fim de A, e sim o right
    if ( it!=A.begin()+right && ocorrencia < 2 )
            return (it-A.begin());
    else if ( it!=A.begin()+right && ocorrencia > 1 ){
        while( ocorrencia > 1 ){
            ocorrencia--;
            it = std::search( it-left+1, A.begin()+right, needle, needle+1 );
        }
        if ( it != A.begin()+right ) return ( it-A.begin() );
        else return -1;
    }
    else return -1;
}

// #8 //
long int BSearchWrapper( std::vector <long int> &A, long int key, long int left, long int right, int ocorrencia ){
    long int *p1 = ( long int * ) std::bsearch( &key, A.data(), right-left, sizeof(A[0]), compare );
    if( p1 == NULL )
        return -1;
    // ESSE SÓ TÁ FUNCIONANDO PRA OCORRÊNCIA == 3, QUE É O NECESSÁRIO PRO TRABALHO :d
    else if ( ocorrencia==3 ){
            auto i(1);
            // Enquanto houver um valor anterior igual ao k, ele será procurado. i == primeiro caso.        
            if( A[(p1 - &A[0])] == key ){
                while ( A[(p1 - &A[i])] == key ){ // Vai contar quantos valores tem antes, o resultado é i-1.
                    i++;
                }
            }
            if( A[(p1 - &A[0])+ocorrencia-i] == key ) // simplificou de > (p1 - &A[0])-i+1+ocorrencia-1 <
                return ( p1 - &A[0] )-i+ocorrencia;
            else return -1;
        }
    else return ( p1 - &A[0] );
}