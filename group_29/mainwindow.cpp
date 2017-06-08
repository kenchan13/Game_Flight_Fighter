#include "mainwindow.h"
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QDialog>
#include <iostream>
using namespace std;

QSet<int> pressedKeys;

int i = 0;
int gameListStatus = 0;


void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    // 可以在這裡新增背景圖片
    QPainter painter(this);
    QPixmap bgImg;
    QPixmap start, start_selected, exit, exit_selected, score, score_selected;
    bgImg.load(":/Image/background.gif");
    painter.drawPixmap(0, 0, 760, 900, bgImg);
    cout << "paintEvent" << endl;
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    win_width = 760;
    win_height = 900;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/player1.png"));
    this->setWindowTitle("Fight Flighter");

    //create player
    cout << "create player" << endl;

    if (gameListStatus == 1) { // Game Start
        //create player
        cout << "if gameListStatus == 1" << endl;
        player=new ROLE(this);
        playerTimer = new QTimer(this);

        connect(playerTimer, SIGNAL(timeout()), this, SLOT(playerAction()));
        playerTimer->start(100);

        int i;
        for(i=0;i<24;i++) bullet[i]=new mybullet(this);
        bulletTimer = new QTimer(this);
        connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mybulletAction()));
        bulletTimer->start(2);

        //Music
        bgm =new easyMusic("musicFile/bg_music.mp3",80,1);
        jump_sound = new easyMusic("musicFile/jumpSound.mp3",100,0);
        hit_music = new easyMusic("musicFile/sfx_hit.wav",100,0);

        //主選單

        //遊戲初始模式
        gameRedy();

        //遊戲開始
        gameStart();
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
    if (gameListStatus == 0) { //Game List Mouse Action
        if (event->button() == Qt::LeftButton) {
            auto startPoint = event->pos();
            if (100 <= startPoint.rx() && startPoint.rx() <= 500) { //Start
                if (300 <= startPoint.ry() && startPoint.ry() < 400) {
                    gameListStatus = 1;
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

    player->move(0,0);
    playerTimer=new QTimer(this);
    connect(playerTimer,SIGNAL(timeout()),this,SLOT(playerAction()));
    timedata=8;
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


void MainWindow::playerAction()
{

}

void MainWindow::collisDete()
{
    //水管碰撞偵測

}
void MainWindow::gameRedy()
{
    gamemod=redy;
    createPlayer();
}
void MainWindow::gameLose()
{
    gamemod=lose;
}
void MainWindow::gameStart()
{
    gamemod=start;
    playerTimer->start(timedata);
    bgm->play();
}
