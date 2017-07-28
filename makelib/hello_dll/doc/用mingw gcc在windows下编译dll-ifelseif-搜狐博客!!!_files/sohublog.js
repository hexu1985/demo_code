function lsl(_sl, charset) {
	if (!_sl) return;
	var ch = charset || '';
	var ss = document.getElementsByTagName('script');
	for (var i=0; i<_sl.length; i++) {
		var _sf = _sl[i];
		var _f = false;
		for (var j=0; j<ss.length; j++) {
			var _s = ss[j].getAttribute('src');
			if (_s && _s==_sf) {
				_f = true;
				break;
			}
		}
		if (!_f) {
			document.write('<script type="text/javascript"' + ' charset="' + ch + '" src="' + _sf + '"></script>');
		}
	}
}
