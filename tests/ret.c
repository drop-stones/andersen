
int* one(void)
{
    int *p, a;
    a = 1;
    p = &a;
    return p;
}
//int* two(void)   { int b = 2; return &b; }
//int* three(void) { int c = 3; return &c; }

int main(void)
{
    return *one();
}