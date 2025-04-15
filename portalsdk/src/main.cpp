// Extension lib defines
#define EXTENSION_NAME portalsdk
#define LIB_NAME "portalsdk"
#define MODULE_NAME LIB_NAME

// Defold SDK
#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

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
// todo async methods
// extern "C" bool isAdEnabled(cb);
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
extern "C" const char* getConfig();
static int GetConfig(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    const char* result = getConfig();

    if (result == 0 || strcmp(result, "") == 0) {
        lua_pushnil(L);
    } else {
        lua_pushstring(L, result);
    }

    return 1;
}
//----------------------------------------
//-- User
//----------------------------------------
// todo async methods
// extern "C" const char* getProfile(cb);
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
// todo async methods
// extern "C" void openPurchaseConfirmModal(itemId, useRect, x, y, width, height, cb);
// extern "C" const char* getShopItems(cb);
// extern "C" const char* getPurchasedShopItems(cb);
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
// todo async methods
// extern "C" void setValue(const char* key, const char* v);
// extern "C" const char* getValue(const char* key, cb);
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
    {"GameReady", GameReady},
    {"IsAdRunning", IsAdRunning},
    {"ReloadAd", ReloadAd},
    {"RequestAd", RequestAd},
    {"GetVersion", GetVersion},
    {"GetConfig", GetConfig},
    {"GetLocale", GetLocale},
    {"ShowSharing", ShowSharing},
    {"GetStartParam", GetStartParam},
    {"SetValueSync", SetValueSync},
    {"GetValueSync", GetValueSync},
    {"RemoveValue", RemoveValue},
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
