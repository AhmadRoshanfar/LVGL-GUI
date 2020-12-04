/*
 * base_obj.c
 *
 *  Created on: Dec 4, 2020
 *      Author: ahmad
 */

#include <base_gui/base_obj.h>
#include <stdio.h>
#include <string.h>
#include "lvgl/lvgl.h"

lv_obj_t *slider_label;
lv_obj_t *slider;
lv_obj_t *btn, *animate_btn;
lv_obj_t *led;
lv_obj_t *btn_label, *animate_btn_label;
lv_obj_t *arc;

static void arc_loader(lv_task_t *t) {
	static int16_t a = 270;

	a += 2;

	lv_arc_set_end_angle(t->user_data, a);

	if (a >= 270 + 360) {
		lv_task_del(t);
		return;
	}
}

static void event_handler(lv_obj_t *obj, lv_event_t event) {
	if (event == LV_EVENT_VALUE_CHANGED) {
		printf("Value: %d\n", lv_slider_get_value(slider));
		static char buf[4];
		snprintf(buf, 4, "%u", lv_slider_get_value(slider));
		lv_label_set_text(slider_label, buf);
	}
	if (event == LV_EVENT_CLICKED) {
		printf("Clicked \n");
	}
}

void base_obj(void) {

	printf("base_obj \n");
	/* Screen Object */
	lv_obj_t *base_obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(base_obj, 800, 800);

	static lv_style_t style_gum;
	lv_style_init(&style_gum);
	lv_style_set_transform_width(&style_gum, LV_STATE_PRESSED, 10);
	lv_style_set_transform_height(&style_gum, LV_STATE_PRESSED, -10);
	lv_style_set_value_letter_space(&style_gum, LV_STATE_PRESSED, 5);
	lv_style_set_transition_time(&style_gum, LV_STATE_DEFAULT, 250);
	lv_style_set_transition_delay(&style_gum, LV_STATE_DEFAULT, 100);
	lv_style_set_transition_prop_1(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
	lv_style_set_transition_prop_2(&style_gum, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);

	/* Animation Button Object */
	animate_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(animate_btn, 150, 50);
	lv_obj_align(animate_btn, slider, LV_ALIGN_IN_BOTTOM_MID, 0, -60);
	lv_btn_set_checkable(animate_btn, true);
	lv_obj_add_style(animate_btn, LV_BTN_PART_MAIN, &style_gum);

	/* Animation Button Label Object */
	animate_btn_label = lv_label_create(animate_btn, NULL);
	lv_label_set_text(animate_btn_label, "Animation Button");

	/* Led Object */
//	led = lv_led_create(lv_scr_act(), NULL);
//	lv_obj_align(led, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
//	lv_obj_set_drag(led, 1);
	/* Button Object */
	btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn, event_handler);
	lv_obj_set_size(btn, 150, 50);
	lv_obj_align(btn, slider, LV_ALIGN_IN_TOP_MID, 0, 60);
	lv_btn_set_checkable(btn, true);

	/* Button Label Object */
	btn_label = lv_label_create(btn, NULL);
	lv_label_set_text(btn_label, "Button");

	/* Slider Object */
	slider = lv_slider_create(lv_scr_act(), NULL);
	lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);
//	lv_obj_set_pos(slider, 200, 100);
	lv_obj_set_width(slider, LV_DPI * 2);
	lv_slider_set_range(slider, 0, 100);
	lv_obj_set_event_cb(slider, event_handler);

	/* Slider Label Object */
	slider_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(slider_label, "0");
	lv_obj_set_auto_realign(slider_label, true);
	lv_obj_align(slider_label, slider, LV_ALIGN_IN_TOP_RIGHT, 0, 10);

	/* Arc Loader Object */
	arc = lv_arc_create(lv_scr_act(), NULL);
	lv_arc_set_bg_angles(arc, 0, 360);
	lv_arc_set_angles(arc, 270, 270);
	lv_obj_align(arc, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

	lv_task_create(arc_loader, 20, LV_TASK_PRIO_LOWEST, arc);

	fflush(NULL);
}
