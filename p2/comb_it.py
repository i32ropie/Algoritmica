#!/usr/bin/env python
import sys

# long long fact_n = 1, fact_k = 1, fact_nk = 1;
# for( int i = 2 ; i <= n ; ++i )
# fact_n *= i;
# for( int i = 2 ; i <= k ; ++i )
# fact_k *= i;
# for( int i = 2 ; i <= (n-k) ; ++i )
# fact_nk *=

n = int(sys.argv[1])
k = int(sys.argv[2])

fact_n, fact_k, fact_nk = 1, 1, 1

for x in range(2, n+1):
    fact_n *= x

for x in range(2, k+1):
    fact_k *= x

for x in range(2, (n-k)+1):
    fact_nk *= x


print(fact_n//fact_k//fact_nk)
