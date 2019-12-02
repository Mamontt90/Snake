#include"TXLib.h"

struct cart
{
    int mp[500][500];
    int H,L;
    int x,y,dx,dy,N;
    COLORREF color;
}first;

struct calc
{
    int x,y,dx,dy,delt,napr;
    int L,SL,SH;
    int coord[1000][2];
    COLORREF color1;
}one;

struct cart generated_cart(struct cart first);
struct calc clac_one(struct calc one);
void drow_cart(struct cart first);
int main()
{
    one.x=10;                       //координата старта x
    one.y=10;                       //координата старта y
    one.delt = 1;                   //скорость
    one.dx=0;                       //перемещение по x
    one.dy = 1;                     //перемещение по y
    one.L = 1;                      //длинна змеи
    one.SL = 44;                    //ширина картинки
    one.SH = 44;                    //высота картинки
    one.coord[0][0]=one.x;          //массив хранящий координаны каждой ячейки змеи
    one.coord[0][1]=one.y;

    first.H=30;                     //высота поля
    first.L=30;                     //ширина поля
    first.x=1;                      //точки отсчёта рисования поля
    first.y=1;
    first.dx=44;                    //ширина вставляемой картинки
    first.dy=44;                    //высота вставляемой картинки
    first.N=10;                     //количество областей куда нельзя
    first.color=RGB(255,255,255);   //цвет удаляемого фона

    //first = generated_cart(first);
    //drow_cart(first);

    while(GetAsyncKeyState(VK_ESCAPE) == 0)
    {
    if(GetAsyncKeyState(VK_DOWN) != 0 && one.napr !=3)
    {
        one.dx=0;
        one.dy = -1*one.delt;
        one.napr = 3;

    }

    if(GetAsyncKeyState(VK_LEFT) != 0 && one.napr !=4 )
    {
        one.dx-= one.delt;
        one.dy=0;
        one.napr = 4;
    }

    if(GetAsyncKeyState(VK_RIGHT) != 0 && one.napr !=2)
    {
        one.dx += one.delt;
        one.dy =0;
        one.napr = 2;
    }

    if(GetAsyncKeyState(VK_UP) != 0 && one.napr !=1 )
    {
        one.dx = 0;
        one.dy = one.delt;
        one.napr = 1;
    }

    one.x += one.dx;
    one.y += one.dy;

    if(first.mp[one.y][one.x] == 4)
    {
        one.L++;

        srand(time(NULL));

        if(rand() % 2 == 0)
        {
            first.mp[rand() % first.H][rand() % first.L] = 3;
        }else
        {
            first.mp[rand() % first.H][rand() % first.L] = 4;
        }

    }else if(first.mp[one.y][one.x] == 3)
    {
        one.L+=3;

        srand(time(NULL));

        if(rand() % 2 == 0)
        {
            first.mp[rand() % first.H][rand() % first.L] = 3;
        }else
        {
            first.mp[rand() % first.H][rand() % first.L] = 4;
        }

    }

    if(one.x == first.L || one.x == 0 || one.y == first.H || one.y == 0)
    {
        printf("GAME OVER");
        Sleep(500);
        return 0;
    }

        Sleep(1000);
    }
}

struct cart generated_cart(struct cart first)
{
    for(int y=0;y<first.H;y++)
    {
        for(int x=0;x<first.L;x++)
        {

            first.mp[y][x] = 1;

        }
    }

    srand(time(NULL));


    for(int i=0;i<first.N;i++)
    {
        first.mp[rand() % first.H][rand() % first.L] = 2;
    }

    if(rand() % 2 == 0)
    {
        first.mp[rand() % first.H][rand() % first.L] = 3;
    }else
    {
        first.mp[rand() % first.H][rand() % first.L] = 4;
    }

    return(first);
}

void drow_cart(struct cart first)
{

    txCreateWindow(first.L*first.dx+2,first.H*first.dy+2);
    txSetFillColor(RGB(255,255,255));
    txClear();

    HDC  picture = txLoadImage ("Map.bmp",IMAGE_BITMAP);


    for(int y=0;y < first.H;y++)
    {
        for(int x=0;x < first.L;x++)
        {
            if(first.mp[y][x] == 1)
            {
                Win32::TransparentBlt (txDC(), first.x+first.dx*x, first.y+first.dy*y, first.dx, first.dy,picture, 88, 0, first.dx, first.dy,first.color);
            }else if(first.mp[y][x] == 2)
            {
                Win32::TransparentBlt (txDC(), first.x+first.dx*x, first.y+first.dy*y, first.dx, first.dy,picture, 132, 0, first.dx, first.dy,first.color);
            }else if(first.mp[y][x] == 3)
            {
                Win32::TransparentBlt (txDC(), first.x+first.dx*x, first.y+first.dy*y, first.dx, first.dy,picture, 44, 0, first.dx, first.dy,first.color);
            }else if(first.mp[y][x] == 4)
            {
                Win32::TransparentBlt (txDC(), first.x+first.dx*x, first.y+first.dy*y, first.dx, first.dy,picture, 0, 0, first.dx, first.dy,first.color);
            }
        }
    }

    txDeleteDC(picture);
}

