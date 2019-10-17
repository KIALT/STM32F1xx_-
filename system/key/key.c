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

/*   include **************************************/

/*   Define *************************************/

/*   variable***********************************/
#include "stdio.h"
#include "key.h"
#define EVENT_CB(ev)   if(handle->cb[ev])handle->cb[ev]((Button*)handle)
      

/* 按键句柄链头*/
static struct Button* head_handle = NULL;

/**
  * @brief  初始化结构句柄.
  * @param  handle       : 按键句柄.
  * @param  pin_level    : 读取按键电平
  * @param  active_level : 触发电平
  * @retval None
  */
void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level)
{
    memset(handle, 0, sizeof(struct Button));              
    handle->event = (uint8_t)NONE_PRESS;                
    handle->hal_button_Level = pin_level;               
    handle->button_level = handle->hal_button_Level(); 
    handle->active_level = active_level;
}

/**
  * @brief  添加按键事件回调函数.
  * @param  handle: 按键句柄结构.
  * @param  event : 触发事件类型.
  * @param  cb    : 回调函数.
  * @retval None
  */
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb)
{
    handle->cb[event] = cb;
}

/**
  * @brief  检测按键事件的发生.
  * @param  handle: 按键的句柄.
  * @retval 返回按键事件.
  */
PressEvent get_button_event(struct Button* handle)
{
    return (PressEvent)(handle->event);
}

/**
  * @brief  按键驱动函数, 设备状态机.
  * @param  handle: 按键句柄结构.
  * @retval None
  */
void button_handler(struct Button* handle)
{
    uint8_t read_gpio_level = handle->hal_button_Level();
  
    if((handle->state) > 0) handle->ticks++;              /* 计数开始工作*/

    /*------------按键去抖---------------*/
    if(read_gpio_level != handle->button_level) {          /*两次电平不等*/
                                                          /*连续检测3次电平变化*/
        if(++(handle->debounce_cnt) >= DEBOUNCE_TICKS) {  /*结束去抖*/ 
            handle->button_level = read_gpio_level;       /*读取按键电平*/
            handle->debounce_cnt = 0;                     /*清空抖动比较次数*/
        }
    } else {                                              /*无按键抖动*/

    }

    /*-----------------State machine-------------------*/
    switch (handle->state) {
    case 0:
        if(handle->button_level == handle->active_level) {   /*按键事件触发*/
            handle->event = (uint8_t)PRESS_DOWN;             /*标记按键按下*/                                 
            EVENT_CB(PRESS_DOWN);                            /*响应按键*/   
            handle->ticks = 0;
            handle->repeat = 1;   
            handle->state = 1;                               /* 标记状态1*/   
        } else {
            handle->event = (uint8_t)NONE_PRESS;
        }
        break;

    case 1:
        if(handle->button_level != handle->active_level) { /* 按键弹起*/
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);                             /*响应按键*/
            handle->ticks = 0;
            handle->state = 2; 

        } else if(handle->ticks > LONG_TICKS) {            /* 长按*/
            handle->event = (uint8_t)LONG_RRESS_START;
            EVENT_CB(LONG_RRESS_START);
            handle->state = 5;
        }
        break;

    case 2:
        if(handle->button_level == handle->active_level) {   /*连续按下*/
            handle->event = (uint8_t)PRESS_DOWN;
            EVENT_CB(PRESS_DOWN);                           
            handle->repeat++;
            if(handle->repeat == 2) {                       /* 双击*/
                EVENT_CB(DOUBLE_CLICK); 
            } 
            EVENT_CB(PRESS_REPEAT);                        /* 多击*/
            handle->ticks = 0;
            handle->state = 3;
        } else if(handle->ticks > SHORT_TICKS) {           /*单击*/
            if(handle->repeat == 1) {
                handle->event = (uint8_t)SINGLE_CLICK;
                EVENT_CB(SINGLE_CLICK);
            } else if(handle->repeat == 2) {              /*双击*/
                handle->event = (uint8_t)DOUBLE_CLICK;
            }
            handle->state = 0;
        }
        break;

    case 3:
        if(handle->button_level != handle->active_level) {  /*无按键按下*/
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);                             /*响应 按键*/
            if(handle->ticks < SHORT_TICKS) {    
                handle->ticks = 0;
                handle->state = 2;                        
            } else {
                handle->state = 0;
            }
        }
        break;

    case 5:
        if(handle->button_level == handle->active_level) {  
            
            handle->event = (uint8_t)LONG_PRESS_HOLD;
            EVENT_CB(LONG_PRESS_HOLD);

        } else { 
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);
            handle->state = 0; 
        }
        break;
    }
}

/**
  * @brief  运行按键, 添加按键句柄到运行链表.
  * @param  handle:  目标按键的句柄.
  * @retval 0 : 添加成功. 
  *         -1: 已经添加.
  */
int button_start(struct Button* handle)
{
    struct Button* target = head_handle;
    while(target) {
        if(target == handle) return -1;    //已经添加
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}
/**
  * @brief  停止按键运行, 弹出检测链表.
  * @param  handle: 目标按键句柄.
  * @retval None
  */
void button_stop(struct Button* handle)
{
    struct Button** curr;
    for(curr = &head_handle; *curr; ) {
        struct Button* entry = *curr;
        if (entry == handle) {
            *curr = entry->next;
//            free(entry);
        } else
            curr = &entry->next;
    }
}

/**
  * @brief  按键检测，时间由调用此函数的时间决定.
  * @param  None.
  * @retval None
  */
void button_ticks()
{
    struct Button* target;
    for(target=head_handle; target; target=target->next) {
        button_handler(target);
    }
}

