#define WASM_EXPORT __attribute__((visibility("default")))

extern int mem[1024];

WASM_EXPORT
int sum(int *numbers, int n)
{

    int acc = 0;
    for (int i = 0; i < n; i++)
    {
        acc += numbers[i];
    }
    return acc;
}