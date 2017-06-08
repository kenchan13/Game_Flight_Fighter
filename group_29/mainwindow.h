#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <role.h>
#include <mybullet.h>
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
    void playerAction();			//鳥的動作
    void collisDete();			//碰撞偵測
    void mybulletAction();
private:
    void gameList();             //主選單
    void createPlayer();          // 產生角色
    void gameLose();			 //遊戲結束
    void gameStart();			 //遊戲開始
    void gameRedy();             //遊戲預備
    void moving(char);
    void myshoot();

    ROLE *player;			// 建立一隻角色 - 鳥
    QTimer *playerTimer;
    double timedata;			// playerTimer interval
    enum{lose=0,start=1,redy=2};  // Enum三個參數, 代表遊戲狀態
    int gamemod;		//目前遊戲狀態, 0=lose, 1=start, 2=redy
    // 遊戲狀態預設流程： redy -> start -> lose -> redy -> start .... 不斷循環

    int win_width;      // 視窗寬度
    int win_height;     // 視窗高度

    easyMusic *bgm;
    easyMusic *jump_sound;
    easyMusic *hit_music;

    mybullet *bullet[24];
    QTimer *bulletTimer;
};

#endif // MAINWINDOW_H
