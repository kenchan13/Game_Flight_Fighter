#include "mainwindow.h"
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QDialog>
#include <iostream>
using namespace std;

int i = 0;
int j = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    win_width = 760;
    win_height = 900;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/player1.png"));
    this->setWindowTitle("Fight Flighter");


    //create player
    player=new ROLE(this);
    /*playerTimer = new QTimer(this);
    connect(playerTimer, SIGNAL(timeout()), this, SLOT());
    playerTimer->start(50);*/

    //create enemy
    enemy=new Enemy(this);
    /*enemyTimer = new QTimer(this);
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(enemyAction()));
    enemyTimer->start(50);*/

    //create my bullet
    for(int i=0;i<24;i++) bullet[i]=new mybullet(this);
    bulletTimer = new QTimer(this);
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletAction()));
    bulletTimer->start(2);

    //create enemy bullet
    for(int j=0;j<8;j++) enemy_bullet[j]=new enemybullet(this);
    /*enemybulletTimer = new QTimer(this);
    connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemybulletAction()));
    enemybulletTimer->start(2);*/

    //Music
    bgm =new easyMusic("musicFile/bg_music.mp3",80,1);
    jump_sound = new easyMusic("musicFile/jumpSound.mp3",100,0);
    hit_music = new easyMusic("musicFile/sfx_hit.wav",100,0);
    DeathTheme = new easyMusic("musicFile/DeathTheme.mp3",100,1);
    VictoryTheme = new easyMusic("musicFile/VictoryTheme.mp3",100,1);

    //遊戲初始模式
    gameRedy();



    //遊戲開始
    gameStart();
}

void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    // 可以在這裡新增背景圖片

    QPainter painter(this);
    QPixmap bgImg;
    bgImg.load(":/Image/background.gif");

    painter.drawPixmap(0, 0, 760, 900, bgImg);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 在這裡設定按下鍵盤要觸發的功能
    if(event->key()==Qt::Key_Left)
    {
        if(gamemod!=lose) moving('L');
    }
    if(event->key()==Qt::Key_Right)
    {
        if(gamemod!=lose) moving('R');
    }
    if(event->key()==Qt::Key_Up)
    {
        if(gamemod!=lose) moving('U');
    }
    if(event->key()==Qt::Key_Down)
    {
        if(gamemod!=lose) moving('D');
    }
    // shooting
    if(event->key()==Qt::Key_Space)
    {
        if(gamemod!=lose) myshoot();
    }

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 在這裡設定按下滑鼠要觸發的功能
}


void MainWindow::createPlayer(){

    player->move(320,750);
    playerTimer=new QTimer(this);
    connect(playerTimer,SIGNAL(timeout()),this,SLOT());
    timedata=8;
}

void MainWindow::createEnemy()
{
    enemy->move(240,25);
    enemyTimer = new QTimer(this);
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(enemyAction()));
}

void MainWindow::createEnemyBullet()
{
    enemybulletTimer = new QTimer(this);
    //connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemyShoot()));
    connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemybulletAction()));
    connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemybulletCollision()));
}

void MainWindow::moving(char cmd)
{
    if(cmd=='L')
    {
        if(player->pos().x()>20) player->move(player->pos().x()-20,player->pos().y());
    }
    if(cmd=='R')
    {
        if(player->pos().x()<640) player->move(player->pos().x()+20,player->pos().y());
    }
    if(cmd=='U')
    {
        if(player->pos().y()>20) player->move(player->pos().x(),player->pos().y()-20);
    }
    if(cmd=='D')
    {
        if(player->pos().y()<740) player->move(player->pos().x(),player->pos().y()+20);
    }
}

void MainWindow::myshoot()
{
    bullet[i++]->move(player->pos().x()+37,player->pos().y()-15);
    if(i==24) i=0;
}

void MainWindow::mybulletAction()
{
    bullet[i]->move(bullet[i]->pos().x(),bullet[i]->pos().y()-40);
    i++;
    if(i==24) i = 0;
}


void MainWindow::enemyAction()
{
    if(enemy->pos().x() > player->pos().x()-80) enemy->move(enemy->pos().x()-15,enemy->pos().y());
    if(enemy->pos().x() <= player->pos().x()-80) enemy->move(enemy->pos().x()+15,enemy->pos().y());
}

void MainWindow::enemyShoot()
{
    enemy_bullet[j++]->move(enemy->pos().x()+115,enemy->pos().y()+125);
    if(j==8) j = 0;
    /*for(int i=0;i<24;i++)
    {
        enemy_bullet[i]->move(enemy->pos().x(),enemy->pos().y());
    }*/
}

void MainWindow::enemybulletAction()
{
    for(int i=0;i<8;i++)
    {
        if(enemy_bullet[i]->pos().y()<1200) enemy_bullet[i]->move(enemy_bullet[i]->pos().x(),enemy_bullet[i]->pos().y()+2);
    }

    //enemy_bullet[j]->move(enemy_bullet[j]->pos().x(),enemy_bullet[j]->pos().y()+50);

    /*collideDetection
    if(player->pos().x() <= enemy_bullet[j]->pos().x() && player->pos().x()+91 >= enemy_bullet[j]->pos().x())
    {
        if(player->pos().y()+925 <= enemy_bullet[j]->pos().y() && player->pos().y()+1050 >= enemy_bullet[j]->pos().y())
        {
            gameLose();
        }
    }
    j++;
    if(j==8) j = 0;*/
}

void MainWindow::enemybulletCollision()
{
    for(int i=0;i<8;i++)
    {
        cout << player->pos().x() << " " << player->pos().y() << " " << enemy_bullet[i]->pos().x()<< " " << enemy_bullet[i]->pos().y() << endl;
        if(player->pos().x() <= enemy_bullet[i]->pos().x() && player->pos().x()+91 >= enemy_bullet[i]->pos().x())
        {
            if(player->pos().y() <= enemy_bullet[i]->pos().y() && player->pos().y()+125 >= enemy_bullet[i]->pos().y())
            {
                gameLose();
            }
        }
    }
}


void MainWindow::gameRedy()
{
    gamemod=redy;
    createPlayer();
    createEnemy();
    createEnemyBullet();
}
void MainWindow::gameLose()
{
    gamemod=lose;
    timetimer->stop();
    playerTimer->stop();
    enemyTimer->stop();
    enemybulletTimer->stop();
    DeathTheme->play();
}
void MainWindow::gameStart()
{
    gamemod=start;
    playerTimer->start(timedata);
    enemyTimer->start(50);
    enemybulletTimer->start(2);
    //bgm->play();
    time = new Number(this);
    timetimer = new QTimer(this);
    connect(timetimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(timetimer, SIGNAL(timeout()), this, SLOT(enemyShoot()));
    timetimer->start(1000);
}

void MainWindow::countdown()
{
    time->TimeLimit--;
    //enemyShoot();
}
