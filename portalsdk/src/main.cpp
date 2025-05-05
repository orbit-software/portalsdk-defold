// Extension lib defines
#define EXTENSION_NAME portalsdk
#define LIB_NAME "portalsdk"
#define MODULE_NAME LIB_NAME

// Defold SDK
#include <dmsdk/sdk.h>
#define DLIB_LOG_DOMAIN LIB_NAME

#if defined(DM_PLATFORM_HTML5)

#include <emscripten.h>

//----------------------------------------
//-- Startup Events
//----------------------------------------
extern "C" void gameReady();
static int GameReady(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    gameReady();

    lua_pushnil(L);

    return 1;
}
//----------------------------------------
//-- Advertisement
//----------------------------------------

typedef void (*IsAdEnabledCallback)(const bool enabled);
extern "C" bool isAdEnabled(IsAdEnabledCallback callback);
static dmScript::LuaCallbackInfo* isAdEnabledCallback = 0x0;
static void PortalSDK_IsAdEnabledCallback(const bool enabled)
{
    if (!dmScript::IsCallbackValid(isAdEnabledCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }

    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(isAdEnabledCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(isAdEnabledCallback))
    {
        return;
    }

    lua_pushboolean(L, enabled);

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(isAdEnabledCallback);

    if ((isAdEnabledCallback != 0x0))
    {
        dmScript::DestroyCallback(isAdEnabledCallback);
        isAdEnabledCallback = 0x0;
    }

}
static int IsAdEnabled(lua_State* L)
{
    int type = lua_type(L, 1);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);

    isAdEnabledCallback = dmScript::CreateCallback(L, 1);

    isAdEnabled((IsAdEnabledCallback)PortalSDK_IsAdEnabledCallback);

    return 0;
}

extern "C" bool isAdRunning();
static int IsAdRunning(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    bool result = isAdRunning();

   lua_pushboolean(L, result);

    return 1;
}

extern "C" void reloadAd();
static int ReloadAd(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    reloadAd();

    lua_pushnil(L);

    return 1;
}

extern "C" void requestAd();
static int RequestAd(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    requestAd();

    lua_pushnil(L);

    return 1;
}
//----------------------------------------
//-- SDK Information
//----------------------------------------
extern "C" const char* getVersion();
static int GetVersion(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    const char* result = getVersion();

    if (result == 0 || strcmp(result, "") == 0) {
        lua_pushnil(L);
    } else {
        lua_pushstring(L, result);
    }

    return 1;
}
//----------------------------------------
//-- Per-App Information
//----------------------------------------;
typedef void (*GetConfigCallback)(const char* data, const int length);
extern "C" const char* getConfig(GetConfigCallback callback);
static dmScript::LuaCallbackInfo* getConfigCallback = 0x0;
static void PortalSDK_GetConfigCallback(const char* data, const int length)
{
    if (!dmScript::IsCallbackValid(getConfigCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }
    
    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(getConfigCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(getConfigCallback))
    {
        return;
    }

    dmScript::JsonToLua(L, data, length); 

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(getConfigCallback);

    if ((getConfigCallback != 0x0))
    {
        dmScript::DestroyCallback(getConfigCallback);
        getConfigCallback = 0x0;
    }
    
}
static int GetConfig(lua_State* L)
{
    int type = lua_type(L, 1);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }
    
    DM_LUA_STACK_CHECK(L, 0);

    getConfigCallback = dmScript::CreateCallback(L, 1);

    getConfig((GetConfigCallback)PortalSDK_GetConfigCallback);

    return 0;
}
//----------------------------------------
//-- User
//----------------------------------------
typedef void (*GetProfileCallback)(const char* data, const int length);
extern "C" const char* getProfile(GetProfileCallback callback);
static dmScript::LuaCallbackInfo* getProfileCallback = 0x0;
static void PortalSDK_GetProfileCallback(const char* data, const int length)
{
    if (!dmScript::IsCallbackValid(getProfileCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }

    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(getProfileCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(getProfileCallback))
    {
        return;
    }

    dmScript::JsonToLua(L, data, length); 

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(getProfileCallback);

    if ((getProfileCallback != 0x0))
    {
        dmScript::DestroyCallback(getProfileCallback);
        getProfileCallback = 0x0;
    }

}
static int GetProfile(lua_State* L)
{
    int type = lua_type(L, 1);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);

    getProfileCallback = dmScript::CreateCallback(L, 1);

    getProfile((GetProfileCallback)PortalSDK_GetProfileCallback);

    return 0;
}
// extern "C" long getBalance(cb)
extern "C" const char* getLocale();
static int GetLocale(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    const char* result = getLocale();

    if (result == 0 || strcmp(result, "") == 0) {
        lua_pushnil(L);
    } else {
        lua_pushstring(L, result);
    }

    return 1;
}
//----------------------------------------
//-- Share
//----------------------------------------
extern "C" void showSharing(const char* url, const char* text);
static int ShowSharing(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    const char* url = luaL_checkstring(L, 1);
    const char* text = luaL_checkstring(L, 2);

    showSharing(url, text);

    lua_pushnil(L);

    return 1;
}
extern "C" const char* getStartParam();
static int GetStartParam(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    const char* result = getStartParam();

    if (result == 0 || strcmp(result, "") == 0) {
        lua_pushstring(L, "");
    } else {
        lua_pushstring(L, result);
    }

    return 1;
}
//----------------------------------------
//-- IAP
//----------------------------------------
typedef void (*OpenPurchaseConfirmModalCallback)(const char* data, const int length);
extern "C" const char* openPurchaseConfirmModal(const int itemId, const bool useRect, const int x, const int y, 
                                                const int width, const int height, OpenPurchaseConfirmModalCallback callback);
