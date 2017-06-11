#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <role.h>
#include <mybullet.h>
#include <enemy.h>
#include <enemybullet.h>
#include <number.h>
#include <doomed.h>
#include "easymusic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);    //繪製背景圖
    void keyPressEvent(QKeyEvent *event);	//鍵盤事件
    void mousePressEvent(QMouseEvent *event);	//滑鼠點下事件

private slots:
    void enemyAction();
    void enemyShoot();
    void enemybulletAction();
    void enemybulletCollision();
    void mybulletAction();
    void mybulletHit();
    void countdown();
    void bgmoviestop();
private:

    void createPlayer();          // 產生角色
    void createEnemy();
    void createEnemyBullet();
    void gameLose();			 //遊戲結束
    void gameStart();			 //遊戲開始
    void gameRedy();             //遊戲預備
    void gameVictory();
    void moving(char);
    void myshoot();

    void createBackground();
    void fighterAction();
    void createLoseMovie();

    ROLE *player;			// 建立一隻角色 - 鳥
    QTimer *playerTimer;
    double timedata;			// playerTimer interval
    enum{lose=0,start=1,redy=2,victory=3};  // Enum三個參數, 代表遊戲狀態
    int gamemod;		//目前遊戲狀態, 0=lose, 1=start, 2=redy
    // 遊戲狀態預設流程： redy -> start -> lose -> redy -> start .... 不斷循環

    int win_width;      // 視窗寬度
    int win_height;     // 視窗高度

    easyMusic *bgm;
    easyMusic *jump_sound;
    easyMusic *hit_music;
    easyMusic *DeathTheme;
    easyMusic *VictoryTheme;

    mybullet *bullet[24];
    QTimer *bulletTimer;

    Enemy *enemy;
    QTimer *enemyTimer;

    enemybullet *enemy_bullet[8];
    QTimer *enemybulletTimer;

    Number *time;
    QTimer *timetimer;

    Doomed *doom;
    QTimer *doomTimer;

    QMovie* bgmovie;
    QTimer *bgmovieTimer;
    QLabel* bglabel;

    QMovie* losemovie;
    QLabel* loselabel;

};

#endif // MAINWINDOW_H
