/*
 * =====================================================================================
 *
 *       Filename:  filesystem.c
 *
 *    Description:  file system
 *
 *        Version:  1.0
 *        Created:  2019年01月22日 15时50分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhijinzeng@allwinnertech.com
 *   Organization:  AW-PDC-PSW
 *
 * =====================================================================================
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jerryscript.h"
#include "jerryscript-ext/debugger.h"
#include "jerryscript-ext/handler.h"
#include "jerryscript-port.h"
#include "jerryscript-port-default.h"

extern int js_static_fs_init(void);
extern int js_fs_init(void);
#define DECLARE_HANDLER(NAME)       \
     static jerry_value_t NAME ## _handler (const jerry_value_t func_value, const jerry_value_t this_value, const jerry_value_t args[], const jerry_length_t args_cnt __attribute__((unused)))
#define JS_HANDLER_NAME(NAME)   NAME ## _handler


extern void set_function_property(jerry_value_t global_object, const char *func_name,jerry_value_t (* handler)(const jerry_value_t func_value, const jerry_value_t this_value, const jerry_value_t args[], const jerry_length_t args_cnt));
void set_function_property(jerry_value_t global_object, const char *func_name,jerry_value_t (* handler)(const jerry_value_t func_value, const jerry_value_t this_value, const jerry_value_t args[], const jerry_length_t args_cnt))
{
    jerry_value_t func_obj = jerry_create_external_function(handler);
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) func_name);
    jerry_set_property(global_object, prop_name, func_obj);
    jerry_release_value(prop_name);
    jerry_release_value(func_obj);
}
DECLARE_HANDLER(test2)
{
    printf("%s line %d.\n",__func__, __LINE__);
   jerry_value_t a;
   a = func_value; 
   a = this_value;
   a = args[0]; 
   return a;
}
DECLARE_HANDLER(test0)
{
   jerry_value_t a;
   while(1)
    printf("%s line %d.\n",__func__, __LINE__);
   a = func_value; 
   a = this_value;
   a = args[0]; 
   return a;
}

DECLARE_HANDLER(test1)
{
   jerry_value_t a;
    printf("%s line %d.\n",__func__, __LINE__);
   a = func_value; 
   a = this_value;
   a = args[0]; 
   return a;
}
int js_static_fs_init(void)
{
    const jerry_char_t my_js_object[] = " \
	fs = \
	{ \
	}";

    jerry_value_t my_js_obj_val;
    my_js_obj_val = jerry_eval(my_js_object, sizeof(my_js_object) - 1, JERRY_PARSE_NO_OPTS);

    set_function_property(my_js_obj_val, "test0", JS_HANDLER_NAME(test0));
    set_function_property(my_js_obj_val, "test1", JS_HANDLER_NAME(test1));
    set_function_property(my_js_obj_val, "test2", JS_HANDLER_NAME(test2));

    jerry_release_value(my_js_obj_val);

    return 0;
}
int js_fs_init(void)
{
    int ret = 0;
    jerry_value_t js_rect = jerry_get_global_object();
    ret = js_static_fs_init();
    jerry_release_value(js_rect);
    return ret;
}
