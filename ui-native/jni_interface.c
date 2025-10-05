// ui-native/jni_interface.c

#include <jni.h>
#include "framebuffer.h"

JNIEXPORT jboolean JNICALL Java_org_javaos_ui_NativeUI_init(JNIEnv *env, jclass clazz) {
    return (fb_init() == 0) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL Java_org_javaos_ui_NativeUI_clear(JNIEnv *env, jclass clazz, jint color) {
    fb_clear((uint32_t)color);
}

JNIEXPORT void JNICALL Java_org_javaos_ui_NativeUI_drawRect(JNIEnv *env, jclass clazz, jint x, jint y, jint w, jint h, jint color) {
    fb_draw_rect(x, y, w, h, (uint32_t)color);
}

JNIEXPORT void JNICALL Java_org_javaos_ui_NativeUI_shutdown(JNIEnv *env, jclass clazz) {
    fb_close();
}