static dmScript::LuaCallbackInfo* openPurchaseConfirmModalCallback = 0x0;
static void PortalSDK_OpenPurchaseConfirmModal(const char* data, const int length)
{
    if (!dmScript::IsCallbackValid(openPurchaseConfirmModalCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }

    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(openPurchaseConfirmModalCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(openPurchaseConfirmModalCallback))
    {
        return;
    }

    dmScript::JsonToLua(L, data, length); 

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(openPurchaseConfirmModalCallback);

    if ((openPurchaseConfirmModalCallback != 0x0))
    {
        dmScript::DestroyCallback(openPurchaseConfirmModalCallback);
        openPurchaseConfirmModalCallback = 0x0;
    }

}
// extern "C" void openPurchaseConfirmModal(itemId, useRect, x, y, width, height, cb);
static int OpenPurchaseConfirmModal(lua_State* L)
{
    int type = lua_type(L, 2);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);

    const int itemId = luaL_checkinteger(L, 1);

    openPurchaseConfirmModalCallback = dmScript::CreateCallback(L, 2);

    openPurchaseConfirmModal(itemId, false, 0, 0, 0, 0, (OpenPurchaseConfirmModalCallback)PortalSDK_OpenPurchaseConfirmModal);

    return 0;
}


typedef void (*GetShopItemsCallback)(const char* data, const int length);
extern "C" const char* getShopItems(GetShopItemsCallback callback);
static dmScript::LuaCallbackInfo* getShopItemsCallback = 0x0;
static void PortalSDK_GetShopItemsCallback(const char* data, const int length)
{
    if (!dmScript::IsCallbackValid(getShopItemsCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }

    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(getShopItemsCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(getShopItemsCallback))
    {
        return;
    }

    dmScript::JsonToLua(L, data, length); 

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(getShopItemsCallback);

    if ((getShopItemsCallback != 0x0))
    {
        dmScript::DestroyCallback(getShopItemsCallback);
        getShopItemsCallback = 0x0;
    }

}
static int GetShopItems(lua_State* L)
{
    int type = lua_type(L, 1);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);

    getShopItemsCallback = dmScript::CreateCallback(L, 1);

    getShopItems((GetShopItemsCallback)PortalSDK_GetShopItemsCallback);

    return 0;
}


typedef void (*GetPurchasedShopItemsCallback)(const char* data, const int length);
extern "C" const char* getPurchasedShopItems(GetPurchasedShopItemsCallback callback);
static dmScript::LuaCallbackInfo* getPurchasedShopItemsCallback = 0x0;
static void PortalSDK_GetPurchasedShopItemsCallback(const char* data, const int length)
{
    if (!dmScript::IsCallbackValid(getPurchasedShopItemsCallback))
    {
        dmLogError("PortalSDK callback is invalid. Use callback function as an argument.");
        return;
    }

    // Callback invoke...
    lua_State* L = dmScript::GetCallbackLuaContext(getPurchasedShopItemsCallback);

    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(getPurchasedShopItemsCallback))
    {
        return;
    }

    dmScript::JsonToLua(L, data, length); 

    int numOfArgs = 2;
    int ret = dmScript::PCall(L, numOfArgs, 0);
    (void)ret;

    dmScript::TeardownCallback(getPurchasedShopItemsCallback);

    if ((getPurchasedShopItemsCallback != 0x0))
    {
        dmScript::DestroyCallback(getPurchasedShopItemsCallback);
        getPurchasedShopItemsCallback = 0x0;
    }

}
static int GetPurchasedShopItems(lua_State* L)
{
    int type = lua_type(L, 1);
    if (type != LUA_TFUNCTION)
    {
        luaL_error(L, "PortalSDK callback is invalid. The first argument should be a callback function.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);

    getPurchasedShopItemsCallback = dmScript::CreateCallback(L, 1);

    getPurchasedShopItems((GetPurchasedShopItemsCallback)PortalSDK_GetPurchasedShopItemsCallback);

    return 0;
}
//----------------------------------------
//-- Cloud Saves
//----------------------------------------
extern "C" void setValueSync(const char* key, const char* value);
static int SetValueSync(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char* key = luaL_checkstring(L, 1);
    const char* value = luaL_checkstring(L, 2);

    setValueSync(key, value);

    lua_pushnil(L);

    return 1;
}
extern "C" const char* getValueSync(const char* key);
static int GetValueSync(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char* key = luaL_checkstring(L, 1);
    
    const char* result = getValueSync(key);

    if (result == 0 || strcmp(result, "") == 0) {
        lua_pushstring(L, "");
    } else {
        lua_pushstring(L, result);
    }

    return 1;
}
extern "C" void removeValue(const char* key);
static int RemoveValue(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char* key = luaL_checkstring(L, 1);

    removeValue(key);

    lua_pushnil(L);

    return 1;
}

//
// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"game_ready", GameReady},
    {"is_ad_running", IsAdRunning},
    {"is_ad_enabled", IsAdEnabled},
    {"reload_ad", ReloadAd},
    {"request_ad", RequestAd},
    {"get_version", GetVersion},
    {"get_config", GetConfig},
    {"get_profile", GetProfile},
    {"get_shop_items", GetShopItems},
    {"get_purchased_shop_items", GetPurchasedShopItems},
    {"open_purchase_confirm_modal", OpenPurchaseConfirmModal},
    {"get_locale", GetLocale},
    {"show_sharing", ShowSharing},
    {"get_start_param", GetStartParam},
    {"set_value_sync", SetValueSync},
    {"get_value_sync", GetValueSync},
    {"remove_value", RemoveValue},
    {0, 0}
};

//
// Extension
static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    // Init Lua
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    dmLogWarning("Registered %s (null) Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, 0, 0, FinalizeExtension)
