#include <iostream>
#include <cstring>
using namespace std;

class SieveOfEratosthenes {
    public:
        SieveOfEratosthenes(int n) {
            bool prime[n+1];
            memset(prime, true, sizeof(prime));
            int p, i;
            for (p=2; p*p<=n; p++)
            {
                if (prime[p] == true)
                {
                    for (i = p*p; i<=n; i+=p)
                    {
                        prime[i] = false;
                    }
                }
            }
            cout<<"Following are the prime nos less than or equal to "<<n<<endl;
            for (p = 2; p <= n; p++)
            {
                if (prime[p] == true)
                {
                    cout<<p<<", ";
                }
            }
            cout<<"\b\b ";
        }
};

class CheckNumber {
    private:
        int n;
    public:
        CheckNumber() {
            cout<<"Enter a number : ";
            cin>>n;
            if (n < 2)
            {
                cout<<"Prime nos start from 2. Type a correct number"<<endl;
                CheckNumber();
            }
            else
            {
                SieveOfEratosthenes soe(n);
            }
        }
};

int main()
{
    CheckNumber cn;
    return 0;
}