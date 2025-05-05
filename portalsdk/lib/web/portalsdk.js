var LIB = {
  
  $PortalSDK: {
      _getConfigCallback: null,
      _getProfileCallback: null,
      _getPurchasedShopItemsCallback: null,
      _getShopItemsCallback: null,
      _openPurchaseConfirmModalCallback: null
  },

  //----------------------------------------
  //-- Startup Events
  //----------------------------------------
  
  gameReady: function() {
    return window.CryptoSteamSDK.gameReady();
  },

  //----------------------------------------
  //-- Advertisement
  //----------------------------------------
  
  isAdEnabled: function(cb) {

    PortalSDK._isAdEnabledCallback = cb;

    window.CryptoSteamSDK.isAdEnabled().then(response => {
        // dynCall_vi(cb, response);

        {{{ makeDynCall("vi", "PortalSDK._isAdEnabledCallback")}}}(response);
    });
  },
  isAdRunning: function() {
    return window.PortalEmuSDK.isAdRunning();
  },
  reloadAd: function() {
    window.PortalEmuSDK.reloadAd();
  },
  requestAd: function() {
    return window.PortalEmuSDK.requestAd();
  },
  
  
  //----------------------------------------
  //-- SDK Information
  //----------------------------------------
  
  getVersion: function() {
    var str = window.CryptoSteamSDK.getVersion();

    var bufferSize = lengthBytesUTF8(str) + 1;
    var buffer = _malloc(bufferSize);
    stringToUTF8(str, buffer, bufferSize);
    return buffer;
  },
   
  //----------------------------------------
  //-- Per-App Information
  //----------------------------------------
  
  getConfig: function(cb) {
    
    PortalSDK._getConfigCallback = cb;
    
    window.CryptoSteamSDK.getConfig().then(response => {
       var str = JSON.stringify(response)
       
       var bufferSize = lengthBytesUTF8(str) + 1;
       var buffer = _malloc(bufferSize);
       stringToUTF8(str, buffer, bufferSize);
       
       // dynCall_vi(cb, buffer);

        {{{ makeDynCall("vi", "PortalSDK._getConfigCallback")}}}(buffer, str.length);
    });
  },
    
   
  //----------------------------------------
  //-- User
  //----------------------------------------
  
  getProfile: function(cb) {

    PortalSDK._getProfileCallback = cb;

    window.CryptoSteamSDK.getProfile().then(response => {
      
      var str = JSON.stringify(response)
      
      var bufferSize = lengthBytesUTF8(str) + 1;
      var buffer = _malloc(bufferSize);
      stringToUTF8(str, buffer, bufferSize);
      
      // dynCall_vi(cb, buffer);
      {{{ makeDynCall("vi", "PortalSDK._getProfileCallback")}}}(buffer, str.length);
    });
  },
    
  getBalance: function(cb) {
    window.CryptoSteamSDK.getBalance().then(response => {
       var str = response.toString()
       
       var bufferSize = lengthBytesUTF8(str) + 1;
       var buffer = _malloc(bufferSize);
       stringToUTF8(str, buffer, bufferSize);
       
       dynCall_vi(cb, buffer);
    });
  },

  getLocale: function() {  
    var str = window.CryptoSteamSDK.getLocale();
    var bufferSize = lengthBytesUTF8(str) + 1;
    var buffer = _malloc(bufferSize);
    stringToUTF8(str, buffer, bufferSize);
    return buffer
  },

  //----------------------------------------
  //-- Share
  //----------------------------------------
    
  showSharing: function(url, text) {
      window.CryptoSteamSDK.showSharing(url, text)
  },
 
  getStartParam: function() {  
    var str = window.PortalEmuSDK.getStartParam();
    var bufferSize = lengthBytesUTF8(str) + 1;
    var buffer = _malloc(bufferSize);
    stringToUTF8(str, buffer, bufferSize);
    return buffer
  },
  
  //----------------------------------------
  //-- IAP
  //----------------------------------------
  
  openPurchaseConfirmModal: function(itemId, useRect, x, y, width, height, cb) {
    
    PortalSDK._openPurchaseConfirmModalCallback = cb;

    window.CryptoSteamSDK.getShopItems().then(response => {
    
      const item = response.find(item => item.id === itemId)
      
      if(!item) {
          const str = "{ \"status\": " + "\"item not found\"" + "}";
                   
          const bufferSize = lengthBytesUTF8(str) + 1;
          const buffer = _malloc(bufferSize);
          stringToUTF8(str, buffer, bufferSize);
          
          // dynCall_vi(cb, buffer);
          {{{ makeDynCall("vi", "PortalSDK._openPurchaseConfirmModalCallback")}}}(buffer, str.length);
          return;
      }

      
      var rect = null;
      
      if(useRect) {
        rect = { x, y, width, height }; 
      } 
   
      window.CryptoSteamSDK.openPurchaseConfirmModal(item, rect).then(response => {
           
           var str;
           try {
            str = JSON.stringify(response);
           }
           catch(ex) {
            str = "{ \"status\": " + "\"error\"" + "}";
           }
           
           var bufferSize = lengthBytesUTF8(str) + 1;
           var buffer = _malloc(bufferSize);
           stringToUTF8(str, buffer, bufferSize);
           
           // dynCall_vi(cb, buffer);
           {{{ makeDynCall("vi", "PortalSDK._openPurchaseConfirmModalCallback")}}}(buffer, str.length);
        }).catch(response => {
           const str = "{ \"status\": " + "\"error\"" + "}";
                      
           var bufferSize = lengthBytesUTF8(str) + 1;
           var buffer = _malloc(bufferSize);
           stringToUTF8(str, buffer, bufferSize);
           
           // dynCall_vi(cb, buffer);
           {{{ makeDynCall("vi", "PortalSDK._openPurchaseConfirmModalCallback")}}}(buffer, str.length);
        });
 
    })  
  },

  getShopItems: function(cb) {
      
      PortalSDK._getShopItemsCallback = cb;
      
      window.CryptoSteamSDK.getShopItems().then(response => {
         
          var str = "{ \"items\": " + JSON.stringify(response) + "}";
          
          var bufferSize = lengthBytesUTF8(str) + 1;
          var buffer = _malloc(bufferSize);
          stringToUTF8(str, buffer, bufferSize);
          
          // dynCall_vi(cb, buffer);
          {{{ makeDynCall("vi", "PortalSDK._getShopItemsCallback")}}}(buffer, str.length);
      });
  },
    
  getPurchasedShopItems: function(cb) {
      
      PortalSDK._getPurchasedShopItemsCallback = cb;

      window.CryptoSteamSDK.getPurchasedShopItems().then(response => {
          
          var str = JSON.stringify(response);
          
          var bufferSize = lengthBytesUTF8(str) + 1;
          var buffer = _malloc(bufferSize);
          stringToUTF8(str, buffer, bufferSize);
          
          //dynCall_vi(cb, buffer);
          {{{ makeDynCall("vi", "PortalSDK._getPurchasedShopItemsCallback")}}}(buffer, str.length);
      });
  },
    

  //----------------------------------------
  //-- Cloud Saves
  //----------------------------------------
  
  setValueSync: function(key, value) {
    window.PortalEmuSDK.setValueSync(UTF8ToString(key), UTF8ToString(value))
  },
  
  getValueSync: function(key) {
      var str = window.PortalEmuSDK.getValueSync(UTF8ToString(key))
      
      if(!str) {
        str = "";
      }
      
      var bufferSize = lengthBytesUTF8(str) + 1;
      var buffer = _malloc(bufferSize);
      stringToUTF8(str, buffer, bufferSize);
      
      return buffer;
  },
  
  removeValue: function(key) {
    window.PortalEmuSDK.removeValueSync(UTF8ToString(key));
  },
    
  setValue: function(key, value) {
    window.CryptoSteamSDK.setValue(UTF8ToString(key), UTF8ToString(value))
  },

  getValue: function(key, cb) {
    window.CryptoSteamSDK.getValue(UTF8ToString(key)).then(response => {
        var str = response;
                  
        var bufferSize = lengthBytesUTF8(str) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(str, buffer, bufferSize);
        
        dynCall_vi(cb, buffer);
    }).catch(response => {
        var str = "";
                  
        var bufferSize = lengthBytesUTF8(str) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(str, buffer, bufferSize);
        
        dynCall_vi(cb, buffer);
    });
  },

  
  //----------------------------------------
  //-- Achievements
  //----------------------------------------
  
  
  // not implemented
  
  //----------------------------------------
  //-- Game Events
  //----------------------------------------
  
  // not implemented
  
 
}

autoAddDeps(LIB, '$PortalSDK');
addToLibrary(LIB);
