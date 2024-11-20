#include <iostream>
#include <fstream>
#include <string>
//#include <vector>
#include <cmath>


using namespace std;


int **array2_int(int m, int n)
{
    int **array = new int*[n];
    for(size_t i{0}; i<n; i++)
    {
        array[i] = new int[m];
        for(size_t j{0}; j<m; j++)
        {
            array[i][j] = 0b0;
        }
    }

    return array;
}


bool intpoint_inside_trigon(double sx, double sy, double ax, double ay, double bx, double by, double cx, double cy)
{
    int as_x = sx - ax;
    int as_y = sy - ay;

    bool s_ab = (bx - ax) * as_y - (by - ay) * as_x > 0;

    if ((cx - ax) * as_y - (cy - ay) * as_x > 0 == s_ab)
        return false;
    if ((cx - bx) * (sy - by) - (cy - by)*(sx - bx) > 0 != s_ab)
        return false;
    return true;
}


//-------------------------------------------------------------------------- Rectangle

class Rectangle {
    public:
        double dx;
        double x_center;
        double y_center;
        double a;
        double b;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<5; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x_c")   x_center = value;

            if(parametr == "y_c")   y_center = value;

            if(parametr == "a")     a = value;
           
            if(parametr == "b")     b = value;

            if(parametr == "mat")     mat = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x_start = (x_center-a/2 + 0.5)/dx;
            int y_start = (y_center-b/2 + 0.5)/dx;
            int x_stop = (x_center+a/2 + 0.5)/dx;
            int y_stop = (y_center+b/2 + 0.5)/dx;
           
            if(x_start<0) x_start=0;
            if(y_start<0) y_start=0;

            if(x_stop>geometry_x_n) x_stop=geometry_x_n;
            if(x_stop>geometry_y_n) y_stop=geometry_y_n;
           
            for(size_t i = x_start; i<=x_stop; i++)
            {
                for(size_t j = y_start; j<=y_stop; j++)
                {
                    geometry[i][j] = mat;
                }
            }
           
            return geometry;
        }
};

//--------------------------------------------------------------------------

//-------------------------------------------------------------------------- Rectangle Wall

class RectangleWall {
    public:
        double dx;
        double x_center;
        double y_center;
        double a;
        double b;
        double t;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<6; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x_c")   x_center = value;

            if(parametr == "y_c")   y_center = value;

            if(parametr == "a")     a = value;
           
            if(parametr == "b")     b = value;

            if(parametr == "mat")     mat = value;

            if(parametr == "t")     t = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x_start = (x_center-a/2 + 0.5)/dx;
            int y_start = (y_center-b/2 + 0.5)/dx;
            int x_stop = (x_center+a/2 + 0.5)/dx;
            int y_stop = (y_center+b/2 + 0.5)/dx;
            int t_n = (t+0.5)/dx;
           
            if(x_start<0) x_start=0;
            if(y_start<0) y_start=0;

            if(x_stop>geometry_x_n) x_stop=geometry_x_n;
            if(x_stop>geometry_y_n) y_stop=geometry_y_n;
           
            for(size_t i = x_start; i<=x_stop; i++)
            {
                for(size_t j = y_start; j<=y_start+t_n; j++)
                {
                    geometry[i][j] = mat;
                }

                for(size_t j = y_stop-t_n; j<=y_stop; j++)
                {
                    geometry[i][j] = mat;
                }
            }

            for(size_t j = y_start+t_n; j<=y_stop-t_n; j++)
            {
                for(size_t i = x_start; i<=x_start+t_n; i++)
                {
                    geometry[i][j] = mat;
                }

                for(size_t i = x_stop-t_n; i<=x_stop; i++)
                {
                    geometry[i][j] = mat;
                }
            }
           
            return geometry;
        }
};

//--------------------------------------------------------------------------


//-------------------------------------------------------------------------- Circle

class Circle {
    public:
        double dx;
        double x_center;
        double y_center;
        double R;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<4; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x_c")   x_center = value;

            if(parametr == "y_c")   y_center = value;

