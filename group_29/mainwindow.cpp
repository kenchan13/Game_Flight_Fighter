#include "mainwindow.h"
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QDialog>
QSet<int> pressedKeys;

#include <iostream>
using namespace std;

int i = 0;
int j = 0;
int gameListStatus = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    win_width = 760;
    win_height = 900;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/player1.png"));
    this->setWindowTitle("Fight Flighter");

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


    if (gameListStatus == 0) {
        QPainter painter(this);
        QPixmap bgImg;
        bgImg.load(":/Image/background.gif");
        painter.drawPixmap(0, 0, 760, 900, bgImg);

        QPixmap start, start_selected, exit, exit_selected, score, score_selected;
        start.load(":/Image/start_selected.png");
        start_selected.load(":/Image/start_selected.png");
        exit.load(":/Image/exit_selected.png");
        exit_selected.load(":/Image/exit_selected.png");
        score.load(":/Image/score_selected.png");
        score_selected.load(":/Image/score_selected.png");

        painter.drawPixmap(100, 300, 400, 100, start);
        painter.drawPixmap(100, 400, 400, 100, score);
        painter.drawPixmap(100, 500, 400, 100, exit);
    }

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
    if (gameListStatus == 0) { //Game List Mouse Action
        if (event->button() == Qt::LeftButton) {
            auto startPoint = event->pos();
            if (100 <= startPoint.rx() && startPoint.rx() <= 500) { //Start
                if (300 <= startPoint.ry() && startPoint.ry() < 400) {
                    gameListStatus = 1;
                    //this->repaint();
                    gameRedy();
                    gameStart();
//                    this->repaint();
                    cout << "start" << endl;
                } else if (400 <= startPoint.ry() && startPoint.ry() < 500) { //Score
                    cout << "score" << endl;
                    gameListStatus = 2;
                } else if (500 <= startPoint.ry() && startPoint.ry() < 600) { //Exit
                    cout << "exit" << endl;
                    gameListStatus = 3;
                }
            }
        }
    }
}


void MainWindow::createPlayer(){
    //this->repaint();
    player=new ROLE(this);
    playerTimer = new QTimer(this);
    //connect(playerTimer, SIGNAL(timeout()), this, SLOT());
//    playerTimer->start(50);

    player->move(0,0);
    playerTimer=new QTimer(this);
//    connect(playerTimer,SIGNAL(timeout()),this,SLOT());
//    timedata=8;
}

void MainWindow::createEnemy(){
    enemy=new Enemy(this);
    enemyTimer = new QTimer(this);
//    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(enemyAction()));
//    enemyTimer->start(50);
}

void MainWindow::createMyBullet(){
    int i;
    for(i=0;i<24;i++) bullet[i]=new mybullet(this);
    bulletTimer = new QTimer(this);
//    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletAction()));
//    bulletTimer->start(2);
}

void MainWindow::createEnemyBullet(){
    int j;
    for(j=0;j<24;j++) enemy_bullet[j]=new enemybullet(this);
    enemybulletTimer = new QTimer(this);
//    connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemybulletAction()));
//    enemybulletTimer->start(2);
}

void MainWindow::moving(char cmd)
{
    if(cmd=='L')
    {
        if(player->pos().x()>-300) player->move(player->pos().x()-20,player->pos().y());
    }
    if(cmd=='R')
    {
        if(player->pos().x()<320) player->move(player->pos().x()+20,player->pos().y());
    }
    if(cmd=='U')
    {
        if(player->pos().y()>-720) player->move(player->pos().x(),player->pos().y()-20);
    }
    if(cmd=='D')
    {
        if(player->pos().y()<0) player->move(player->pos().x(),player->pos().y()+20);
    }
}

void MainWindow::myshoot()
{
    bullet[i++]->move(player->pos().x()+357,player->pos().y()+740);
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
    if(enemy->pos().x() > player->pos().x()) enemy->move(enemy->pos().x()-20,enemy->pos().y());
    if(enemy->pos().x() < player->pos().x()) enemy->move(enemy->pos().x()+20,enemy->pos().y());
}

void MainWindow::enemyShoot()
{
    if(gamemod!=lose) enemy_bullet[j++]->move(enemy->pos().x()-405,enemy->pos().y()+150);
    if(j==24) j = 0;
}

void MainWindow::enemybulletAction()
{
    if(enemy_bullet[j]->pos().y() < 1000) enemy_bullet[j]->move(enemy_bullet[j]->pos().x(),enemy_bullet[j]->pos().y()+50);

    cout << enemy_bullet[j]->pos().y() << endl;
    j++;
    if(j==24) j = 0;
}


void MainWindow::gameRedy()
{
    cout << "gameRedy-----------------------" << endl;
    gamemod=redy;
    createPlayer();
    createEnemy();
    createMyBullet();
    createEnemyBullet();
}

void MainWindow::gameLose()
{
    gamemod=lose;
    timetimer->stop();
    DeathTheme->play();
}

void MainWindow::gameStart()
{
    cout << "gameStart" << cout;
    gamemod=start;
    playerTimer->start(timedata);
    //bgm->play();
    time = new Number(this);
    timetimer = new QTimer(this);
    connect(timetimer, SIGNAL(timeout()), this, SLOT(countdown()));
    timetimer->start(1000);
    connect(playerTimer, SIGNAL(timeout()), this, SLOT());
    playerTimer->start(50);
    timedata=8;
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(enemyAction()));
    enemyTimer->start(50);
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletAction()));
    bulletTimer->start(2);
    connect(enemybulletTimer, SIGNAL(timeout()), this, SLOT(enemybulletAction()));
    enemybulletTimer->start(2);
}

void MainWindow::countdown()
{
    time->TimeLimit--;
    enemyShoot();
}
