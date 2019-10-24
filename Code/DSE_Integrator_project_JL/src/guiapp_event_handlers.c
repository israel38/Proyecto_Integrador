

#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "main_thread.h"
#include "DSE_PWM_Thread.h"

/* -- Defines timer settings -- */
#define APP_TIMER_ID        (101)
#define APP_TIMER_PERIOD    (10)



extern GX_WINDOW_ROOT * p_window_root;

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);

UINT      status = TX_SUCCESS;
UINT Count_filter_rpm=0;
uint16_t Speed[10]={0},Speed_Filtred=0;
uint16_t ReceiveData[4]={0};

UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{

    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {

        case GX_EVENT_SHOW:
                gx_system_timer_start(widget, APP_TIMER_ID, APP_TIMER_PERIOD,
                                      APP_TIMER_PERIOD);
            break;
            case GX_EVENT_TIMER:
                if (APP_TIMER_ID == event_ptr->gx_event_payload.gx_event_timer_id)
                {
                    //
                    status = _txe_queue_receive (&datadisplay, ReceiveData, TX_WAIT_FOREVER);

                            char text[8];
                            gx_utility_ltoa((LONG) ReceiveData[0], text, 8);
                            // Change the prompt text
                            status = gx_prompt_text_set(&window1.window1_DUTY, text);

                            // Redraw the prompt
                            gx_system_dirty_mark((GX_WIDGET *) &window1.window1_DUTY);
                            gx_system_canvas_refresh();

                            if(Count_filter_rpm<9){
                                Speed[Count_filter_rpm]=ReceiveData[2];
                                Count_filter_rpm++;
                                }
                            else{
                                Speed[Count_filter_rpm]=ReceiveData[2];
                                Count_filter_rpm=0;
                            }
Speed_Filtred=(uint16_t)((Speed[0]+Speed[1]+Speed[2]+Speed[3]+Speed[4]+Speed[5]+Speed[6]+Speed[7]+Speed[8]+Speed[9])/10);
                            char text1[8];
                              gx_utility_ltoa((LONG) Speed_Filtred, text1, 8);
                              // Change the prompt text
                              status = gx_prompt_text_set(&window1.window1_SPEED, text1);

                              // Redraw the prompt
                              gx_system_dirty_mark((GX_WIDGET *) &window1.window1_SPEED);
                              gx_system_canvas_refresh();

                              char text2[8];
                                gx_utility_ltoa((LONG) ReceiveData[1], text2, 8);
                                // Change the prompt text
                                status = gx_prompt_text_set(&window1.window1_SETPOINT, text2);

                                // Redraw the prompt
                                gx_system_dirty_mark((GX_WIDGET *) &window1.window1_SETPOINT);
                                gx_system_canvas_refresh();

                }
                else
                {}
            break;
  /*  case GX_SIGNAL(ID_BUTTONENABLER, GX_EVENT_TOGGLE_ON):
    show_window((GX_WINDOW*)&window2, (GX_WIDGET*)widget, true);

        update_text_id(widget->gx_widget_parent, ID_WINDOWCHANGER, GX_STRING_ID_BUTTON_ENABLED);
        update_text_id(widget->gx_widget_parent, ID_INSTRUCTIONS, GX_STRING_ID_INSTRUCT_BUTTON);

       break;
    */
    default:
        gx_window_event_process(widget, event_ptr);
        break;
    }

    return result;
}

UINT window2_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type){
        case GX_EVENT_PEN_UP:
            show_window((GX_WINDOW*)&window1, (GX_WIDGET*)widget, true);
            break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET * p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET*)p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}

/*static void update_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = gx_widget_find(p_widget, id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_prompt_text_id_set(p_prompt, string_id);
    }
}

*/
