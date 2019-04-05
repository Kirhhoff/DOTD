#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#define SCREEN_WIDTH 213 //屏幕横向字符宽度
#define SCREEN_HEIGHT 60 //屏幕纵向字符宽度
#define BATTLE_WIDTH   213 //战场横向字符宽度
#define BATTLE_HEIGHT   48 //战场纵向字符宽度
#define MAX_INPUT_RECORD   10 //单次同时接受的输入数量上限
#define BATTLE_AREA   48 //操作区与显示栏的分界线
#define IMAGE_INFO   55 //头像区与信息区的分界线
#define INFO_FUNCTION   113  //信息区与功能区的分界线
#define MAX_MONSTER_NUM   3 //最大辅导员数量 
#define MAX_HERO_NUM 4 //最大英雄数量
#define PIX_PER_WIDTH   9 //一个字符宽占的像素
#define PIX_PER_HEIGHT   18 //一个字符高占的像素
#define IMAGE_WIDTH_CHAR 30 //头像区宽度(字符计)
#define IMAGE_HEIGHT_CHAR 11 //头像区高度(字符计)
#define IMAGE_LEFT   0 //头像区左边缘的像素X坐标
#define IMAGE_TOP (PIX_PER_HEIGHT * IMAGE_WIDTH_CHAR) //头像区右边缘的像素X坐标
#define IMAGE_WIDTH_PIX (PIX_PER_WIDTH * IMAGE_WIDTH_CHAR) //头像区宽度(像素计)
#define IMAGE_HEIGHT_PIX   (PIX_PER_HEIGHT * IMAGE_HEIGHT_CHAR) //头像区高度(像素计)
#define THING_WIDTH_CHAR   10 //功能区宽度(字符计)
#define THING_HEIGHT_CHAR   5 //功能区高度(字符计)
#define THING_WIDTH_PIX   (PIX_PER_WIDTH * THING_WIDTH_CHAR) //功能区宽度(像素计)
#define THING_HEIGHT_PIX   (PIX_PER_HEIGHT * THING_HEIGHT_CHAR) //功能区高度(像素计)

#endif