            if(parametr == "R")     R = value;

            if(parametr == "D")     R = value/2.0;

            if(parametr == "mat")     mat = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x_srodek = x_center/dx+0.5;
            int y_srodek = y_center/dx+0.5;
            int R_n =  R/dx+0.5;

            int x_start = (x_center-R+0.5)/dx;
            int x_stop = (x_center+R+0.5)/dx;

            /*for(size_t i = x_start; i<=x_stop; i++)
            {
                geometry[i][y_srodek] = mat;
            }*/

            int A {0};
           
            for(size_t i = 0; i<=R_n; i++)
            {
                A = sqrt( (pow(R_n,2)-pow(i,2)) );
                for(size_t j=x_srodek-A; j<=x_srodek+A; j++ )
                {
                    geometry[j][y_srodek+i] = mat;
                    geometry[j][y_srodek-i] = mat;
                }
            }
           
            return geometry;
        }
};

//--------------------------------------------------------------------------


//-------------------------------------------------------------------------- Line

class Line {
    public:
        double dx;
        double x1;
        double y1;
        double x2;
        double y2;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<5; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x1")   x1 = value;

            if(parametr == "x2")   x2 = value;

            if(parametr == "y1")     y1 = value;

            if(parametr == "y2")    y2 = value;

            if(parametr == "mat")     mat = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x1_n, x2_n, y1_n, y2_n;

            double a;
            double b;

           

            //--------------------------------------
            if(x1<x2)
            {
                x1_n = x1/dx+0.5;
                x2_n = x2/dx+0.5;

                y1_n = y1/dx+0.5;
                y2_n = y2/dx+0.5;

                a = (y1-y2)/(x1-x2);
                b = y1_n-a*x1_n;
            }

            if(x1>x2)
            {
                x1_n = x2/dx+0.5;
                x2_n = x1/dx+0.5;

                y1_n = y2/dx+0.5;
                y2_n = y1/dx+0.5;

                a = (y1-y2)/(x1-x2);
                b = y1_n-a*x1_n;
            }

            if(x1==x2)
            {
                x1_n = x2/dx+0.5;
                x2_n = x1/dx+0.5;

                y1_n = y2/dx+0.5;
                y2_n = y1/dx+0.5;
            }

           
            //--------------------------------------

            //--------------------------------------
            if(x1_n>geometry_x_n)   x1_n = geometry_x_n;
            if(x2_n>geometry_x_n)   x2_n = geometry_x_n;

            if(x1_n<0)   x1_n = 0;
            if(x2_n<0)   x2_n = 0;
            //--------------------------------------

            //--------------------------------------
            //cout << "a = " << a << endl;
            //cout << "b = " << b << endl;
           
            //--------------------------------------

            //--------------------------------------
            int j = 0;

            if(x1_n != x2_n)
            {
                for(size_t i = x1_n; i<x2_n; i++)
                {
                    j = (a*i+b)+0.5;
                   
                    geometry[i][j] = mat;  
                }
            }
            else
            {
                int ymin = y2_n>y1_n ? y1_n : y2_n;
                int ymax = y2_n>y1_n ? y2_n : y1_n;
               
                for(size_t j = ymin; j<ymax; j++)
                {
                    geometry[x1_n][j] = mat;
                }
            }
            //--------------------------------------
           
            return geometry;
        }
};

//--------------------------------------------------------------------------


//-------------------------------------------------------------------------- Circle half

class CircleHalf {
    public:
        double dx;
        double x_center;
        double y_center;
        double R;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<4; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x_c")   x_center = value;

            if(parametr == "y_c")   y_center = value;

            if(parametr == "R")     R = value;

            if(parametr == "D")     R = value/2.0;

            if(parametr == "mat")     mat = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x_srodek = x_center/dx+0.5;
            int y_srodek = y_center/dx+0.5;
            int R_n =  R/dx+0.5;

            int x_start = (x_center-R+0.5)/dx;
            int x_stop = (x_center+R+0.5)/dx;

