(window.webpackJsonp=window.webpackJsonp||[]).push([[129],{1783:function(t,e,n){},1956:function(t,e,n){var map={"./icon-why-mqtt-1.png":1321,"./icon-why-mqtt-2.png":1322,"./icon-why-mqtt-3.png":1323,"./icon-why-mqtt-4.png":1324,"./icon-why-mqtt-5.png":1325};function c(t){var e=r(t);return n(e)}function r(t){if(!n.o(map,t)){var e=new Error("Cannot find module '"+t+"'");throw e.code="MODULE_NOT_FOUND",e}return map[t]}c.keys=function(){return Object.keys(map)},c.resolve=r,t.exports=c,c.id=1956},1957:function(t,e,n){var map={"./banner-bg.png":1354,"./icon-android.png":1355,"./icon-angular.png":1356,"./icon-dart.png":1357,"./icon-electron.png":1358,"./icon-esp32.png":1359,"./icon-esp8266.png":1360,"./icon-flutter.png":1361,"./icon-go.png":1362,"./icon-ios.png":1363,"./icon-java.png":1364,"./icon-miniprogram.png":1365,"./icon-mqtt.png":1366,"./icon-nodejs.png":1367,"./icon-php.png":1368,"./icon-python.png":1369,"./icon-raspberry-pi.png":1370,"./icon-react.png":1371,"./icon-rust.png":1372,"./icon-vue.png":1373,"./icon-websocket.png":1374,"./icon-why-mqtt-1.png":1321,"./icon-why-mqtt-2.png":1322,"./icon-why-mqtt-3.png":1323,"./icon-why-mqtt-4.png":1324,"./icon-why-mqtt-5.png":1325};function c(t){var e=r(t);return n(e)}function r(t){if(!n.o(map,t)){var e=new Error("Cannot find module '"+t+"'");throw e.code="MODULE_NOT_FOUND",e}return map[t]}c.keys=function(){return Object.keys(map)},c.resolve=r,t.exports=c,c.id=1957},1958:function(t,e,n){"use strict";n(1783)},2392:function(t,e,n){"use strict";n.r(e);var c=n(5),r=(n(52),n(8)),l=n(644),o=n(222),d=Object(r.b)({name:"MQTT",head:{},nuxtI18n:{locales:["en","zh"]},setup:function(){var t=Object(r.o)(),e=t.app,n=t.$auth,d=t.$axios,m=Object(r.q)(),v=Object(r.j)("server"),h=Object(r.n)(Object(c.a)(regeneratorRuntime.mark((function t(){var e,n,c,r,l,data;return regeneratorRuntime.wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return c={blogType:"mqtt_features"},t.prev=1,t.next=4,d.get("/blog",{params:c});case 4:r=t.sent,l=r.status,data=r.data,200===l&&(null===(e=null==data?void 0:data.items)||void 0===e?void 0:e.length)&&(n=data.items),t.next=12;break;case 10:t.prev=10,t.t0=t.catch(1);case 12:return t.abrupt("return",n);case 13:case"end":return t.stop()}}),t,null,[[1,10]])}))),"f8vLK/qDXOXHrkRkZkGKGQ=="),_=Object(r.n)(Object(c.a)(regeneratorRuntime.mark((function t(){var e,n,c,r,l,data;return regeneratorRuntime.wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return c={blogType:"mqtt_basics"},t.prev=1,t.next=4,d.get("/blog",{params:c});case 4:r=t.sent,l=r.status,data=r.data,200===l&&(null===(e=null==data?void 0:data.items)||void 0===e?void 0:e.length)&&(n=data.items),t.next=12;break;case 10:t.prev=10,t.t0=t.catch(1);case 12:return t.abrupt("return",n);case 13:case"end":return t.stop()}}),t,null,[[1,10]])}))),"i3tqBv1XlodQ7l/w37Wixg==");return Object(l.a)(m,{title:e.i18n.tc("mqtt.title"),description:e.i18n.tc("mqtt.description"),keywords:e.i18n.te("mqtt.keywords")?e.i18n.tc("mqtt.keywords"):""}),{currentTag:v,featureData:h,basicsData:_,handleTagChange:function(t){v.value=t},getCloudStartTrialUrl:function(){Object(o.a)(e,n,"new")}}}}),m=(n(1958),n(53)),component=Object(m.a)(d,(function(){var t=this,e=t.$createElement,c=t._self._c||e;return c("div",{staticClass:"page-mqtt"},[c("section",{attrs:{id:"banner"}},[c("div",{staticClass:"container has-text-centered"},[c("h1",{staticClass:"mb-5"},[t._v(t._s(t.$t("mqtt.banner.title")))]),t._v(" "),c("p",{staticClass:"mx-auto is-size-18"},[t._v(t._s(t.$t("mqtt.banner.subTitle")))])])]),t._v(" "),c("section",{staticClass:"py-6",attrs:{id:"why-mqtt"}},[c("div",{staticClass:"container has-text-centered"},[c("div",{staticClass:"columns is-multiline"},t._l(t.$t("mqtt.why"),(function(e,r){return c("div",{key:r,staticClass:"column"},[c("div",{staticClass:"px-3"},[c("img",{staticClass:"mb-5",attrs:{loading:"lazy",src:n(1956)("./icon-why-mqtt-"+(r+1)+".png"),alt:e,width:"36",height:"36"}}),t._v(" "),c("p",{staticClass:"is-size-18 is-text-black has-text-weight-semibold"},[t._v(t._s(e))])])])})),0)])]),t._v(" "),t.basicsData&&t.featureData?c("section",{staticClass:"py-88",attrs:{id:"mqtt-beginners-guide"}},[c("div",{staticClass:"container has-text-centered"},[c("h2",{staticClass:"mb-5"},[t._v(t._s(t.$t("mqtt.MQTTGettingStarted.title")))]),t._v(" "),c("p",{staticClass:"mb-64 is-size-18"},[t._v(t._s(t.$t("mqtt.MQTTGettingStarted.subTitle")))]),t._v(" "),c("div",{staticClass:"mb-6 columns is-multiline has-text-left"},t._l(t.basicsData.concat(t.featureData),(function(e){return c("div",{key:e.id,staticClass:"column is-6"},[c("nuxt-link",{staticClass:"card is-block py-6 px-5 is-shadowless is-trans-top",attrs:{to:t.localePath("/blog/"+e.titleUrl)}},[c("h3",{staticClass:"mb-5 is-size-5"},[t._v(t._s(e.title)+" "),c("span",{staticClass:"is-text-primary"},[t._v("→")])]),t._v(" "),c("p",{staticClass:"is-text-normal"},[t._v(t._s(e.summary))])])],1)})),0),t._v(" "),c("nuxt-link",{staticClass:"button is-gradient has-text-weight-medium",attrs:{to:t.localePath("/mqtt/mqtt5")}},[t._v("\n        "+t._s(t.$t("mqtt.MQTTGettingStarted.learnMore"))+" →\n      ")])],1)]):t._e(),t._v(" "),c("section",{staticClass:"py-88",attrs:{id:"mqtt-in-depth"}},[c("div",{staticClass:"container has-text-centered"},[c("h2",{staticClass:"mb-5"},[t._v(t._s(t.$t("mqtt.MQTTInDepth.title")))]),t._v(" "),c("p",{staticClass:"mb-64 is-size-18"},[t._v(t._s(t.$t("mqtt.MQTTInDepth.subTitle")))]),t._v(" "),c("div",{staticClass:"pb-5 is-flex is-justify-content-center"},[c("div",{staticClass:"blog-tags columns is-mobile is-align-items-center"},t._l(t.$t("mqtt.MQTTInDepth.tagOptions"),(function(e){return c("div",{key:e.value,staticClass:"column is-narrow"},[c("div",{class:["blog-tag","is-inline-block","px-6","py-2",{"is-active":t.currentTag===e.value}],on:{click:function(n){return t.handleTagChange(e.value)}}},[t._v("\n              "+t._s(e.label)+"\n            ")])])})),0)]),t._v(" "),c("div",{staticClass:"mb-6 columns is-multiline has-text-left"},t._l(t.$t("mqtt.MQTTInDepth.list."+t.currentTag),(function(e){return c("div",{key:e.link,staticClass:"column is-4"},[c("nuxt-link",{staticClass:"card is-relative is-block p-5 pr-6 is-shadowless is-trans-top",attrs:{to:t.localePath(e.link)}},[c("p",{staticClass:"is-text-normal"},[t._v(t._s(e.title)+" "),c("span",{staticClass:"is-text-primary"},[t._v("→")])]),t._v(" "),c("img",{staticClass:"icon-tech-stack",attrs:{loading:"lazy",src:n(1957)("./"+e.icon+".png"),alt:e.title,width:"32",height:"32"}})])],1)})),0),t._v(" "),c("nuxt-link",{staticClass:"is-text-primary has-text-weight-medium hover-move",attrs:{to:t.localePath(t.$t("mqtt.MQTTInDepth.learnMoreLink"))}},[t._v("\n        "+t._s(t.$t("mqtt.MQTTInDepth.learnMore"))+" →\n      ")])],1)]),t._v(" "),c("section",{staticClass:"py-140",attrs:{id:"get-started"}},[c("div",{staticClass:"container"},[c("h2",{staticClass:"mb-64 has-text-white has-text-centered"},[t._v(t._s(t.$t("mqtt.quickStart.title")))]),t._v(" "),c("div",{staticClass:"steps is-flex is-flex-direction-column has-text-white"},t._l(t.$t("mqtt.quickStart.steps"),(function(e,n){return c("div",{key:n,staticClass:"step is-flex"},[c("div",{staticClass:"step-head is-relative is-flex-grow-0"},[c("div",{staticClass:"step-line"}),t._v(" "),c("div",{staticClass:"step-icon is-relative is-flex is-align-items-center is-justify-content-center is-size-4 has-text-weight-semibold"},[t._v("\n              "+t._s(n+1)+"\n            ")])]),t._v(" "),c("div",{staticClass:"step-main mb-64 pl-4 is-flex-grow-1"},[c("h3",{staticClass:"step-title mb-4 is-size-4 has-text-white has-text-weight-semibold"},[t._v(t._s(e.title))]),t._v(" "),0===n?c("div",{staticClass:"step-description"},[c("div",{staticClass:"columns"},[c("div",{staticClass:"column"},[c("div",{staticClass:"card cloud px-6 py-5 is-flex is-flex-direction-column is-justify-content-space-between"},[c("div",[c("h4",{staticClass:"mb-5 is-size-5 has-text-white"},[t._v(t._s(e.cloud.title))]),t._v(" "),c("p",{staticClass:"mb-5"},[t._v(t._s(e.cloud.contents))])]),t._v(" "),c("div",[c("a",{staticClass:"button is-gradient px-5 py-2 has-text-weight-medium",attrs:{href:"javascript:;"},on:{click:t.getCloudStartTrialUrl}},[t._v("\n                        "+t._s(e.cloud.tryCloud)+" →\n                      ")])])])]),t._v(" "),t._m(0,!0),t._v(" "),c("div",{staticClass:"column"},[c("div",{staticClass:"card enterprise px-6 py-5 is-flex is-flex-direction-column is-justify-content-space-between"},[c("div",[c("h4",{staticClass:"mb-5 is-size-5 has-text-white"},[t._v(t._s(e.enterprise.title))]),t._v(" "),c("p",{staticClass:"mb-5"},[t._v(t._s(e.enterprise.contents))])]),t._v(" "),c("div",[c("nuxt-link",{staticClass:"button is-gradient px-5 py-2 has-text-weight-medium",attrs:{to:t.localePath("/try?product=enterprise")}},[t._v("\n                        "+t._s(e.enterprise.download)+" →\n                      ")])],1)])])])]):t._e(),t._v(" "),1===n?c("div",{staticClass:"step-description"},[c("div",{staticClass:"card px-6 py-5"},[c("p",{staticClass:"mb-5"},[t._v(t._s(e.mqttx.contents))]),t._v(" "),c("nuxt-link",{staticClass:"button is-gradient px-5 py-2 has-text-weight-medium",attrs:{to:t.localePath("/try?product=MQTTX")}},[t._v("\n                  "+t._s(e.mqttx.download)+" →\n                ")])],1)]):t._e(),t._v(" "),2===n?c("div",{staticClass:"step-description"},[c("div",{staticClass:"card px-6 py-5"},[c("h4",{staticClass:"mb-5 is-size-5 has-text-white"},[t._v(t._s(e.automotive.title))]),t._v(" "),c("p",{staticClass:"mb-5"},[t._v(t._s(e.automotive.contents))]),t._v(" "),c("nuxt-link",{staticClass:"button is-gradient px-5 py-2 has-text-weight-medium",attrs:{to:t.localePath(e.automotive.learnMoreLink)}},[t._v("\n                  "+t._s(e.automotive.learnMore)+" →\n                ")])],1)]):t._e()])])})),0)])])])}),[function(){var t=this,e=t.$createElement,n=t._self._c||e;return n("div",{staticClass:"column is-narrow"},[n("div",{staticClass:"or px-5 is-size-5 is-flex is-align-items-center"},[t._v("Or")])])}],!1,null,null,null);e.default=component.exports},644:function(t,e,n){"use strict";n.d(e,"a",(function(){return c}));n(22),n(57);function c(t,e){t.title.value=e.title,t.meta.value.push({hid:"description",name:"description",content:e.description},{hid:"og:title",name:"og:title",property:"og:title",content:e.title},{hid:"og:description",name:"og:description",property:"og:description",content:e.description},{hid:"twitter:title",name:"twitter:title",content:e.title},{hid:"twitter:description",name:"twitter:description",content:e.description}),e.keywords&&t.meta.value.push({hid:"keywords",name:"keywords",content:e.keywords}),e.titleTemplate&&(t.titleTemplate.value=e.titleTemplate),e.image&&t.meta.value.push({hid:"og:image",property:"og:image",content:e.image},{hid:"og:image:alt",property:"og:image:alt",content:e.title},{hid:"twitter:image",name:"twitter:image",content:e.image},{hid:"twitter:image:alt",name:"twitter:image:alt",content:e.title})}}}]);