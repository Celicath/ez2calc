/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    char str[20];
    int i,j,k;
    int t,s;
    int score,combo,perfect,great,good,poor,miss,mcombo,hp,mhp;
    int min,sec,mingoal,secgoal,frame,speed=6;
    int sel=0, page=0, ms=0, diff=0;

    char text;
    int timer;

    unsigned int notes[75][6];
    unsigned int lnote[75][6];
    unsigned int key;
    unsigned short press;
    unsigned char lpress;

    while(1)
    {
        Bdisp_AllClr_DDVRAM();
        PrintXY(42,8,(unsigned char*)"ez2calc",0);
        PrintMini(88,1,(unsigned char*)"v1.00.0006",MINI_OVER);
        PrintMini(29,18,(unsigned char*)"2008.7.26-2008.9.2",MINI_OVER);
        PrintXY(35,36,(unsigned char*)"Guest Play",0);
        PrintXY(35,44,(unsigned char*)"Options",0);
        PrintXY(35,52,(unsigned char*)"Rankings",0);
        Bdisp_AreaReverseVRAM(0,36+8*sel,127,43+8*sel);
        do
        {
            GetKey(&key);
            if(key==KEY_CTRL_UP && sel>0)
            {
                sel--;
                Bdisp_AreaReverseVRAM(0,36+8*sel,127,51+8*sel);
            }
            if(key==KEY_CTRL_DOWN && sel<2)
            {
                Bdisp_AreaReverseVRAM(0,36+8*sel,127,51+8*sel);
                sel++;
            }
        }while(key!=KEY_CTRL_EXE);
        if(sel>=1) continue;
        while(1)
        {
            Bdisp_AllClr_DDVRAM();
            PrintXY(27,0,(unsigned char*)"Choose Music",0);
            if(diff==0) PrintMini(112,3,(unsigned char*)"Easy",MINI_OVER);
            else if(diff==1) PrintMini(107,3,(unsigned char*)"Norm",MINI_OVER);
            else if(diff==2) PrintMini(111,3,(unsigned char*)"Hard",MINI_OVER);

            if(page==0)
            {
                if(diff==0)
                {
                    PrintMini(0,9,(unsigned char*)"No.1  Eleventh Hour [2:15]",0);
                    PrintMini(5,15,(unsigned char*)"Lv 5  NOTE  400  BPM 150<-162",0);
                    PrintMini(0,22,(unsigned char*)"No.2  Digit 2 DJ [?:??]",0);
                    PrintMini(5,28,(unsigned char*)"Lv??  NOTE  218  BPM 150",0);
                }
                else if(diff==1)
                {
                    PrintMini(0,9,(unsigned char*)"No.1  Eleventh Hour [2:15]",0);
                    PrintMini(5,15,(unsigned char*)"Lv11  NOTE  669  BPM 150<-162",0);
                    PrintMini(0,22,(unsigned char*)"No.2  Digit 2 DJ [?:??]",0);
                    PrintMini(5,28,(unsigned char*)"Lv??  NOTE  546  BPM 150",0);
                }
                else if(diff==2)
                {
                    PrintMini(0,9,(unsigned char*)"No.1  Eleventh Hour [2:15]",0);
                    PrintMini(5,15,(unsigned char*)"Lv25  NOTE 1257  BPM 150<-162",0);
                    PrintMini(0,22,(unsigned char*)"No.2  Digit 2 DJ [?:??]",0);
                    PrintMini(5,28,(unsigned char*)"Lv??  NOTE  824  BPM 150",0);
                }
            }
            Bdisp_AreaReverseVRAM(0,13*ms+8,127,13*ms+20);
            while(1)
            {
                GetKey(&key);
                if(key==KEY_CTRL_F1)
                {
                    diff=(diff+1)%3;
                    break;
                }
                if(key==KEY_CTRL_UP && ms>0)
                {
                    ms--;
                    Bdisp_AreaReverseVRAM(0,13*ms+8,127,13*ms+33);
                }
                if(key==KEY_CTRL_DOWN && ms<3)
                {
                    Bdisp_AreaReverseVRAM(0,13*ms+8,127,13*ms+33);
                    ms++;
                }
                if(key==KEY_CTRL_LEFT && page>0)
                {
                    page--;
                    break;
                }
                if(key==KEY_CTRL_RIGHT && page<4)
                {
                    page++;
                    break;
                }
                if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && page!=key-KEY_CHAR_0)
                {
                    page=key-KEY_CHAR_0;
                    break;
                }
                if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC || key==KEY_CTRL_EXE)
                    break;
            }
            if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC || key==KEY_CTRL_EXE)
                break;
        }
        if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC) continue;

        Bdisp_AllClr_DDVRAM();
    
        for(i=0;i<75;i++)
            for(j=0;j<6;j++)
            {
                notes[i][j]=0;
                lnote[i][j]=0;
            }

        switch(12*page+3*ms+diff)
        {
            case 0:
mingoal=0; secgoal=2;
                break;
            case 1:
//2008.9.2
notes[0][0]=0x88288288; notes[1][0]=0x28828828; notes[2][0]=0x80880020; notes[3][0]=0x88288288; notes[4][0]=0x28828828; notes[5][0]=0x82202020; notes[6][0]=0x88288288; notes[7][0]=0x28828828; notes[8][0]=0x82000020; notes[10][0]=0x8000; notes[12][0]=0x82; notes[13][0]=0x8200000; notes[14][0]=0x20000000; notes[15][0]=0x80002000; notes[16][0]=0x200028; notes[17][0]=0x82002802; notes[18][0]=0x80000; notes[20][0]=0x2000020; notes[21][0]=0x80; notes[22][0]=0x8208; notes[23][0]=0x20820820; 
notes[24][0]=0x88288288; notes[25][0]=0x28828828; notes[26][0]=0x82882882; notes[27][0]=0x88288288; notes[28][0]=0x28828828; notes[29][0]=0x82882882; notes[30][0]=0x8208200; notes[33][0]=0x82082000; notes[35][0]=0x20; notes[36][0]=0x88288288; notes[37][0]=0x28828828; notes[38][0]=0x80820820; notes[39][0]=0x88288288; notes[40][0]=0x28828828; notes[41][0]=0x82000020; notes[43][0]=0x8000; notes[46][0]=0x8020000; notes[47][0]=0x820820; 
notes[2][1]=0x2000008; notes[3][1]=0x200; notes[5][1]=0x808080; notes[7][1]=0x8000000; notes[8][1]=0x20800008; notes[9][1]=0x82088200; notes[10][1]=0x8000; notes[11][1]=0x820; notes[12][1]=0x82082000; notes[13][1]=0x8008000; notes[14][1]=0x82000000; notes[15][1]=0x2080000; notes[16][1]=0x8000200; notes[17][1]=0x20008800; notes[18][1]=0x8080; notes[19][1]=0x200200; notes[20][1]=0x20000; notes[21][1]=0x20; notes[23][1]=0x2080808; 
notes[30][1]=0x8; notes[31][1]=0x20820000; notes[32][1]=0x82082; notes[33][1]=0x82; notes[34][1]=0x8200200; notes[35][1]=0x20820808; notes[40][1]=0x8000000; notes[41][1]=0x20800008; notes[42][1]=0x82088200; notes[43][1]=0x8000; notes[44][1]=0x820; notes[45][1]=0x8000200; notes[46][1]=0x20008000; notes[47][1]=0x2000000; 
notes[0][2]=0x2002002; notes[1][2]=0x200200; notes[2][2]=0x20000002; notes[3][2]=0x800; notes[5][2]=0x800; notes[7][2]=0x8000; notes[8][2]=0x82000002; notes[9][2]=0x2880; notes[11][2]=0x20820822; notes[12][2]=0x80; notes[14][2]=0x800000; notes[15][2]=0x82; notes[16][2]=0x8800; notes[17][2]=0x8020800; notes[18][2]=0x8002020; notes[19][2]=0x800; notes[20][2]=0x20082000; notes[21][2]=0x8080008; notes[22][2]=0x200000; notes[23][2]=0x20020002; 
notes[24][2]=0x2002002; notes[25][2]=0x200200; notes[26][2]=0x20000000; notes[27][2]=0x2002002; notes[28][2]=0x200200; notes[29][2]=0x20800000; notes[30][2]=0x82002000; notes[31][2]=0x820; notes[32][2]=0x82000000; notes[33][2]=0x2002000; notes[34][2]=0x8208; notes[35][2]=0x20800022; notes[36][2]=0x200; notes[38][2]=0x200000; notes[40][2]=0x8000; notes[41][2]=0x82000002; notes[42][2]=0x2880; notes[44][2]=0x20820822; notes[45][2]=0x2002002; notes[46][2]=0x2000; notes[47][2]=0x20000000; 
notes[3][3]=0x80002080; notes[5][3]=0x20800000; notes[6][3]=0x80000280; notes[7][3]=0x200000; notes[8][3]=0x800; notes[9][3]=0x80000800; notes[11][3]=0x2000000; notes[12][3]=0x80000200; notes[13][3]=0x200000; notes[14][3]=0x20000000; notes[15][3]=0x80; notes[16][3]=0x200000; notes[17][3]=0x80800; notes[18][3]=0x82000208; notes[19][3]=0x8008000; notes[20][3]=0x80800800; notes[21][3]=0x82008002; notes[22][3]=0x200; notes[23][3]=0x80002000; 
notes[24][3]=0x202020; notes[25][3]=0x20202020; notes[26][3]=0x20000000; notes[27][3]=0x202020; notes[28][3]=0x20202020; notes[29][3]=0x20000000; notes[30][3]=0x80002; notes[31][3]=0x208208; notes[32][3]=0x20A88820; notes[33][3]=0x2; notes[34][3]=0x200820; notes[35][3]=0x82000000; notes[36][3]=0x80000880; notes[38][3]=0x20802020; notes[39][3]=0x80000280; notes[40][3]=0x200000; notes[41][3]=0x800000; notes[42][3]=0x80000800; notes[44][3]=0x2000000; notes[45][3]=0x80008008; notes[46][3]=0x820800; notes[47][3]=0x80000000; 
notes[0][4]=0x80808080; notes[1][4]=0x80808080; notes[2][4]=0x80000000; notes[3][4]=0x80000; notes[4][4]=0x8008000; notes[5][4]=0x2000000; notes[6][4]=0x2000; notes[8][4]=0x800000; notes[9][4]=0x2200; notes[10][4]=0x8008208; notes[11][4]=0x20800000; notes[12][4]=0x2000; notes[13][4]=0x8208; notes[15][4]=0x80080000; notes[16][4]=0x8008008; notes[17][4]=0x200800; notes[18][4]=0x200002; notes[19][4]=0x8; notes[21][4]=0x202000; notes[22][4]=0x20000808; 
notes[24][4]=0x2020202; notes[25][4]=0x2020202; notes[26][4]=0x2000000; notes[27][4]=0x2020202; notes[28][4]=0x2020202; notes[29][4]=0x2000000; notes[30][4]=0x82082000; notes[31][4]=0x200; notes[32][4]=0x20820820; notes[33][4]=0x8208200; notes[35][4]=0x82082; notes[36][4]=0x2000; notes[37][4]=0x8008000; notes[38][4]=0x2028282; notes[39][4]=0x2000; notes[41][4]=0x800; notes[42][4]=0x2200; notes[43][4]=0x8008208; notes[44][4]=0x20800000; notes[45][4]=0x200080; notes[46][4]=0x200208; notes[47][4]=0x2; 
notes[0][5]=0x20202020; notes[1][5]=0x20202020; notes[2][5]=0x20A88820; notes[3][5]=0x2002002; notes[4][5]=0x200200; notes[5][5]=0x20020202; notes[6][5]=0x2002002; notes[7][5]=0x200200; notes[8][5]=0x20000000; notes[9][5]=0x80000082; notes[10][5]=0x8200000; notes[14][5]=0x820820; notes[15][5]=0x2002000; notes[16][5]=0x20200; notes[17][5]=0x20800800; notes[19][5]=0x20000020; notes[21][5]=0x200; notes[22][5]=0x8008020; 
notes[24][5]=0x808080; notes[25][5]=0x80808080; notes[26][5]=0x80A88820; notes[27][5]=0x808080; notes[28][5]=0x80808080; notes[29][5]=0x80000000; notes[30][5]=0x82; notes[31][5]=0x8200000; notes[33][5]=0x8; notes[34][5]=0x20820000; notes[36][5]=0x2002002; notes[37][5]=0x200200; notes[38][5]=0x20082082; notes[39][5]=0x2002002; notes[40][5]=0x200200; notes[41][5]=0x20000000; notes[42][5]=0x80000082; notes[43][5]=0x8200000; notes[45][5]=0x80000; notes[47][5]=0x82082; 
mingoal=2, secgoal=15;
                break;
            case 2:
//~2008.8.29
notes[0][0]=0x8208200; notes[1][0]=0x820; notes[2][0]=0x82000000; notes[3][0]=0x8288288; notes[4][0]=0x28828828; notes[5][0]=0x82882882; notes[6][0]=0x8288288; notes[7][0]=0x28828828; notes[8][0]=0x82082082; notes[9][0]=0x8208208; notes[10][0]=0x20820820; notes[11][0]=0x82082082; notes[12][0]=0x8208208; notes[13][0]=0x20820820; notes[14][0]=0x82082082; notes[15][0]=0x41041041; notes[16][0]=0x4100004; notes[17][0]=0x10000402; notes[18][0]=0x880000A0; notes[20][0]=0x2000000; notes[21][0]=0x880000A0; notes[23][0]=0x22800000; 
notes[24][0]=0x88288082; notes[25][0]=0x8208828; notes[26][0]=0x80820820; notes[27][0]=0x82; notes[28][0]=0x8220208; notes[29][0]=0x22000028; notes[30][0]=0x82082082; notes[31][0]=0x8208208; notes[32][0]=0x20820820; notes[33][0]=0x82082082; notes[34][0]=0x8208208; notes[35][0]=0x20820820; notes[36][0]=0x82082082; notes[37][0]=0x8208208; notes[38][0]=0x20820820; notes[39][0]=0x82082082; notes[40][0]=0x8208208; notes[41][0]=0x20820820; notes[42][0]=0x82082082; notes[43][0]=0x8208820; notes[44][0]=0x82082082; notes[45][0]=0x2200288; notes[46][0]=0x28008; notes[47][0]=0x20820820; notes[48][0]=0x80000000; 
notes[0][1]=0x8; notes[1][1]=0x20820000; notes[2][1]=0x82028; notes[3][1]=0x2002282; notes[4][1]=0x200000; notes[5][1]=0x800; notes[6][1]=0x82002002; notes[7][1]=0x8200000; notes[8][1]=0x22800028; notes[9][1]=0x2802; notes[10][1]=0x8008000; notes[11][1]=0x22020820; notes[12][1]=0x82082082; notes[13][1]=0x8208808; notes[14][1]=0xA0820820; notes[15][1]=0x41041041; notes[16][1]=0x4104101; notes[17][1]=0x4001400; notes[18][1]=0x8A0880A8; notes[19][1]=0x20; notes[20][1]=0x22802000; notes[21][1]=0x8A0880A8; notes[23][1]=0x22880020; 
notes[24][1]=0x2020; notes[25][1]=0x82080000; notes[26][1]=0x22208208; notes[27][1]=0x2220; notes[28][1]=0x82080000; notes[29][1]=0xA280082A; notes[30][1]=0xA02; notes[31][1]=0x200000; notes[32][1]=0x22; notes[33][1]=0x2002000; notes[34][1]=0x8200000; notes[35][1]=0x28820828; notes[36][1]=0x800282; notes[37][1]=0x200200; notes[38][1]=0x20000000; notes[39][1]=0x80002000; notes[40][1]=0x8208000; notes[41][1]=0xA2000028; notes[42][1]=0x80000082; notes[43][1]=0x8008000; notes[44][1]=0x228208A2; notes[45][1]=0xA28220A; notes[46][1]=0x22A008; notes[47][1]=0xA2800820; notes[48][1]=0x80000000; 
notes[2][2]=0x8A; notes[3][2]=0xA80; notes[4][2]=0x8000000; notes[5][2]=0x22800800; notes[6][2]=0x80002000; notes[8][2]=0x8280000A; notes[9][2]=0x82080A80; notes[10][2]=0x8008000; notes[11][2]=0x200008A2; notes[12][2]=0x82082280; notes[13][2]=0x8002200; notes[14][2]=0x22000800; notes[15][2]=0x4104104; notes[16][2]=0x10411040; notes[17][2]=0x41044400; notes[18][2]=0xA28A02A; notes[19][2]=0x200228; notes[20][2]=0xA2022820; notes[21][2]=0x8A28A02A; notes[22][2]=0x228; notes[23][2]=0xA08A0008; 
notes[24][2]=0x80002808; notes[25][2]=0x20828000; notes[26][2]=0x22882082; notes[27][2]=0x80002288; notes[28][2]=0x20828000; notes[29][2]=0x80800802; notes[30][2]=0x80002A80; notes[31][2]=0x8000; notes[32][2]=0x20A88822; notes[33][2]=0x80000080; notes[34][2]=0x8000000; notes[35][2]=0xA280000A; notes[36][2]=0xA80; notes[37][2]=0x8000200; notes[38][2]=0x22000008; notes[40][2]=0x208000; notes[41][2]=0xA280000A; notes[42][2]=0x82082280; notes[43][2]=0x8008208; notes[44][2]=0x22800800; notes[45][2]=0x8800A280; notes[46][2]=0x8A02800; notes[47][2]=0xA2800000; notes[48][2]=0x80000000; 
notes[2][3]=0xA88822; notes[3][3]=0x80002800; notes[4][3]=0x8018000; notes[5][3]=0x22828200; notes[6][3]=0x280; notes[7][3]=0x8008000; notes[8][3]=0x80800802; notes[9][3]=0x80000080; notes[10][3]=0x8000000; notes[11][3]=0x2800002; notes[12][3]=0x80002200; notes[13][3]=0x8000; notes[14][3]=0x82800020; notes[15][3]=0x11011011; notes[16][3]=0x410; notes[17][3]=0x110400; notes[18][3]=0x228A20A; notes[19][3]=0x28208A28; notes[20][3]=0xA00A2820; notes[21][3]=0x228A208; notes[22][3]=0x28208A28; notes[23][3]=0x800A2822; 
notes[24][3]=0x8208280; notes[25][3]=0x8000820; notes[26][3]=0x82801800; notes[27][3]=0x88208200; notes[28][3]=0x8200820; notes[29][3]=0x82082022; notes[30][3]=0x80002080; notes[31][3]=0x8000000; notes[32][3]=0x22800800; notes[33][3]=0x80002280; notes[34][3]=0x8000; notes[35][3]=0x80800802; notes[36][3]=0x80002808; notes[37][3]=0x8018000; notes[38][3]=0x22A02020; notes[39][3]=0x280; notes[40][3]=0x8000000; notes[41][3]=0x800800; notes[42][3]=0x80008A80; notes[43][3]=0x820A28A; notes[44][3]=0x28A28A28; notes[45][3]=0x8A202; notes[46][3]=0x28200A28; notes[47][3]=0x800800; notes[48][3]=0x80000000; 
notes[0][4]=0x82; notes[1][4]=0x8200000; notes[2][4]=0x820820; notes[3][4]=0x80002000; notes[4][4]=0x200; notes[5][4]=0x20202022; notes[6][4]=0x2200; notes[7][4]=0x208200; notes[8][4]=0x20000820; notes[9][4]=0x80002280; notes[10][4]=0x208208; notes[11][4]=0x20800800; notes[12][4]=0x80002208; notes[13][4]=0x20A08000; notes[14][4]=0x800020; notes[15][4]=0x41041040; notes[16][4]=0x4104114; notes[17][4]=0x50400400; notes[18][4]=0x202282; notes[19][4]=0x28208A08; notes[20][4]=0x808A0820; notes[21][4]=0x202282; notes[22][4]=0x28208A28; notes[23][4]=0x2820; 
notes[24][4]=0x20820800; notes[25][4]=0x800A082; notes[26][4]=0x8220820; notes[27][4]=0x20820880; notes[28][4]=0x820A082; notes[29][4]=0x8208888; notes[30][4]=0x2002000; notes[31][4]=0x8008200; notes[32][4]=0x22800000; notes[33][4]=0x2202; notes[34][4]=0x208200; notes[35][4]=0x20000820; notes[36][4]=0x80002000; notes[37][4]=0x800000; notes[38][4]=0x828282; notes[39][4]=0x2002202; notes[40][4]=0x200200; notes[41][4]=0x20000822; notes[42][4]=0x80002800; notes[43][4]=0x800A8A2; notes[44][4]=0x8A28A28A; notes[45][4]=0x80002000; notes[46][4]=0x28208220; notes[47][4]=0xA2800820; 
notes[0][5]=0x82082000; notes[1][5]=0x8208; notes[2][5]=0x20000000; notes[3][5]=0x82082082; notes[4][5]=0x8208208; notes[5][5]=0x20820820; notes[6][5]=0x82082082; notes[7][5]=0x8208208; notes[8][5]=0x20820820; notes[9][5]=0x82082082; notes[10][5]=0x8208208; notes[11][5]=0x20820820; notes[12][5]=0x82082082; notes[13][5]=0x8208208; notes[14][5]=0x20820820; notes[15][5]=0x41041055; notes[16][5]=0x54104104; notes[17][5]=0x10410400; notes[18][5]=0x200; notes[19][5]=0x28008800; notes[20][5]=0x880000; notes[21][5]=0x202; notes[22][5]=0x28208800; notes[23][5]=0x2800; 
notes[24][5]=0x82082082; notes[25][5]=0x8208208; notes[26][5]=0x208A2280; notes[27][5]=0x82082000; notes[28][5]=0x8208; notes[29][5]=0x208A2202; notes[30][5]=0x8208208; notes[31][5]=0x20820820; notes[32][5]=0x82082082; notes[33][5]=0x8208208; notes[34][5]=0x20820820; notes[35][5]=0x82082080; notes[36][5]=0x88288288; notes[37][5]=0x28828828; notes[38][5]=0x82082082; notes[39][5]=0x88288288; notes[40][5]=0x28828828; notes[41][5]=0x82082082; notes[42][5]=0x8208288; notes[43][5]=0x20800A28; notes[44][5]=0xA28A28A2; notes[45][5]=0x80000000; notes[46][5]=0x8808000; notes[47][5]=0xA20A28A2; notes[48][5]=0x80000000; 
lnote[18][0]=0x78000060; lnote[21][0]=0x78000060; lnote[23][0]=0x1800000; lnote[29][0]=0x1E000018; lnote[45][0]=0x1E00078; lnote[46][0]=0x18000; 
lnote[2][1]=0x18; lnote[3][1]=0x180; lnote[5][1]=0x7FF; lnote[6][1]=0x80000000; lnote[7][1]=0x7E00000; lnote[8][1]=0x1E000018; lnote[9][1]=0x1800; lnote[10][1]=0x7FF8000; lnote[11][1]=0x1E000000; lnote[13][1]=0x7E00000; lnote[14][1]=0x60000000; lnote[18][1]=0x6078018; lnote[20][1]=0x1800000; lnote[21][1]=0x6078018; lnote[23][1]=0x780000; 
lnote[26][1]=0x1E000000; lnote[27][1]=0x1E00; lnote[29][1]=0x618007E6; lnote[30][1]=0x600; lnote[32][1]=0x1E; lnote[34][1]=0x7E00000; lnote[35][1]=0x18000018; lnote[36][1]=0x180; lnote[39][1]=0x7FFFE000; lnote[40][1]=0x7E07FFF; lnote[41][1]=0x9E000018; lnote[42][1]=0x7FFFFF80; lnote[43][1]=0x7FFF; lnote[44][1]=0xE180079E; lnote[45][1]=0x6181E06; lnote[46][1]=0x1E6007; lnote[47][1]=0x9E7FF81F; lnote[48][1]=0x80000000; 
lnote[2][2]=0x6; lnote[3][2]=0x67F; lnote[4][2]=0xF8000000; lnote[5][2]=0x1E7FF800; lnote[6][2]=0x7FFFE000; lnote[8][2]=0x1800006; lnote[9][2]=0x67F; lnote[10][2]=0xF8007FFF; lnote[11][2]=0xE000079E; lnote[12][2]=0x7F; lnote[13][2]=0xF8000000; lnote[14][2]=0x1E000000; lnote[18][2]=0x1E06006; lnote[19][2]=0x18; lnote[20][2]=0x1E00181F; lnote[21][2]=0x81E06006; lnote[22][2]=0x1E0; lnote[23][2]=0x60060000; 
lnote[24][2]=0x7FFFE000; lnote[25][2]=0x7FFF; lnote[26][2]=0xE1800000; lnote[27][2]=0x7FFFE180; lnote[28][2]=0x7FFF; lnote[29][2]=0x807FF801; lnote[30][2]=0x80001980; lnote[31][2]=0x7FFF; lnote[32][2]=0xE00007E1; lnote[33][2]=0x8000007F; lnote[34][2]=0xF8000000; lnote[35][2]=0x61800006; lnote[36][2]=0x67F; lnote[37][2]=0xF8000000; lnote[38][2]=0x1E000000; lnote[40][2]=0x1F8000; lnote[41][2]=0x61800006; lnote[42][2]=0x180; lnote[43][2]=0x7FF8000; lnote[44][2]=0x1E7FF800; lnote[45][2]=0x7800607F; lnote[46][2]=0xF8601800; lnote[47][2]=0x61800000; 
lnote[2][3]=0x1; lnote[3][3]=0x80001800; lnote[4][3]=0x7FF7FFF; lnote[5][3]=0xE0000000; lnote[6][3]=0x7F; lnote[7][3]=0xF8007FFF; lnote[8][3]=0x807FF801; lnote[9][3]=0x8000007F; lnote[10][3]=0xF8000000; lnote[11][3]=0x1800001; lnote[12][3]=0x80001E00; lnote[13][3]=0x7FFF; lnote[14][3]=0x81800000; lnote[18][3]=0x181E01; lnote[19][3]=0xE01F81E0; lnote[20][3]=0x6001E000; lnote[21][3]=0x181E00; lnote[22][3]=0x181F8007; lnote[23][3]=0x8001E000; 
lnote[24][3]=0x7F; lnote[25][3]=0xF8000000; lnote[26][3]=0x7FF7FF; lnote[27][3]=0x80000000; lnote[28][3]=0x7E00000; lnote[30][3]=0x7FFFE07F; lnote[31][3]=0xF8000000; lnote[32][3]=0x1E7FF800; lnote[33][3]=0x7FFFE180; lnote[34][3]=0x7FFF; lnote[35][3]=0x807FF801; lnote[36][3]=0x80001800; lnote[37][3]=0x7FF7FFF; lnote[38][3]=0xE1800000; lnote[39][3]=0x7F; lnote[40][3]=0xF8000000; lnote[41][3]=0x7FF800; lnote[42][3]=0x7FFF867F; lnote[43][3]=0xF8006186; lnote[44][3]=0x18618618; lnote[45][3]=0x79E01; lnote[46][3]=0xE7E00618; lnote[47][3]=0x7FF800; 
lnote[3][4]=0x7FFFE000; lnote[6][4]=0x1E00; lnote[7][4]=0x1F8000; lnote[8][4]=0x7E0; lnote[9][4]=0x7FFFE180; lnote[11][4]=0x7FF800; lnote[12][4]=0x7FFFE000; lnote[13][4]=0x1F8000; lnote[14][4]=0x7FFFE0; lnote[18][4]=0x180; lnote[19][4]=0x7E00607; lnote[20][4]=0x800607E0; lnote[21][4]=0x180; lnote[22][4]=0x618; lnote[23][4]=0x7E0; 
lnote[25][4]=0x7FF8000; lnote[27][4]=0x7F; lnote[28][4]=0xF81F8000; lnote[31][4]=0x7FF8000; lnote[32][4]=0x1800000; lnote[33][4]=0x1E00; lnote[34][4]=0x1F8000; lnote[35][4]=0x7E0; lnote[36][4]=0x7FFFE000; lnote[39][4]=0x1E00; lnote[41][4]=0x7E1; lnote[42][4]=0x80001800; lnote[43][4]=0x7FF9861; lnote[44][4]=0x86186186; lnote[45][4]=0x7FFFE000; lnote[46][4]=0x181F81E0; lnote[47][4]=0x618007E0; 
lnote[19][5]=0x18007800; lnote[20][5]=0x780000; lnote[21][5]=0x1; lnote[22][5]=0xE7E07800; lnote[23][5]=0x1800; 
lnote[43][5]=0x618; lnote[44][5]=0x61861861; lnote[45][5]=0x80000000; lnote[46][5]=0x7807FFF; lnote[47][5]=0x9E000000; 
mingoal=2, secgoal=15;
            break;
        }

        score=0, combo=0, perfect=0, great=0, good=0, poor=0, miss=0, mcombo=0, hp=3000, mhp=4000;
        min=0, sec=0;

        PrintMini(2,57,(unsigned char*)"F1",MINI_OVER);
        PrintMini(12,57,(unsigned char*)"F2",MINI_OVER);
        PrintMini(22,57,(unsigned char*)"F3",MINI_OVER);
        PrintMini(32,57,(unsigned char*)"F4",MINI_OVER);
        PrintMini(42,57,(unsigned char*)"F5",MINI_OVER);
        PrintMini(52,57,(unsigned char*)"F6",MINI_OVER);

        Bdisp_DrawLineVRAM(0,0,0,63);
        Bdisp_DrawLineVRAM(0,63,127,63);
        Bdisp_DrawLineVRAM(127,63,127,0);
        Bdisp_DrawLineVRAM(127,0,0,0);
        for(i=1;i<=6;i++)
            Bdisp_DrawLineVRAM(10*i,0,10*i,63);
        Bdisp_DrawLineVRAM(0,55,60,55);
        Bdisp_DrawLineVRAM(65,0,65,63);
        Bdisp_DrawLineVRAM(65,0,65,63);
    
        PrintMini(69,2,(unsigned char*)"SCORE",MINI_OVER);
        PrintMini(69,8,(unsigned char*)"COMBO",MINI_OVER);
        PrintMini(69,14,(unsigned char*)"PERFECT",MINI_OVER);
        PrintMini(69,20,(unsigned char*)"GREAT",MINI_OVER);
        PrintMini(69,26,(unsigned char*)"GOOD",MINI_OVER);
        PrintMini(69,32,(unsigned char*)"POOR",MINI_OVER);
        PrintMini(69,38,(unsigned char*)"MISS",MINI_OVER);
        PrintMini(69,44,(unsigned char*)"MAX COMBO",MINI_OVER);
        if(secgoal<10)
            sprintf(str,"    /%d:0%d",mingoal,secgoal);
        else
            sprintf(str,"    /%d:%d",mingoal,secgoal);
        PrintMini(69,51,(unsigned char*)str,MINI_OVER);
        PrintMini(69,57,(unsigned char*)"HP",MINI_OVER);
    
        SaveDisp(SAVEDISP_PAGE1);
        s=0;

        press=lpress=text=0;
        for(frame=-47;;frame++)
        {
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_AreaReverseVRAM(61,62,64,62-61*hp/mhp);
            sprintf(str,"%8d",score);
            PrintMini(94,2,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",combo);
            PrintMini(110,8,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",perfect);
            PrintMini(110,14,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",great);
            PrintMini(110,20,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",good);
            PrintMini(110,26,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",poor);
            PrintMini(110,32,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",miss);
            PrintMini(110,38,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%4d",mcombo);
            PrintMini(110,44,(unsigned char*)str,MINI_OVER);
            if(sec<10)
                sprintf(str,"%d:0%d",min,sec);
            else
                sprintf(str,"%d:%d",min,sec);
            PrintMini(69,51,(unsigned char*)str,MINI_OVER);
            sprintf(str,"%5d/%5d",hp>0?hp:0,mhp);
            PrintMini(82,57,(unsigned char*)str,MINI_OVER);
    
            if(IsKeyDown(KEY_CHAR_LPAR) && speed>1)
            {
                if(key!=KEY_CHAR_LPAR)
                {
                    speed--;
                    key=KEY_CHAR_LPAR;
                }
            }
            else if(key==KEY_CHAR_LPAR) key=0;
            if(IsKeyDown(KEY_CHAR_RPAR) && speed<16)
            {
                if(key!=KEY_CHAR_RPAR)
                {
                    speed++;
                    key=KEY_CHAR_RPAR;
                }
            }
            else if(key==KEY_CHAR_RPAR) key=0;
            if(speed%2) sprintf(str,"x%d.5",speed/2);
            else sprintf(str,"x%d",speed/2);
            PrintMini(110,51,(unsigned char*)str,MINI_OVER);
    
            if(text && timer)
            {
                if(combo>=2)
                {
                    sprintf(str,"%d COMBO",combo);
                    PrintMini(30-2*strlen(str),15,(unsigned char*)str,MINI_OVER);
                }
                timer--;
                if(text==1)
                {
                    PrintMini(17,25,(unsigned char*)"PERFECT",MINI_OVER);
                }
                if(text==2)
                {
                    PrintMini(21,25,(unsigned char*)"GREAT",MINI_OVER);
                }
                if(text==3)
                {
                    PrintMini(23,25,(unsigned char*)"GOOD",MINI_OVER);
                }
                if(text==4)
                {
                    PrintMini(23,25,(unsigned char*)"POOR",MINI_OVER);
                }
                if(text==5)
                {
                    PrintMini(22,25,(unsigned char*)"MISS",MINI_OVER);
                }
                s+=6;
            }

            for(j=0;j<6;j++)
            {
                if(IsKeyDown(KEY_CTRL_F1+j) /**/|| (notes[frame/64][j] & (1<<(31-((frame/2)%32)))) ^ (lnote[(frame+1)/64][j] & (1<<(31-(((frame+1)/2)%32)))) && frame>=0/**/)
                {
                    Bdisp_AreaReverseVRAM(10*j+1,62,10*j+9,56);
                    s+=100;
                    if((press&(1<<j*2))==0)
                    {
                        press|=(1<<j*2);
                        press&=(-1-(2<<j*2));
                        s+=75;
                    }
                    else
                    {
                        press|=(3<<j*2);
                    }
                }
                else
                {
                    if(press&(1<<j*2))
                    {
                        press|=(2<<j*2);
                        press&=(-1-(1<<j*2));
                        s+=75;
                    }
                    else
                    {
                        press&=(-1-(3<<j*2));
                    }
                }
            }

            for(j=0;j<6;j++)
            {
                press&=-1-(3<<14);
                for(i=(frame-5)/2;;i++)
                {
                    if(i<0) continue;
                    k=((2*i-frame)*speed+4)/2-2;
                    if(notes[i/32][j] & (1<<(31-(i%32))))
                    {
                        if(k>-2)
                        {
                            Bdisp_DrawLineVRAM(10*j,53-k,10*j+9,53-k);
                            s+=3;
                        }
                        if(k>-1)
                        {
                            Bdisp_DrawLineVRAM(10*j,54-k,10*j+9,54-k);
                            s+=3;
                        }
                        if((press&(1<<15))==0 && 2*i<=frame+4)
                        {
                            if((lnote[i/32][j] & (1<<(31-(i%32))))==0 && (press&(3<<j*2))==(1<<j*2)
                                  || (lnote[i/32][j] & (1<<(31-(i%32)))) && (press&(3<<j*2))==(2<<j*2) && lpress&(1<<j))
                            {
                                if(2*i>=frame-3 && 2*i<=frame+2)
                                {
                                    if(2*i>=frame-1 && 2*i<=frame+0)
                                    {
                                        perfect++;
                                        hp+=5;
                                        score+=800+combo/4;
                                        text=1;
                                    }
                                    if(2*i==frame-2 || 2*i==frame+1)
                                    {
                                        great++;
                                        hp+=3;
                                        score+=400+combo/4;
                                        text=2;
                                    }
                                    if(2*i==frame-3 || 2*i==frame+2)
                                    {
                                        good++;
                                        hp++;
                                        score+=100+combo/4;
                                        text=3;
                                    }
                                    combo++;
                                    if(combo>mcombo) mcombo=combo;
                                }
                                else
                                {
                                    poor++;
                                    hp-=20;
                                    score+=1;
                                    combo=0;
                                    text=4;
                                }
                                notes[i/32][j] -= (1<<(31-(i%32)));
                                timer=15;
                                if(hp>mhp) hp=mhp;
                                press&=-1-(2<<j*2);
                                if(lnote[(i+1)/32][j] & (1<<(31-((i+1)%32))) || lnote[i/32][j] & (1<<(31-(i%32)))) lpress|=(1<<j);
                                if(lnote[i/32][j] & (1<<(31-(i%32)))) lpress&=-1-(1<<j);
                            }
                            else if(2*i==frame-5 && ((lnote[i/32][j] & (1<<(31-(i%32))))==0 || (press&(3<<j*2))==(3<<j*2)))
                            {
                                if(lnote[i/32][j] & (1<<(31-(i%32))))
                                    hp-=50;
                                else
                                {
                                    miss++;
                                    hp-=100;
                                }
                                combo=0;
                                text=5;
                                timer=15;
                            }
                            press|=(1<<15);
                        }
                    }
                    if(i>0 && lnote[i/32][j] & (1<<(31-(i%32))))
                    {
                        t=54-((2*(i-1)-frame)*speed+4)/2;
                        if(t<1) t=1;
                        if(t>54) t=54;
                        if(k>-1)
                        {
                            Bdisp_AreaReverseVRAM(10*j+2,t,10*j+8,k>=53?1:53-k);
                            s+=3;
                        }
                        if((press&(1<<14))==0 && (press&(3<<j*2))==(2<<j*2) && (lnote[i/32][j]&(1<<(31-(i%32)))) && (lnote[(i+1)/32][j]&(1<<(31-((i+1)%32))))==0 && (lpress&(1<<j)))
                        {
                            lpress&=-(1-(1<<j));
                            hp-=50;
                            combo=0;
                            text=5;
                            timer=15;
                        }
                        if(t==1) break;
                    }
                    if(k>51) break;
                }
            }

            Bdisp_DrawLineVRAM(0,52,60,52);
    
            Bdisp_PutDisp_DD();
            if(min==mingoal && sec==secgoal) break;
            if(hp<=-20) break;

            if(IsKeyDown(KEY_CTRL_EXIT) && IsKeyDown(KEY_CTRL_AC)) break;
            t=s/20;
            if(t>30) t=30;
            Sleep(30-t);
            s-=20*t;
            if(frame%24==0)
                sec++;
            if(sec>=60)
            {
                min++;
                sec=0;
            }
        }
        if(min==mingoal && sec==secgoal)
            PrintMini(4,14,(unsigned char*)"STAGE CLEARED",MINI_OVER);
        else if(hp<=0)
            PrintMini(7,14,(unsigned char*)"STAGE FAILED",MINI_OVER);
        PrintMini(10,36,(unsigned char*)"PRESS [EXE]",MINI_OVER);
        do{
            GetKey(&key);
        }while(key!=KEY_CTRL_EXE);
    }
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