            /* for(size_t i = x_srodek; i<=x_stop; i++)
            {
                geometry[i][y_srodek] = mat;
            }*/

            int A {0};
           
            for(size_t i = 0; i<=R_n; i++)
            {
                A = sqrt( (pow(R_n,2)-pow(i,2)) );
                for(size_t j=x_srodek; j<=x_srodek+A; j++ )
                {
                    geometry[j][y_srodek+i] = mat;
                    geometry[j][y_srodek-i] = mat;
                }
            }
           
            return geometry;
        }
};

//--------------------------------------------------------------------------


//-------------------------------------------------------------------------- Triangle

class Triangle {
    public:
        double dx;
        double x1, y1;
        double x2, y2;
        double x3, y3;
        int mat;

        void set(string setup)
        {
            auto first_token = setup.substr(setup.find(' ')+1, setup.length());
            string order;
            double value;

            //---------------------------------------------------------------------------------
            for(size_t i{0}; i<7; i++)
            {
                order = first_token.substr(0, first_token.find(' '));
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
                value = stod( first_token.substr(0, first_token.find(' ')) );
                set_parametr(order,  value);
                first_token = first_token.substr(first_token.find(' ')+1, first_token.length());
            }
            //---------------------------------------------------------------------------------

           
        }

        void set_parametr(string parametr, double value)
        {
            if(parametr == "x1")   x1 = value;
            if(parametr == "x2")   x2 = value;
            if(parametr == "x3")   x3 = value;

            if(parametr == "y1")   y1 = value;
            if(parametr == "y2")   y2 = value;
            if(parametr == "y3")   y3 = value;
           
            if(parametr == "mat")     mat = value;
        }

        int** make(int **geometry, int geometry_x_n, int geometry_y_n)
        {
            int x1_n = x1/dx+0.5;
            int x2_n = x2/dx+0.5;
            int x3_n = x3/dx+0.5;

            int y1_n = y1/dx+0.5;
            int y2_n = y2/dx+0.5;
            int y3_n = y3/dx+0.5;
           
            Line line;
            line.dx = dx;
            line.mat = mat;

            //-----------------------------------------------------
            line.x1 = x1;
            line.y1 = y1;
            line.x2 = x2;
            line.y2 = y2;
           
            line.make(geometry, geometry_x_n, geometry_y_n);
            //-----------------------------------------------------

            //-----------------------------------------------------
            line.x1 = x1;
            line.y1 = y1;
            line.x2 = x3;
            line.y2 = y3;
           
            line.make(geometry, geometry_x_n, geometry_y_n);
            //-----------------------------------------------------

            //-----------------------------------------------------
            line.x1 = x2;
            line.y1 = y2;
            line.x2 = x3;
            line.y2 = y3;
           
            line.make(geometry, geometry_x_n, geometry_y_n);
            //-----------------------------------------------------

            //-----------------------------------------------------
            int xmin_n;

            if(x1_n<x2_n)   xmin_n = x1_n<x3_n ? x1_n : x3_n;
            else    xmin_n = x2_n<x3_n ? x2_n : x3_n;
            //-----------------------------------------------------

            //-----------------------------------------------------
            int xmax_n;

            if(x1_n>x2_n)   xmax_n = x1_n>x3_n ? x1_n : x3_n;
            else    xmax_n = x2_n>x3_n ? x2_n : x3_n;
            //-----------------------------------------------------

            //-----------------------------------------------------
            int ymin_n;

            if(y1_n<y2_n)   ymin_n = y1_n<y3_n ? y1_n : y3_n;
            else    ymin_n = y2_n<y3_n ? y2_n : y3_n;
            //-----------------------------------------------------

            //-----------------------------------------------------
            int ymax_n;

            if(y1_n>y2_n)   ymax_n = y1_n>y3_n ? y1_n : y3_n;
            else    ymax_n = y2_n>y3_n ? y2_n : y3_n;
            //-----------------------------------------------------

            //-----------------------------------------------------
            int v;

            for(int i=xmin_n; i<=xmax_n; i++)
            {
                for(int j=ymin_n; j<=ymax_n; j++)
                {
                    v = intpoint_inside_trigon(i*dx*100, j*dx*100, x1*100, y1*100, x2*100, y2*100, x3*100, y3*100);
                   
                    if( v > 0 )
                    {
                        //cout << i*dx << " " << j*dx << " " << PointInTriangle (i*dx, j*dx, x1, y1, x2, y2, x3, y3) << endl;
                        //cout << "ok" << endl;
                        geometry[i][j] = mat;
                    }
                }
            }
            //-----------------------------------------------------
                       
           
            return geometry;
        }
};

