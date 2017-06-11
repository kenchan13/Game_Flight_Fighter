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
    this->setWindowIcon(QIcon(":/Image/Kappa.png"));
    this->setWindowTitle("Fight Flighter");

    //create player
    player=new ROLE(this);

    //create enemy
    enemy=new Enemy(this);

    //create my bullet
    for(int i=0;i<24;i++) bullet[i]=new mybullet(this);
    bulletTimer = new QTimer(this);
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletAction()));
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletHit()));
    bulletTimer->start(2);

    //create enemy bullet
    for(int j=0;j<8;j++)
    {
        enemy_bullet[j]=new enemybullet(this);
        enemy_bullet[j]->setVisible(false);
    }

    //Music
    bgm =new easyMusic("musicFile/bg_music.mp3",80,1);
    jump_sound = new easyMusic("musicFile/jumpSound.mp3",100,0);
    hit_music = new easyMusic("musicFile/sfx_hit.wav",100,0);
    DeathTheme = new easyMusic("musicFile/DeathTheme.mp3",100,1);
    VictoryTheme = new easyMusic("musicFile/VictoryTheme.mp3",100,0);

    time = new Number(this);
    timetimer = new QTimer(this);
    connect(timetimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(timetimer, SIGNAL(timeout()), this, SLOT(enemyShoot()));

    doom = new Doomed(this);
    doomTimer = new QTimer(this);
    connect(doomTimer, SIGNAL(timeout()), this, SLOT(enemyShoot()));


    createBackground();

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
        if(gamemod==start) moving('L');
    }
    if(event->key()==Qt::Key_Right)
    {
        if(gamemod==start) moving('R');
    }
    if(event->key()==Qt::Key_Up)
    {
        if(gamemod==start) moving('U');
    }
    if(event->key()==Qt::Key_Down)
    {
        if(gamemod==start) moving('D');
    }
    // shooting
    if(event->key()==Qt::Key_Space)
    {
        if(gamemod==start) myshoot();
    }

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 在這裡設定按下滑鼠要觸發的功能
}


void MainWindow::createPlayer(){

    player->move(320,750);
    playerTimer=new QTimer(this);
    //connect(playerTimer,SIGNAL(timeout()),this,SLOT());
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
    bullet[i]->move(player->pos().x()+37,player->pos().y()-15);
    bullet[i]->setVisible(true);
    i++;
    if(i==24) i=0;
}

void MainWindow::mybulletAction()
{
    for(int i=0;i<24;i++) if(bullet[i]->pos().y()>-100) bullet[i]->move(bullet[i]->pos().x(),bullet[i]->pos().y()-2);
}

void MainWindow::mybulletHit()
{
    for(int i=0;i<24;i++)
    {
        if(enemy->pos().x() < bullet[i]->pos().x() && enemy->pos().x()+250 > bullet[i]->pos().x())
        {
            if(enemy->pos().y() <= bullet[i]->pos().y() && enemy->pos().y()+129 >= bullet[i]->pos().y())
            {
                bullet[i]->setVisible(false);
                bullet[i]->move(bullet[i]->pos().x(),bullet[i]->pos().y()-160);
                enemy->HP--;
                if(enemy->HP==0) gameVictory();
            }
        }
    }
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
}

void MainWindow::enemybulletAction()
{
    for(int i=0;i<8;i++)
    {
        if(enemy_bullet[i]->pos().y()<1200) enemy_bullet[i]->move(enemy_bullet[i]->pos().x(),enemy_bullet[i]->pos().y()+2);
    }
}

void MainWindow::enemybulletCollision()
{
    for(int i=0;i<8;i++)
    {
        if(player->pos().x() < enemy_bullet[i]->pos().x() && player->pos().x()+91 > enemy_bullet[i]->pos().x())
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
    bgm->stop();
    timetimer->stop();
    doomTimer->stop();
    playerTimer->stop();
    bulletTimer->stop();
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
    timetimer->start(1000);
    bgm->play();
}

void MainWindow::gameVictory()
{
    gamemod=victory;
    bgm->stop();
    timetimer->stop();
    playerTimer->stop();
    enemyTimer->stop();
    enemybulletTimer->stop();
    VictoryTheme->play();
}

void MainWindow::countdown()
{
    for(int i=0;i<8;i++) enemy_bullet[i]->setVisible(true);
    if(time->TimeLimit>0) time->TimeLimit--;
    else
    {
        timetimer->stop();
        doomTimer->start(200);
    }
}

void MainWindow::createBackground()

{

    movie = new QMovie(":/Image/start.gif");
    label = new QLabel(this);

    label->setGeometry(0,0,760,900);
    label->setMovie(movie);

    movie->start();

    movieTimer = new QTimer(this);
    connect(movieTimer, SIGNAL(timeout()), this, SLOT(moviestop()));
    movieTimer->start(6000);
}

void MainWindow::moviestop()
{
    movie->stop();
    label->setVisible(false);

}
void MainWindow::fighterAction()
{
    /*int step_lenghth=55;

    if(i<=step_lenghth*4)
    {
        fighters->move(i,220);
        i=i+step_lenghth;
    }
    else
    {
        i=0;
    }*/
}
