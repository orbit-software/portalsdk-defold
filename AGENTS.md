# portalsdk-defold — AGENTS.md

## Purpose
Defold native extension (`portalsdk/`) exposing the Orbit Portal JS SDK to Lua as the global `portalsdk` table.
**HTML5-only**: on every other platform the extension registers a no-op (`main.cpp` `#else` branch logs
"Registered portalsdk (null) Extension") and the `portalsdk` table does not exist. The repo root is also the
sample/test project (`main/`, `game.project`).

## How a game integrates it
- Dependency: add the repo (git remote `https://github.com/orbit-software/portalsdk-defold.git`) as a Defold
  library dependency, e.g. zip of a tag: `https://github.com/orbit-software/portalsdk-defold/archive/refs/tags/v0.1.92.zip`
  (`game.project` `[library] include_dirs = portalsdk` publishes only the `portalsdk/` folder).
- `game.project` `[html5]` settings used by the sample: `htmlfile = /portalsdk/manifests/web_template/engine_template.html`,
  `cssfile = /portalsdk/manifests/web_template/style.css`, `scale_mode = stretch`, `wasm_streaming = 1`.
  The custom HTML template is what loads the JS SDK, so a game must use it (or replicate its script tags).
- Lua API (`portalsdk/api/portalsdk.script_api` documents it; `main.cpp` `Module_methods` is the source of truth).
  Callbacks receive `(self, data)`; async results are delivered later via the JS promise.
  - `game_ready()` — required; signals the game is loaded.
  - `is_ad_enabled(cb)` — cb(self, bool).
  - `request_ad(cb, placement_id?)` / `request_reward_ad(cb, placement_id?)` — show ad; cb(self, success bool).
  - `set_on_ad_start(cb)` / `set_on_ad_end(cb)` — persistent ad lifecycle callbacks (cb(self, bool)).
  - `clear_on_ad_start()` / `clear_on_ad_end()` — remove those callbacks.
  - `get_version()` — SDK version string or nil.
  - `get_config(cb)` — cb(self, table) `{supported_screen_formats, supported_devices}`.
  - `get_profile(cb)` — cb(self, table) user profile (JSON decoded via `dmScript::JsonToLua`).
  - `get_locale()` — locale string or nil.
  - `get_balance(cb)` — gems balance (cb(self, number)); `get_balance_coins(cb)` — coins balance.
  - `get_shop_items(cb)` — cb(self, `{items = {...}}`); `get_purchased_shop_items(cb)` — cb(self, array).
  - `open_purchase_confirm_modal(item_id, cb)` — cb(self, `{status=...}`); `"item not found"`/`"error"` on failure.
  - `set_value_sync(key, value)` / `get_value_sync(key)` (returns "" when missing) / `remove_value(key)` — cloud KV.
  - `show_sharing(url, text)` — Telegram share dialog; `get_start_param()` — start param string ("" if none).
  - Obsolete, still registered: `is_ad_running()` (always false), `reload_ad()` (no-op).
- Sample usage of every call: `main/main.script`.

## How it talks to the JS SDK
- `portalsdk/lib/web/portalsdk.js` is an Emscripten JS library (`addToLibrary(LIB)`, `autoAddDeps(LIB,'$PortalSDK')`)
  that implements the `extern "C"` functions declared in `portalsdk/src/main.cpp`. Strings are marshalled with
  `UTF8ToString`/`stringToUTF8` + `_malloc`; callbacks are invoked with `{{{ makeDynCall("vi", ...) }}}`.
- The JS side calls the browser globals **`window.CryptoSteamSDK`** (ads, config, profile, balance, shop,
  sharing, `setValue`/`getValue`) and **`window.PortalEmuSDK`** (`getStartParam`, `setValueSync`, `getValueSync`,
  `removeValueSync`).
- The SDK script itself is loaded by the HTML template: `<script src="https://sdk.portalapp.games/sdk.umd.js">`,
  followed by `await PortalSDK.initialize(); await PortalSDK.initializeOverlay()` and a `window.startupConfig`
  (`isFullscreen`, `overlayPosition`). The template then defines `window.runGame` for the engine loader.
  No `@orbit-software/sdk` npm package is referenced in this repo; only the UMD URL above.

## Build / test
- Open the repo root in the Defold editor and Bundle -> HTML5 (or `Project > Build HTML5`) — the extension
  needs the Defold cloud/native builder (there is no local Makefile, bob.jar script, or CI workflow in the repo).
- Runtime verification is only possible in a browser where `sdk.umd.js` loads: `main/main.script` prints results
  of every API call to the console.

## Release
- Versions are git tags on `master`: `v0.1.3` ... `v0.1.9`, `v0.1.92` (latest). `game.project` `version = 0.1` is
  not bumped. No GitHub workflow — tagging is manual.

## Gotchas
- `main.cpp` uses two different global objects (`CryptoSteamSDK` vs `PortalEmuSDK`); the HTML template only
  visibly provides `PortalSDK`. Whether `sdk.umd.js` also defines those aliases cannot be verified from this repo.
- One-shot callbacks are stored in a single static slot per function; calling e.g. `get_config` twice before the
  first reply overwrites (and leaks) the first callback.
- `open_purchase_confirm_modal` in Lua always passes `useRect=false`; the positioned variant exists only in JS.
- `get_balance`/`get_balance_coins` JSON-decode a bare number string, so `data` is a number, not a table.
- `getValue`/`setValue` (async cloud KV) exist in JS but are not bound in `main.cpp`.
- `README.md` is a title only; `.gitignore` excludes `/build`, `manifest.*.der`, `.internal`.
