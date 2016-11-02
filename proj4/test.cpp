#include <GL/glut.h>

#include <iostream>
#include <string>
#include <list>
/* MySQL Connector/C++ specific headers */
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>

#include "encounter.h"

#define MINPID 1
#define MAXPID 30

using namespace std;
using namespace sql;

void init()
{
  // set the screen background color to RGB
  glClearColor(128.0 / 255, 128.0 / 255, 128.0 / 255, 0.0);

  // enable the depth test (important; disabled by default)
  glEnable(GL_DEPTH_TEST);
}

void draw_box(float color_r, float color_g, float color_b, int row, int col)
{
    float x1 = 0.0f;   float y1 = 0.0f;
    float x2 = 0.025f; float y2 = 0.0f;
    float x3 = 0.025f; float y3 = 0.05f;
    float x4 = 0.0f;   float y4 = 0.05f;

    float tran_x = -0.90f + (0.03 * col);
    float tran_y = 0.90f + (-0.06 * row); 

    glPushMatrix();
    glTranslatef(tran_x, tran_y, 0.0f);
    glBegin(GL_POLYGON);
        glColor3f(color_r, color_g, color_b);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
        glVertex3f(x3, y3, 0.0);
        glVertex3f(x4, y4, 0.0);
    glEnd();
    /*
    glBegin(GL_POLYGON);
        glVertex3f(-0.1, 0.1, 0.0);
        glVertex3f(-0.1, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.1, 0.0);
    glEnd();
    */
    //glTranslatef(-10.0, 30.0, 0.0);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //load data 
    sql::Driver *driver;
    sql::Connection *con;
    Statement *stmt;
    ResultSet *res;

    list<Encounter> enc_list;

    driver = get_driver_instance();
    con = driver->connect("tcp://192.168.1.6:3306","root","R@ng00n");
    con->setSchema("cohort");
    stmt = con->createStatement();

    for (int pid = MINPID; pid <= MAXPID; pid++)
    {
        string query = "SELECT pid AS pid, symptons.des AS sympton, days AS days ";
        query.append("FROM encounter LEFT JOIN symptons ON encounter.sym=symptons.code ");
        query.append("WHERE encounter.pid = ");
        query.append(std::to_string(pid));

        //cout << "Query: " << query << endl;
        res = stmt->executeQuery (query);
        
        // empty list
        while (!enc_list.empty())
        {
          enc_list.pop_front();
        }

        int zero_day = 0;
        int count = 0;
        while (res->next())
        {
            count++;
            //cout << res->getInt("pid") << " : ";
            //cout << res->getString("sympton") << " : ";
            //cout << res->getInt("days") << endl;
            Encounter enc(res->getInt("pid"), res->getString("sympton"), res->getInt("days"));

            if (res->getInt("days") == 0)
            {
                zero_day = count;
            }

            enc_list.push_back(enc);
        }

        // cout << "Patient ID : " << pid << ", zero-day @ " << zero_day << "\n";
        if (zero_day > 31)
        {
            for (int cnt = 0; cnt < (zero_day - 31); cnt++)
            {
                enc_list.pop_front();
            }
        } 
        else if (zero_day < 31)
        {
            for (int cnt = 0; cnt < (31 - zero_day); cnt++)
            {
                Encounter enc(pid, "NONE", -10000);
                enc_list.push_front(enc);
            }
        }

        int list_size = enc_list.size();
        if (list_size > 61)
        {
            for (int cnt = 0; cnt < (list_size - 61); cnt++)
            {
                enc_list.pop_back();
            }
        }
        else if (list_size < 61)
        {
            for (int cnt = 0; cnt < (61 - list_size); cnt++)
            {
                Encounter enc(pid, "NONE", 10000);
                enc_list.push_back(enc);
            }
        } 

        int col = 0;
        for (list<Encounter>::iterator it = enc_list.begin(); it != enc_list.end(); it++)
        {
            Encounter enc = *it;
            cout << enc.get_pid() << " : " << enc.get_symp() << " : " << enc.get_days() << "\n";
            
            // compute color here
            float   red = 128.0 / 255;
            float green = 128.0 / 255;
            float blue  = 128.0 / 255;

            if (enc.get_symp().compare("NONskull") == 0)
            {
                red   = 255.0f / 255;
                green = 255.0f / 255;
                blue  = 136.0f / 255;
            }

            if (enc.get_symp().compare("Alzheimer") == 0)
            {
                red = 0.25f;
                green = 0.0f;
                blue  = 0.0f;
            }


            if (enc.get_symp().compare("Anxiety") == 0)
            {
                red = 0.5f;
                green = 0.0f;
                blue  = 0.0f;
            }

            if (enc.get_symp().compare("Audiology") == 0)
            {
                red = 0.75f;
                green = 0.0f;
                blue  = 0.0f;
            }

            int row = pid - 1;
            draw_box(red, green, blue, row, col);
            col++;
        }

    }
/*
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 61; j++)
        {
            if (j == 31)
            {
                draw_box(1.0f, 0.0f, 0.0f, i, j);
            }
            else
            {
                draw_box(0.6f, 0.4f, 0.0f, i, j);
            }
        }
    }
 */   
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1350, 690);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Test");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
