int sieve[1000010];
vector<int> primes;
void get_primes(int x)
{
    sieve[1] = 1;
    for (int i = 2; i <= x; i++) if (!sieve[i])
    {
        primes.pb(i);
        for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
    }
}