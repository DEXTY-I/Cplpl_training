#include <iostream>

int main()
{
    int n{};
    std::cin >> n;
    int x = 1;
    int y = 0;
    for (int i = 0; i < n; i++)
    {
        std::cout << x << ' ';
        int z = x;
        x = x + y;
        y = z;
    }
    return 0;
}
