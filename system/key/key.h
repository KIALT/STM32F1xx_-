/**
  *************************************************************************************************
  * @file     key.h
  * @author   罗涛
  * @version  V1.0.0
  * @date     2019.5.31
  * @brief    按键程序
  **************************************************************************************************
  * @attention
  *                
  *  				None
  * 
  **************************************************************************************************
  */
/* Define to prevent recursive inclusion ----------------------------------------------------------*/

#ifndef _KEY_H
#define _KEY_H

#include <stdint.h>
/* Define **********************************************************/
/* pulic*********************************************************/
 
#define TICKS_INTERVAL    5    //ms            /* 按键扫描时间，用户还有可以自定义调用button_tick()的周期也可以*/
#define DEBOUNCE_TICKS    6    //MAX 8         /* 抖动检测次数*/
#define SHORT_TICKS       (300  /TICKS_INTERVAL)  /* 短按 时间*/
#define LONG_TICKS        (1000 /TICKS_INTERVAL) /* 长按 时间*/ 


typedef void (*BtnCallback)(void*);

typedef enum {
    PRESS_DOWN = 0,              //按键按下,每次按下都触发
    PRESS_UP,                    //按键弹起,每次松开都触发
    PRESS_REPEAT,                //重复按下触发，变量重复计数连击次数
    SINGLE_CLICK,                //单击
    DOUBLE_CLICK,                //双击
    LONG_RRESS_START,            //长按 到达阈值事件触发
    LONG_PRESS_HOLD,             //长按一直触发
    number_of_event,             //
    NONE_PRESS                   //无按键按下 
}PressEvent;

typedef struct Button {
    uint16_t ticks;
    uint8_t  repeat : 4;
    uint8_t  event : 4;
    uint8_t  state : 3;
    uint8_t  debounce_cnt : 3; 
    uint8_t  active_level : 1;
    uint8_t  button_level : 1;
    uint8_t  (*hal_button_Level)(void);
    BtnCallback  cb[number_of_event];
    struct Button* next;
}Button;

#ifdef __cplusplus  
extern "C" {  
#endif  
void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);
#ifdef __cplusplus
} 
#endif

#endif
