

int sum(int *numbers, int n)
{

    int acc = 0;
    for (int i = 0; i < n; i++)
    {
        acc += numbers[i];
    }
    return acc;
}