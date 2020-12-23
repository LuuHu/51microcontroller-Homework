

#include <reg52.h>
#include <STDIO.H>
#include <STRING.H>
#include <cha.h>

#define uchar unsigned char
#define uint unsigned int
#define OneLine 32 //液晶每行的宽�?

uchar UART_buff, table[3];
uint cot = 0, Send_ed = 0, i, ix, io, pp, t;

#define LCD_Outcode P0
sbit LCD_CD = P1 ^ 7;
sbit LCD_RD = P1 ^ 6;
sbit LCD_WR = P1 ^ 5;
sbit LCD_RST = P3 ^ 4;
sbit red = P3 ^ 2;
sbit blue = P3 ^ 3;

void delay(ms)
{
    unsigned int q, w;
    for (q = 0; q < ms; q++)
        for (w = 0; w < 255; w++)
            ;
}

void WriteData(uchar dat)
{
    LCD_CD = 0;
    LCD_WR = 0;
    LCD_Outcode = dat;
    LCD_WR = 1;
}

void WriteCommand(uchar cmd)
{
    LCD_CD = 1;
    LCD_WR = 0;
    LCD_Outcode = cmd;
    LCD_WR = 1;
}

void WriteDC(uchar dat, uchar cmd)
{
    WriteData(dat);
    WriteCommand(cmd);
}

void WriteDDC(uchar data1, uchar data2, uchar cmd)
{
    WriteData(data1);
    WriteData(data2);
    WriteCommand(cmd);
}

void LCD_Init(void)
{
    uchar data1, data2, cmd;
    LCD_WR = 1;
    LCD_RD = 1;
    data1 = 0x00;
    data2 = 0x00;
    cmd = 0x40;
    WriteDDC(data1, data2, cmd);
    data1 = 0x20;
    data2 = 0x00;
    cmd = 0x41;
    WriteDDC(data1, data2, cmd);
    data1 = 0x08;
    data2 = 0x00;
    cmd = 0x42;
    WriteDDC(data1, data2, cmd);
    data1 = 0x20;
    data2 = 0x00;
    cmd = 0x43;
    WriteDDC(data1, data2, cmd);
    cmd = 0xa2;
    WriteCommand(cmd);
    cmd = 0x88;
    WriteCommand(cmd);
    cmd = 0x9e;
    WriteCommand(cmd);
}

