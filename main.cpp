#include <iostream>
#include <fstream>

using namespace std;

struct Punct
{
    float x , y ;
};

ifstream in ( "date.in");
ofstream out ("date.out");
ofstream liv ("liviu.txt");

bool TestOrintare (Punct p , Punct q , Punct r)  ///retunreaza 1 daca r e la stanga, si 0 altfel
{
    int rezultat =( ( q.x - p.x ) * ( r.y - p.y ) - ( q.y - p.y ) * ( r.x - p.x ) );
    if( rezultat > 0 ) ///r este in stanga
        return 1;
    else
        return 0;
}

bool verificaColiniaritate ( Punct p , Punct q , Punct r ) ///returneaza 1 daca sunt si 0 daca nu sunt
{
    int rez = p.x * ( q.y - r.y ) + q.x * ( r.y - p.y ) + r.x * ( p.y - q.y );
    if( rez == 0)
        return 1; ///sunt coliniare
    else
        return 0;
}

int main()
{
    int numarPuncte , i , rezultat1 , rezultat2 , rezultat3 , coliniare1 , coliniare2 ;
    int verifica = 0; ///o sa fie 0 daca punctul e in afara, 1 daca e in interior si 2 daca e pe latura
    Punct P;

    in >> P.x >> P.y;
    in >> numarPuncte;

    Punct *vectorPuncte = new Punct [ numarPuncte + 1 ];

    for(i = 0 ; i < numarPuncte ; i ++)
    {
        in >> vectorPuncte[i].x >> vectorPuncte[i].y;
    }


    if( (P.x == vectorPuncte[0].x && P.y == vectorPuncte[0].y ) )
    {
        verifica = 2;
        out << "Punctul se afla pe latura A0A1"<<endl;
        liv << 0 << 1 <<endl;

    }
    else if(P.x == vectorPuncte[numarPuncte-1].x && P.y == vectorPuncte[numarPuncte-1].y )
    {
         verifica = 2;
         out << "Punctul se afla pe latura A0A"<<numarPuncte-1<<endl;
         liv << 0 << numarPuncte - 1<<endl;
    }
    else
    {
        for( i = 1 ; i < numarPuncte-1 ; i++ )
        {
            rezultat1 = TestOrintare( vectorPuncte[0] , vectorPuncte[i] , P );
            rezultat2 = TestOrintare( vectorPuncte[0] , vectorPuncte[i+1] , P );

            if( (rezultat1 == 0 && rezultat2 == 1)  ) ///este la dreapta si la stanga unei drepta
            {
                rezultat3 = TestOrintare( vectorPuncte[i] , vectorPuncte[i+1] , P );

                if(rezultat3 == 0) ///se afla in poligon, de verificat daca e pe latura unui poligon sau nu, daca e 0 e in triunghi
                {///daca a intrat pe if inseamna ca punctul e in poligon
                    if( i == 1 )  ///trebuie sa verificam pentru 2 laturi ale primului triunghi
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[0], vectorPuncte[i] , P );  ///A0A1P
                        coliniare2 = verificaColiniaritate( vectorPuncte[i], vectorPuncte[i+1] , P ); ///A1A2P

                        if(coliniare1==1) ///se afla pe latura A0A1
                        {
                            verifica = 2;
                            out <<"Punctul se afla pe latura A0A1"<<endl;
                            liv << 0 << 1 <<endl;
                        }
                        else if(coliniare2 == 1) ///e pe A1A2
                        {
                            verifica = 2;
                            out << " Punctul se afla pe latura A1A2"<<endl;
                            liv << 1 << 2 <<endl;
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului
                            out << "Punctul se afla in triunghiul A0A1A2"<<endl;
                            liv << 0 << 1 << 2;
                        }

                    }
                    else if ( i == numarPuncte - 2 ) ///ultimul triunghi
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[i+1] , vectorPuncte[0] , P ); ///A5A0P
                        coliniare2 = verificaColiniaritate( vectorPuncte[i] , vectorPuncte[i+1] , P ); ///A4A5P

                        if( coliniare1 == 1)
                        {
                            verifica = 2; /// e pe A5A0
                            out << "Punctul se afla pe latura A"<<numarPuncte-1<<"A0 " <<endl;
                            liv << 0 << numarPuncte - 1<<endl;
                        }
                        else if( coliniare2 == 1)
                        {
                            verifica = 2; /// e pe A4A5
                            out << "Punctul se afla pe latura A"<<numarPuncte-2<<"A"<<numarPuncte-1<<endl;
                            liv << numarPuncte-2 << numarPuncte - 1<<endl;
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului;
                            out << "Punctul se afla in triunghiul A0A"<<numarPuncte-2<<"A"<<numarPuncte-1<<endl;
                            liv << 0 << numarPuncte - 2<< numarPuncte - 1 <<endl;
                        }

                    }
                    else ///verificam doar pentru o latura a poligonului
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[i], vectorPuncte[i+1], P );

                        if( coliniare1 == 1)
                        {
                            verifica = 2; ///e pe latura AiAi+1
                            out << "Punctul se afla A"<<i<<"A"<<i+1<<endl;
                            liv << i << i+1 <<endl;
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului
                            out << "Punctul se afla in triunghiul A0"<<"A"<<i<<"A"<<i+1<<endl;
                            liv << 0 << i << i+1 <<endl;
                        }

                    }

                    i = numarPuncte;
                }

                else ///e in afara
                {
                    verifica = 0;
                    i = numarPuncte;
                }
            }
        }
    }

    if( verifica == 0 )
        {
            out << "Punctul P se afla inafara poligonului";
            liv << 0 <<endl ;
        }
    else if( verifica == 1 )
        out << "Punctul P se afla inauntru poligonului";
    else
        out << "Punctul P se afla pe o latura a poligonului";


    return 0;
}