//--------------------------------------------------------------------------


//-------------------------------------------------------------------------- Geometry

class GeometryParameters {
  public:
    double dx; // skok siatki, mm
    double x;  // wymiar x siatki, mm
    double y;  // wymiar y siatki, mm
    int x_n;
    int y_n;
    //vector< vector<int> > geometry_orders;
    int **geometry;

    int read_parameters(string file_orders_name)
    {
        string order;
        ifstream file_orders(file_orders_name);
       
        //---------------------------------------------- dx
        file_orders >> order;
        if( order == "dx" )     file_orders >> dx;
        //----------------------------------------------

        //---------------------------------------------- x
        file_orders >> order;
        if( order == "x" )
        {  
            file_orders >> x;
            x_n = x/dx;
        }
        //----------------------------------------------

        //---------------------------------------------- y
        file_orders >> order;
        if( order == "y" )
        {  
            file_orders >> y;
            y_n = y/dx;
        }
        //----------------------------------------------

        geometry = array2_int(x_n, y_n);
       
        //----------------------------------------------

        file_orders >> order;
        while(!file_orders.eof( ))
        {
            //cout<<order<<endl;
            if(order == "//")   getline( file_orders, order );

            if(order == "rectangle")
            {
                Rectangle rectangle;
                rectangle.dx = dx;
                getline( file_orders, order );
                rectangle.set(order);
                rectangle.make(geometry, x_n, y_n);
            }

            if(order == "circle")
            {
                Circle circle;
                circle.dx = dx;
                getline( file_orders, order );
                circle.set(order);
                circle.make(geometry, x_n, y_n);
            }

            if(order == "rectangle_wall")
            {
                RectangleWall rectangle_wall;
                rectangle_wall.dx = dx;
                getline( file_orders, order );
                rectangle_wall.set(order);
                rectangle_wall.make(geometry, x_n, y_n);
            }

            if(order == "circle_half")
            {
                CircleHalf circle;
                circle.dx = dx;
                getline( file_orders, order );
                circle.set(order);
                circle.make(geometry, x_n, y_n);
            }

            if(order == "line")
            {
                Line line;
                line.dx = dx;
                getline( file_orders, order );
                line.set(order);
                line.make(geometry, x_n, y_n);
            }

            if(order == "triangle")
            {
                Triangle triangle;
                triangle.dx = dx;
                getline( file_orders, order );
                triangle.set(order);
                triangle.make(geometry, x_n, y_n);
            }
                       

            file_orders >> order;
        }
       
        file_orders.close();

        //cout << geometry[x_n/2][y_n/2] << endl;

        return 0;
    }

    int save_geometry(void)
    {
        ofstream file_save("Geometry.map2D", ios::out | ios::binary);

        if (!file_save)
        {
            cout << "Cannot open file!" << endl;
            return 1;
        }
   
        file_save.write( (char*)&x_n, 4 );
        file_save.write( (char*)&y_n, 4 );

        for(size_t i{0}; i<x_n; i++)
        {
            for(size_t j{0}; j<y_n; j++)
            {
                file_save.write( (char*)&geometry[i][j], 1 );
            }
        }    

        file_save.close();

        return 0;
    }
   
};

//--------------------------------------------------------------------------



int main()
{
    GeometryParameters gp;

    gp.read_parameters("siatka.op");
    gp.save_geometry();
   
   
    return 0;
}


