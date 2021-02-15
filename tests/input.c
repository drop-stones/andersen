
int foo()
{
    int *ptr, x = 100;
    ptr = &x;
    return *ptr;
}

int bar()
{
    int *p, *q, a, b;
    a = 100; b = 200;
    p = &a;  q = &b;
    p = q;
    return *p;
}

int main(void)
{
    foo();
    bar();
}
