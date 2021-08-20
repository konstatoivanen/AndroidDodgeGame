#include "util.h"

char* get_asset_text(AAssetManager* assetManager, const char* filepath)
{

    AAsset* asset = AAssetManager_open(assetManager, filepath, AASSET_MODE_UNKNOWN);
    if (NULL == asset)
    {
        PK_LOGE("_ASSET_NOT_FOUND_");
        return nullptr;
    }

    size_t size = AAsset_getLength(asset);
    char* buffer = PK_MEMORY_ALLOC(char, size + 1);
    AAsset_read(asset, buffer, size);
    AAsset_close(asset);
    buffer[size] = '\0';
    return buffer;
}