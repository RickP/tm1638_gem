#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <bcm2835.h>
#include <tm1638.h>
#include <ruby.h>

static tm1638_p t;

uint8_t rarray_to_int(VALUE data) {
  uint8_t ret = 0;
  if (TYPE(data) == T_ARRAY) {
    long s_len = RARRAY_LEN(data);

    VALUE *s_arr = RARRAY_PTR(data);

    for(int i = 0; i < 8; i++) {
      ret += ((s_len >= i+1 && (s_arr[i]) == Qtrue) ? 1 : 0) << (7-i);
    }
  }
  return ret;
}

static VALUE set_intensity(VALUE self, VALUE intensity) {
  uint8_t value = (uint8_t) NUM2INT(intensity);
  tm1638_set_intensity(t, value);
  return Qtrue;
}

static VALUE write_text(VALUE self, VALUE text, VALUE dots) {
  tm1638_send_cls(t);
  tm1638_set_7seg_text(t, StringValuePtr(text), rarray_to_int(dots));
  return Qtrue;
}

static VALUE set_leds(VALUE self, VALUE reds, VALUE greens) {
  tm1638_set_8leds(t, rarray_to_int(reds), rarray_to_int(greens));
  return Qtrue;
}

static VALUE get_buttons(VALUE self) {
  VALUE ret = rb_ary_new2(8);
  uint8_t buttons = tm1638_read_8buttons(t);
  for(int i = 0; i < 8; i++) {
    rb_ary_push(ret, (buttons & (1 << i)) != 0 ? Qtrue : Qfalse);
  }
  return ret;
}

static VALUE get_button(VALUE self) {
  uint8_t buttons = tm1638_read_8buttons(t);
  for (int i = 0; i < 8; i++) {
    if (buttons & (1 << i)) {
      return INT2FIX(8-i);
    }
  }
  return INT2FIX(0);
}

static VALUE init(VALUE self, VALUE data, VALUE clock, VALUE strobe) {
  t = tm1638_alloc(NUM2INT(data), NUM2INT(clock), NUM2INT(strobe));
  return Qtrue;
}

void Init_tm1638(void) {
  bcm2835_init();

  VALUE klass = rb_define_class("Tm1638", rb_cObject);

  rb_define_singleton_method(klass, "init", init, 3);
  rb_define_singleton_method(klass, "set_intensity", set_intensity, 1);
  rb_define_singleton_method(klass, "write", write_text, 2);
  rb_define_singleton_method(klass, "set_leds", set_leds, 2);
  rb_define_singleton_method(klass, "get_buttons", get_buttons, 0);
  rb_define_singleton_method(klass, "get_button", get_button, 0);
}
