	$(window).scroll(function()
    {	
    	var h = $(window).height();
        var top = $(window).scrollTop();
    	var rFixedBox = $('#pin').prev().offset();
        var fixedTop = rFixedBox.top;		
        if(top>=fixedTop+$('#pin').prev().height())
			$('#pin').css({'position':'fixed','top': 0});		
        else
            $('#pin').css({'position':'static', 'top':0});   
    });