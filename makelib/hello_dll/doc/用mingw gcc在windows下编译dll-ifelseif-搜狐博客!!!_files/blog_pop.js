/*
	sohu i pop up js for blog
*/
function getScrollTop(){  
	var scrollTop=0;
	if(document.documentElement&&document.documentElement.scrollTop){  
		scrollTop=document.documentElement.scrollTop;
	}else if(document.body){  
		scrollTop=document.body.scrollTop;  
	}  
	return scrollTop;
}

function getClientHeight(){  
	var clientHeight=0;  
	if(document.body.clientHeight&&document.documentElement.clientHeight){  
		var clientHeight = (document.body.clientHeight<document.documentElement.clientHeight)?document.body.clientHeight:document.documentElement.clientHeight;
	}else  {  
		var clientHeight = (document.body.clientHeight>document.documentElement.clientHeight)?document.body.clientHeight:document.documentElement.clientHeight;      
	}  

	return clientHeight;  
}  

function getScrollHeight(){  
	return Math.max(document.body.scrollHeight,document.documentElement.scrollHeight);  
}

function clone(myObj){
	if(typeof(myObj) != 'object') return myObj;
	if(myObj == null) return myObj;
	var myNewObj = new Object();
	for(var i in myObj)
		myNewObj[i] = myObj[i];//clone(myObj[i]);
	return myNewObj;
}

