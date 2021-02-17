
struct Vector2D {
    int x;
    int y;
};

int main(void)
{
    struct Vector2D v;
    v.x = 100;
    v.y = 200;
    return v.x;
}