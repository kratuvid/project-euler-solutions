#include <iostream>

int main()
{
    for (unsigned i=1; i <= 999; i++)
    {
        for (unsigned j=i; j <= 999; j++)
        {
            for (unsigned k=j; k <= 999; k++)
            {
                if (i*i + j*j == k*k)
                {
                    std::cout << "Found Pythagorean triplet ";
                    std::cout << i << "^2 + " << j << "^2 = " << k << "^2" << std::endl;

                    if (i + j + k == 1000)
                    {
                        std::cout << "This is the special triplet where ";
                        std::cout << i << " + " << j << " + " << k << " = " << 1000 << std::endl;

                        std::cout << "Product abc is " << i * j * k << std::endl;
                        return 0;
                    }
                }
            }
        }
    }
}