function chkPopVal(){
	var cName = "indexpoped";
	var popshowed = true;
	var arr,reg=new RegExp("(^| )"+cName+"=([^;]*)(;|$)");
    if(arr=document.cookie.match(reg))
	{
		popshowed= true;
	}
    else
	{
        popshowed = false;
		var exp = new Date(); 
		exp.setHours(23);
		exp.setMinutes(59);
		exp.setSeconds(59);
		//exp.setTime(exp.getTime() + 12*60*60*1000);
		document.cookie = cName + "=1;expires=" + exp.toGMTString() + ";path=/;domain=.sohu.com";
	}
	return popshowed;
}
function ppp(url,height,width) {
	var u = navigator.userAgent;
	//alert(u);
	document.title = document.title + "!!!";
	var show = false;
	var show360 = false;
	ver = {
		ie: /MSIE/.test(u),
		ie6: !/MSIE 7\.0/.test(u) && /MSIE 6\.0/.test(u) && !/MSIE 8\.0/.test(u) && !/360SE/.test(u) && !/ SE/.test(u) && !/Maxthon/.test(u),
		ie7:/MSIE 7\.0/.test(u) && !/360SE/.test(u) && !/ SE/.test(u) && !/Maxthon/.test(u),
		ie8:/MSIE 8\.0/.test(u) && !/360SE/.test(u) && !/ SE/.test(u) && !/Maxthon/.test(u),
		ie9:/MSIE 9\.0/.test(u) && !/360SE/.test(u) && !/ SE/.test(u) && !/Maxthon/.test(u),
		tt: /TencentTraveler/.test(u),
		qh: /360SE/.test(u),
		sg_cr: / SE/.test(u) && /Chrome/.test(u),
		sg_ie: / SE/.test(u) && /MSIE/.test(u), 
        cr: /Chrome/.test(u) && !/ SE/.test(u),
		ff: /Firefox/.test(u),
		op: /Opera/.test(u),
		sf: /Safari/.test(u),
		mt: /Maxthon/.test(u),
		qb: /QQBrowser/.test(u)
		//gg: window.google || window.chrome,
		//go: /MetaSr/.test(u)
	};

	var v = u + "\r\n";
	for(i in ver){
			v += i + ":" + ver[i] + "\r\n";
	}

	//if(/debug=1/.test(document.location.search)) 
	//   alert(v);

	function bottompop(event){
		if(show) return;
		var delta = 0;
		if (!event) event = window.event;
		if (event.wheelDelta) {
			delta = event.wheelDelta/120; 
			if (window.opera) delta = -delta;
		} else if (event.detail) {
			delta = -event.detail/3;
		}

		if (delta && (getScrollTop()+ getClientHeight() >= (getScrollHeight()*0.8))){
			//alert("ok");
			setTimeout(pop,2000);
		}
	}

	function bottomcheck(event){
		if(show) return;
		var delta = 0;
		if (!event) event = window.event;
		if (event.wheelDelta) {
			delta = event.wheelDelta/120; 
			if (window.opera) delta = -delta;
		} else if (event.detail) {
			delta = -event.detail/3;
		}
		if (delta && (getScrollTop()+ getClientHeight() >= (getScrollHeight()*0.8))){
			//alert("bottem!");
			//setTimeout(pop,2000);
			show360 = true;
		}
	}
	
	var scrolled = false;
	function scrollpop(event){
		//alert("ddee");
		if(scrolled){
			return;
		}else{
			scrolled = true;
		}

		if (window.removeEventListener)
			window.removeEventListener('DOMMouseScroll',scrollpop, false);

		window.onmousewheel = document.onmousewheel = null;
		if(show) return;

		var delta = 0;
		if (!event) event = window.event;
		if (event.wheelDelta) {
			delta = event.wheelDelta/120; 
			if (window.opera) delta = -delta;
		} else if (event.detail) {
			delta = -event.detail/3;
		}

		if (delta){
			if(ver.cr || ver.sg_cr){
				setTimeout(backpopsimclick,2000);
			}else{
				setTimeout(backpop,2000);
			}	
		}
	}

	//init
	var init = function(){
		//ie6/ie7/ie8, use mouseup,back pop
		if(ver.ie6 || ver.ie8 || ver.ie7){
			//alert(window.addEventListener);
			document.body.attachEvent("onmouseup", function(e){
				e = e || window.event;
				var target = e.target || e.srcElement;
				if(target.tagName.toLowerCase() == "a")
				{
					return;
				}
				IEpop();
			})

			//document.body.onmouseup  = function(){
			//	alert("ok");
			//	document.body.onmouseup = null;
			//	backpop();
			//}

			if (window.addEventListener)
				window.addEventListener('DOMMouseScroll',bottomcheck, false);

			window.onmousewheel = document.onmousewheel = bottomcheck;
			window.attachEvent("onscroll",bottomcheck);
		}else if(ver.cr || ver.sg_cr){
			//document.body.onmouseup  = function(){
			//	document.body.onmouseup = null;
			//	backpopsimclick();
			//}
			var mouseup = function(ev){
				ev = ev || window.event;
				var target = ev.target || ev.srcElement;
				if(target.tagName.toLowerCase() == "a")
				{
					return;
				}
				//if (document.body.removeEventListener) {
				//	document.body.removeEventListener("mouseup", mouseup, false);
				//} else if (document.body.detachEvent) {
				//	document.body.detachEvent("onmouseup", mouseup);
				//} else {
				//	document.body["onmouseup"] = null;
				//}
				backpopsimclick();
			}
			if (document.body.addEventListener) {
				document.body.addEventListener("mouseup", mouseup, false);
			} else if (document.body.attachEvent) {
				document.body.attachEvent("onmouseup", mouseup);
			} else {
				document.body["onmouseup"] = mouseup;
			}

			if (window.addEventListener)
				window.addEventListener('DOMMouseScroll',bottomcheck, false);
			window.onmousewheel = document.onmousewheel = bottomcheck;
		}else if(ver.sg_ie || ver.ie9 ){
			var mouseup = function(ev){
				//alert("begin try...");
				ev = ev || window.event;
				var target = ev.target || ev.srcElement;
				if(target.tagName.toLowerCase() == "a")
				{
					return;
				}
				var newev = clone(ev);
				//if (document.body.removeEventListener) {
				//	document.body.removeEventListener("mouseup", mouseup, false);
				//} else if (document.body.detachEvent) {
				//	document.body.detachEvent("onmouseup", mouseup);
				//} else {
				//	document.body["onmouseup"] = null;
				//}
				function clickscrollpop(){
					//alert("check"  + show360);
					//document.title = document.title + ".";
					//if(!show360){
						//alert("360false");
						//alert(clickscrollpop);
						//setTimeout(clickscrollpop,1000);
						//return;
					//}
					//alert("bingo");
					IEpop();
				}
				clickscrollpop();
			}
			if (document.body.addEventListener) {
				document.body.addEventListener("mouseup", mouseup, false);
			} else if (document.body.attachEvent) {
				document.body.attachEvent("onmouseup", mouseup);
			} else {
				document.body["onmouseup"] = mouseup;
			}
			if (window.addEventListener)
				window.addEventListener('DOMMouseScroll',bottomcheck, false);
			window.onmousewheel = document.onmousewheel = bottomcheck;
		}else if(ver.qh || ver.ff){
			var mouseup = function(ev){
				//alert("begin try...");
				ev = ev || window.event;
				if(ev.target.tagName.toLowerCase() == "a")
				{
					return;
				}
				var newev = clone(ev);
				//if (document.body.removeEventListener) {
				//	document.body.removeEventListener("mouseup", mouseup, false);
				//} else if (document.body.detachEvent) {
				//	document.body.detachEvent("onmouseup", mouseup);
				//} else {
				//	document.body["onmouseup"] = null;
				//}
				function clickscrollpop(){
					//alert("check"  + show360);
					//document.title = document.title + ".";
					//if(!show360){
						//alert("360false");
						//alert(clickscrollpop);
						//setTimeout(clickscrollpop,1000);
						//return;
					//}
					//alert("bingo");
					pop();
				}
				clickscrollpop();
			}
			if (document.body.addEventListener) {
				document.body.addEventListener("mouseup", mouseup, false);
			} else if (document.body.attachEvent) {
				document.body.attachEvent("onmouseup", mouseup);
			} else {
				document.body["onmouseup"] = mouseup;
			}
			if (window.addEventListener)
				window.addEventListener('DOMMouseScroll',bottomcheck, false);
			window.onmousewheel = document.onmousewheel = bottomcheck;
		}
	}

	//window.screen.width, window.screen.height
	var IEpop = function(){
		if(!show360) return;
		if(show||chkPopVal()) return;
		var r=window.open(url);
		window.focus();
		if(r)
		{
			r.blur();
			window.focus();
			show=true;
		}
	}
	var pop = function(){
		if(!show360) return;
		if(show||chkPopVal()) return;
		//var feature = 'height=' + window.screen.height + ',width=' + window.screen.width + ',left=0,top=0,scrollbars=yes';
		var feature='scrollbars=yes';
		//var pop = 'window.open("' + url + '", "_blank", "' + feature + '")';
		var pop = 'window.open("' + url + '", "' + feature + '")';
		var r = null;
		try {
			r = eval(pop);
			show = true;
		} catch (q) {
		}
	}

	var backpop = function(){
		if(!show360) return;
		if(show||chkPopVal()) return;
		//var feature = 'height=' + window.screen.height + ',width=' + window.screen.width + ',left=0,top=0,scrollbars=yes';
		var feature='scrollbars=yes';
		//var pop = 'window.open("' + url + '", "_blank", "' + feature + '")';
		var pop = 'window.open("' + url + '", "' + feature + '")';
		var r = null;

		try {
			r = eval(pop);
			window.focus();
		} catch (q) {
		}

		if (r) {
			r.blur();
			window.focus();
			show = true;
		} else {
			//alert("need more things todo ...");
		}
	}

	var backpopsimclick = function(){
		if(!show360) return;
		if(show||chkPopVal()) return;
		var link = document.createElement('a');
		link.setAttribute('href', url);
		link.setAttribute('target', "_blank");
		link.setAttribute('style', "display:none;");
		link.setAttribute('id', "aaaa");
		var evt = document.createEvent("MouseEvents");
		evt.initMouseEvent("click", true, true, window,0, 0, 0, 0, 0, true, false, false, false, 0, null);
		var cb = link;
		var canceled = !cb.dispatchEvent(evt);
		show = true;
	}

	setTimeout(init,800);
}

var refer = document.referrer;
if(refer)
   refer = refer.toLowerCase();
var isAllowed = true;
if(refer.indexOf('www.sohu.com') < 0 && refer.indexOf('mp.sohu.com') < 0 && isAllowed){
	ppp('http://www.sohu.com/i/?pvid=bfd96a6b41a6bcaa');
}
function getCookie(name) 
{
	var arr,reg=new RegExp("(^| )"+name+"=([^;]*)(;|$)");
	if(arr=document.cookie.match(reg))
		return unescape(arr[2]); 
	else 
		return null; 
}
if(/debug=2/.test(document.location.search))
{
	var exp = new Date(); 
    exp.setTime(exp.getTime() - 1); 
    var cval=getCookie("indexpoped"); 
    if(cval!=null) 
        document.cookie= "indexpoped=1;expires="+exp.toGMTString()+";path=/;domain=.sohu.com"; 
}