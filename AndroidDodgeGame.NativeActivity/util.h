#pragma once
#include <malloc.h>

#define PK_LOG_TAG "Dodge Game"
#define PK_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, PK_LOG_TAG, __VA_ARGS__))
#define PK_LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, PK_LOG_TAG, __VA_ARGS__))
#define PK_LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, PK_LOG_TAG, __VA_ARGS__))
#define PK_STACK_ALLOC(Type, count) reinterpret_cast<Type*>(__builtin_alloca(sizeof(Type) * count))
#define PK_MEMORY_ALLOC(Type, count) reinterpret_cast<Type*>(malloc(sizeof(Type) * count))
#define PK_CONTIGUOUS_ALLOC(Type, count) reinterpret_cast<Type*>(calloc(count, sizeof(Type)))

char* get_asset_text(AAssetManager* assetManager, const char* filepath);