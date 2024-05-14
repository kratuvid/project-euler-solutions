#include <iostream>

int main()
{
    int sum = 0;
    for (int i=0; i < 1000; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            std::cout << i << " is a multiple of 3 or 5. Adding..." << std::endl;
            sum += i;
        }
    }
    std::cout << "Sum is " << sum << std::endl;
}
