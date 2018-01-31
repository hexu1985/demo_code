;(function(g){
    g.require = {
        // 事件绑定
        addEvent: function(element, event, handler) {
            if(element.addEventListener) {
                element.addEventListener(event, handler, false);
            } else if(element.attachEvent) {
                element.attachEvent("on" + event, handler);
            } else {
                element["on" + event] = handler;
            }
        },
        requireJS: function(jsPath, callback) {
            var _this = this;
            var newScript = document.createElement("script");
            newScript.type = "text/javascript";
            newScript.setAttribute("src", jsPath);
            $(document).ready(function($) {
                document.querySelector("body").appendChild(newScript);
                _this.addEvent(newScript, "load", function() {
                    if (typeof callback == "function") {
                        callback();
                    }
                });
            });
        },

        requireCSS: function(cssPath, callback) {
            var _this = this;
            var link = document.createElement("link");
            link.rel = "stylesheet";
            link.type = "text/css";
            link.href = cssPath;
            document.getElementsByTagName("head")[0].appendChild(link);
            _this.addEvent(link, "load", function() {
                if (typeof callback == "function") {
                    callback();
                }
            });
        }
    };
})(window);