void Write_Photo(row, rol, width, deep, idx)
{
    uint address, Photolength;
    uchar j, data1, data2, cmd;
    Photolength = width * deep;
    address = row * 256 + rol;
    data1 = address;
    data2 = address >> 8;
    cmd = 0x24;
    WriteDDC(data1, data2, cmd);
    WriteCommand(0xb0);
    for (i = 0; i < Photolength; i++)
    {
        WriteData(Photo[idx * 4][i]);
        j++;
        if (j == width)
        {
            WriteCommand(0xb2);
            address = address + 32;
            data1 = address;
            data2 = address >> 8;
            cmd = 0x24;
            WriteDDC(data1, data2, cmd);
            j = 0;
            WriteCommand(0xb0);
        }
    }
    WriteCommand(0xb2);
}
void action(iod)
{
    LCD_RST = 1;
    delay(20);
    LCD_RST = 0;
    delay(20);
    LCD_Init();
    t = 0;
    for (io = 0; io < iod; io++)
    {
        t += num_cha[io];
    }
    for (pp = 0; pp < num_cha[iod-1]; pp++)
    {
        Clear(3, 8 + 4 * pp, 4, 32);
        delay(1);
    }
    for (pp = 0; pp < num_cha[iod]; pp++)
    {
        Write_Photo(3, 8 + 4 * pp, 4, 32, pp + t);
        delay(1);
    }
    if (iod == 0)
    {
        red = 1;
        blue = 1;
    }
    else if (iod == 1)
    {
        red = 1;
        blue = 0;
    }
    else if (iod == 2)
    {
        red = 0;
        blue = 1;
    }
    else if (iod <= 16)
    {
        red = 0;
        blue = 0;
        P2 = iod - 3 + 240;
    }
    else
    {
        red = 0;
        blue = 0;
        P2 = 15 + (iod - 17) * 15;
    }
}
void main(void)
{
    SCON = 0x50;
    TMOD = 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    ES = 1;
    EA = 1;
    LCD_RST = 1;
    red = 0;
    blue = 0;
    while (1)
    {
        if (Send_ed == 1)
        {
            Send_ed = 0;
            if (strstr(table, "000") != NULL)
            {
                ix = 0;
                action(ix);
            }
            else if (strstr(table, "001") != NULL)
            {
                ix = 1;
                action(ix);
            }
            else if (strstr(table, "002") != NULL)
            {
                ix = 2;
                action(ix);
            }
            else if (strstr(table, "L01") != NULL)
            {
                ix = 3;
                action(ix);
            }
            else if (strstr(table, "L02") != NULL)
            {
                ix = 4;
                action(ix);
            }
            else if (strstr(table, "L03") != NULL)
            {
                ix = 5;
                action(ix);
            }
            else if (strstr(table, "L04") != NULL)
            {
                ix = 6;
                action(ix);
            }
            else if (strstr(table, "L05") != NULL)
            {
                ix = 7;
                action(ix);
            }
            else if (strstr(table, "L06") != NULL)
            {
                ix = 8;
                action(ix);
            }
            else if (strstr(table, "L07") != NULL)
            {
                ix = 9;
                action(ix);
            }
            else if (strstr(table, "L08") != NULL)
            {
                ix = 10;
                action(ix);
            }
            else if (strstr(table, "L09") != NULL)
            {
                ix = 11;
                action(ix);
            }
            else if (strstr(table, "L10") != NULL)
            {
                ix = 12;
                action(ix);
            }
            else if (strstr(table, "L11") != NULL)
            {
                ix = 13;
                action(ix);
            }
            else if (strstr(table, "L12") != NULL)
            {
                ix = 14;
                action(ix);
            }
            else if (strstr(table, "L13") != NULL)
            {
                ix = 15;
                action(ix);
            }
            else if (strstr(table, "L14") != NULL)
            {
                ix = 16;
                action(ix);
            }
            else if (strstr(table, "S01") == NULL)
            {
                ix = 17;
                action(ix);
            }
            else if (strstr(table, "S02") != NULL)
            {
                ix = 18;
                action(ix);
            }
            else if (strstr(table, "S03") != NULL)
            {
                ix = 19;
                action(ix);
            }
            else if (strstr(table, "S04") != NULL)
            {
                ix = 20;
                action(ix);
            }
            else if (strstr(table, "S05") != NULL)
            {
                ix = 21;
                action(ix);
            }
            else if (strstr(table, "S06") != NULL)
            {
                ix = 22;
                action(ix);
            }
            else if (strstr(table, "S07") != NULL)
            {
                ix = 23;
                action(ix);
            }
            else if (strstr(table, "S08") != NULL)
            {
                ix = 24;
                action(ix);
            }
            else if (strstr(table, "S09") != NULL)
            {
                ix = 25;
                action(ix);
            }
            else if (strstr(table, "S10") != NULL)
            {
                ix = 26;
                action(ix);
            }
            else if (strstr(table, "S11") != NULL)
            {
                ix = 27;
                action(ix);
            }
            else if (strstr(table, "S12") != NULL)
            {
                ix = 28;
                action(ix);
            }
            else if (strstr(table, "S13") != NULL)
            {
                ix = 29;
                action(ix);
            }
            else if (strstr(table, "S14") != NULL)
            {
                ix = 30;
                action(ix);
            }
        }
        delay(2);
    }
}

void ser(void) interrupt 4
{
    RI = 0;
    table[cot] = SBUF;
    cot++;
    if (cot == 3)
    {
        cot = 0;
        Send_ed = 1;
    }
}

