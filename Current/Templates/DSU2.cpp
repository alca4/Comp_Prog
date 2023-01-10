const int MAXN = 200010;

int p[MAXN];

int root(int n)
{
    return p[n] = (p[n] == n ? n : root(p[n]));
}

void combine(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a!= b)
    {
        p[a] = p[b];
        p[b] = a;
    }
}