#include <bits/stdc++.h>

#define VI vector<int>
#define VII vector<pair<int,int>>
#define QI queue<int>

#define ms(a,v) memset( a, v, sizeof( a ) )
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define ROF(i,a,b) for(int i = a; i >= b; i--)
#define foreach(v, c) for( typeof( (c).begin() ) v = (c).begin(); v != (c).end(); ++v)

#define pb push_back
#define pp pair<int,int>
#define mp make_pair
#define fi first
#define se second

#define popcount __builtin_popcount
#define gcd __gcd
#define bit(n,i) ( n & ( 1LL << i ) )
#define lsb(x) ( x & ( -x ) )

#define FIN(str) freopen(str,"r",stdin)
#define FOUT(str) freopen(str,"w",stdout)
#define Fin(str) ifstream(str)
#define Fout(str) ostream(str)
#define SYNC ios_base::sync_with_stdio(0);

#define ll long long
#define ull unsigned long long

inline void read( int &a )
{
    register char ch;
    a = 0;
    int sign = 1;

    do
    {
        ch = getchar();

    } while ( !isdigit( ch ) && ch != '-' );

    if ( ch == '-' )
    {
        sign = -1;
        ch = getchar();
    }

    do
    {
        a = a * 10 + ch - '0';
        ch = getchar();

    } while( isdigit( ch ) );

    a *= sign;
}

inline void write( int a )
{
    char s[20];
    int i = 0;
    int sign = 1;

    if ( a < 0 )
        sign = -1,
        a = -a;

    do
    {
        s[ i++ ] = a % 10 + '0';
        a /= 10;

    } while ( a );

    i--;

    if ( sign == -1 )
        putchar( '-' );

    while ( i >= 0 ) putchar( s[ i-- ] );
}

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

const int dl[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

const int INF = 2e9;
const double EPS = 1e-9;

const int Nmax = 2e3 + 2;

const int LgMax = log2(Nmax) + 1;

using namespace std;

ll d1[Nmax * 2];
ll d2[Nmax * 2];
int A[Nmax][Nmax];

int N;
ll sol1, sol2;
pp a, b;

int main()
{
    ///FIN("data.in");
    ///FOUT("data.out");

    read( N );

    for ( int i = 1; i <= N; ++i )
        for ( int j = 1; j <= N; ++j )
        {
            read( A[i][j] );

            d1[i + j] += 1LL * A[i][j];
            d2[j - i + N] += 1LL * A[i][j];
        }

    for ( int i = 1; i <= N; ++i )
        for ( int j = 1; j <= N; ++j )
            if ( ( i + j ) & 1 )
            {
                if ( d1[i + j] + d2[j - i + N] - 1LL * A[i][j] >= sol1 )
                {
                    sol1 = d1[i + j] + d2[j - i + N] - 1LL * A[i][j];
                    a = pp( i, j );
                }
            }
            else
            {
                if ( d1[i + j] + d2[j - i + N] - 1LL * A[i][j] >= sol2 )
                {
                    sol2 = d1[i + j] + d2[j - i + N] - 1LL * A[i][j];
                    b = pp( i, j );
                }
            }

    cout << sol1 + sol2 << "\n";
    cout << a.fi << " " << a.se << " " << b.fi << " " << b.se;

    return 0;
}
