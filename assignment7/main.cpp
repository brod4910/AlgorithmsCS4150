#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

long long extended_euclids(long long a, long long b, long long &x, long long &y);
long long modular_multi_inverse(long long a, long long N);
long long gcd(long long a, long long b);
long long modular_exponentiation(long long x, long long y, unsigned long long N);
std::string RSA_algorithm(long long p, long long q);
bool is_prime(long long N);

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

	std::string method;
	long long x, y, z;

	while(std::cin >> method >> x)
	{
		if(method == "gcd")
		{
			std::cin >> y;
			std::cout << gcd(x, y) << std::endl;
		}
		else if(method == "exp")
		{
			std::cin >> y;
			std::cin >> z;
			std::cout << modular_exponentiation(x, y, z) << std::endl;
		}
		else if(method == "inverse")
		{
			std::cin >> y;
			long long res;
			if((res = modular_multi_inverse(x, y)) == -1)
			{
				std::cout << "none" << std::endl;
			}
			else
			{
				std::cout << res << std::endl;
			}
		}
		else if(method == "isprime")
		{
			if(is_prime(x))
			{
				std::cout <<  "yes" << std::endl;
			}
			else
			{
				std::cout <<  "no" << std::endl;
			}
		}
		else
		{
			std::cin >> y;
			std::cout << RSA_algorithm(x, y) << std::endl;
		}
	}

	return 0;
}

long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}

long long modular_exponentiation(long long x, long long y, unsigned long long N)
{
	long long res = 1;

	x = x % N;

	while(y > 0)
	{
		if(y & 1)
		{
			res = (res * x) % N;
		}

		y = y >> 1;
		x = (x*x) % N;
	}

	return res;
}

long long modular_multi_inverse(long long a, long long N)
{
	long long x, y;

	long long g = extended_euclids(a, N, x, y);

	if(g != 1)
	{
		return -1;
	}
	else
	{
		return (x % N + N) % N;
	}
}

long long extended_euclids(long long a, long long b, long long &x, long long &y)
{
	if(a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	else
	{
		long long xp, yp;

		long long d = extended_euclids(b % a, a, xp, yp);

		x = yp - (b/a) * xp;
		y = xp;
		return d;
	}
}


bool is_prime(long long N)
{
	int i = 2;

	if(N <= 1 || N == 4)
	{
		return false;
	}
	else if(N <= 3)
	{
		return true;
	}

	while(i <= 5)
	{
		if(modular_exponentiation(i, N - 1, N) != 1)
		{
			return false;
		}

		i = (i * 2) - 1;
	}

	return true;
}

std::string RSA_algorithm(long long p, long long q)
{
	std::string res = "";

	long long public_exp = 2, private_exp;

	long long N = p*q;
	res += (std::to_string(N) + " ");

	long long phi = (p-1)*(q-1);

	while(public_exp < phi)
	{
		if(gcd(public_exp, phi) == 1)
		{
			res += (std::to_string(public_exp) + " ");
			break;
		}
		else
		{
			public_exp++;
		}
	}

	private_exp = modular_multi_inverse(public_exp, phi);

	res += std::to_string(private_exp);

	return res;
}
