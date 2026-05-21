// game.cpp
// compile with:

// em++ game.cpp -O2 -s WASM=1 -s EXPORTED_FUNCTIONS='["_move","_getCell","_shuffle"]' -o game.js


extern "C"
{

int field[4][4];

int emptyX = 3;
int emptyY = 3;

unsigned int seed = 123456789;

unsigned int rnd()
{
    seed = seed * 1103515245 + 12345;
    return seed;
}

void init()
{
    int k = 1;

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            field[y][x] = k;
            k++;
        }
    }

    field[3][3] = 0;

    emptyX = 3;
    emptyY = 3;
}

int canMove(int x, int y)
{
    int dx = x - emptyX;
    int dy = y - emptyY;

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    return dx + dy == 1;
}

int move(int x, int y)
{
    if(!canMove(x, y))
    {
        return 0;
    }

    field[emptyY][emptyX] = field[y][x];

    field[y][x] = 0;

    emptyX = x;
    emptyY = y;

    return 1;
}

int getCell(int x, int y)
{
    return field[y][x];
}

void shuffle()
{
    //init();

    for(int i = 0; i < 1000; i++)
    {
        int dir = rnd() % 4;

        int nx = emptyX;
        int ny = emptyY;

        if(dir == 0) nx--;
        if(dir == 1) nx++;
        if(dir == 2) ny--;
        if(dir == 3) ny++;

        if(nx < 0 || nx > 3 ||
           ny < 0 || ny > 3)
        {
            continue;
        }

        move(nx, ny);
    }
}

}
