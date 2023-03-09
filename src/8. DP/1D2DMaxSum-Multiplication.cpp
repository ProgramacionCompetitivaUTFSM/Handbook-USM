#include "../Header.cpp"

int main()
{
    // 1D Max Array Sum
    int n = 9, A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 }; //Allow all negative numbers
    int sum = A[0], ans = A[0];
    for (int i = 1; i < n; i++)
    {
        sum = max(A[i] + sum, A[i]); // Ignores sum if prev sum is worse than A[i]
        ans = max(ans, sum);
    }
    cout << ans << "\n";

    // 2D Max Array Sum
    int B [100][100];
    ans = -INF;
    cin>>n;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    {
        cin >> B[i][j];
        if (j > 0) B[i][j] += B[i][j-1]; // Acum sum per Row
    }
    for (int l = 0; l < n; l++) for (int r = l; r < n; r++)
    {
        sum = B[0][r];
        int SubAns = B[0][r];
        if (l > 0){ sum -= B[0][l-1]; SubAns -= B[0][l-1]; }
        for (int row = 1; row < n; row++)
        {
            int aux = B[row][r];
            if(l > 0) aux -= B[row][l-1];
            sum = max(sum + aux, aux);
            SubAns = max (SubAns, sum);
        }
        ans = max(ans, SubAns);
    }
    cout << ans << "\n";

    // Max Array Multiplication
    vl c;
    bool o = 0;
    ans = 1;
    ll miniend = 1, maxiend = 1;
    for (int i = 0; i < c.size(); i++)
    {
        if(c[i] > 0)
        {
            o = 1;
            if(miniend < 0)miniend *= c[i];
            maxiend *= c[i];
        }
        else if(c[i] == 0)
        {
            miniend = 1;
            maxiend = 1;
        }
        else
        {
            int aux = maxiend;
            maxiend = max(1LL, miniend * c[i]);
            miniend = aux*c[i];
        }
        ans = max(ans, maxiend);
    }
    if(ans == 1 && !o) cout << "0\n";
    else
    {
        cout << ans << "\n";
    }


    // n dimension acumulative sum
    for dim = 0 to 4
        for a = 0 to na-1
            for b = 0 to nb-1
                for c = 0 to nc - 1
                    for d = 0 to nd - 1
                        pa = a - (dim==0); pb = b - (dim==1); pc = c - (dim==2);
                        pd = d - (dim==3);
                        if (pa >= 0 && pb >= 0 && pc >= 0 && pd >= 0)
                            dp(a, b, c, d) += dp (pa, pb, pc, pd)
    // o por cada celda
    for x in S //(celda de menor a mayor tal que todas las anteriores estan procesadas)

}
