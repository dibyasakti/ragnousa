/*
 * jQuery Nivo Slider v2.0
 * http://nivo.dev7studios.com
 *
 * Copyright 2010, Gilbert Pellegrom
 * Free to use and abuse under the MIT license.
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * May 2010 - Pick random effect from specified set of effects by toronegro
 * May 2010 - controlNavThumbsFromRel option added by nerd-sh
 * May 2010 - Do not start nivoRun timer if there is only 1 slide by msielski
 * April 2010 - controlNavThumbs option added by Jamie Thompson (http://jamiethompson.co.uk)
 * March 2010 - manualAdvance option added by HelloPablo (http://hellopablo.co.uk)
 */

//eval(function(p,a,c,k,e,d){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--){d[e(c)]=k[c]||e(c)}k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--){if(k[c]){p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c])}}return p}('(9($){$.1f.1q=9(1X){b 3=$.2i({},$.1f.1q.2c,1X);I g.E(9(){b 4={f:0,t:\'\',U:0,o:\'\',N:m,1k:m,1N:m};b 5=$(g);5.1S(\'7:4\',4);5.e(\'2h\',\'2g\');5.1n(\'1q\');b d=5.2j();d.E(9(){b j=$(g);b 1p=\'\';6(!j.K(\'B\')){6(j.K(\'a\')){j.1n(\'7-2k\');1p=j}j=j.1g(\'B:1s\')}b 1c=j.w();6(1c==0)1c=j.s(\'w\');b 1d=j.x();6(1d==0)1d=j.s(\'x\');6(1c>5.w()){5.w(1c)}6(1d>5.x()){5.x(1d)}6(1p!=\'\'){1p.e(\'P\',\'1h\')}j.e(\'P\',\'1h\');4.U++});6(3.1a>0){6(3.1a>=4.U)3.1a=4.U-1;4.f=3.1a}6($(d[4.f]).K(\'B\')){4.t=$(d[4.f])}n{4.t=$(d[4.f]).1g(\'B:1s\')}6($(d[4.f]).K(\'a\')){$(d[4.f]).e(\'P\',\'1w\')}5.e(\'W\',\'V(\'+4.t.s(\'D\')+\') R-Y\');2b(b i=0;i<3.h;i++){b G=X.27(5.w()/3.h);6(i==3.h-1){5.J($(\'<C z="7-c"></C>\').e({21:(G*i)+\'13\',w:(5.w()-(G*i))+\'13\'}))}n{5.J($(\'<C z="7-c"></C>\').e({21:(G*i)+\'13\',w:G+\'13\'}))}}5.J($(\'<C z="7-H"><p></p></C>\').e({P:\'1h\',y:3.1Y}));6(4.t.s(\'16\')!=\'\'){$(\'.7-H p\',5).1y(4.t.s(\'16\'));$(\'.7-H\',5).1x(3.q)}b l=0;6(!3.1i&&d.1j>1){l=1v(9(){F(5,d,3,m)},3.1m)}6(3.T){5.J(\'<C z="7-T"><a z="7-2a">2f</a><a z="7-29">2m</a></C>\');6(3.2d){$(\'.7-T\',5).24();5.25(9(){$(\'.7-T\',5).2l()},9(){$(\'.7-T\',5).24()})}$(\'a.7-2a\',5).1J(\'1I\',9(){6(4.N)I m;S(l);l=\'\';4.f-=2;F(5,d,3,\'1C\')});$(\'a.7-29\',5).1J(\'1I\',9(){6(4.N)I m;S(l);l=\'\';F(5,d,3,\'1A\')})}6(3.M){b 1b=$(\'<C z="7-M"></C>\');5.J(1b);2b(b i=0;i<d.1j;i++){6(3.20){b j=d.1B(i);6(!j.K(\'B\')){j=j.1g(\'B:1s\')}6(3.1Q){1b.J(\'<a z="7-1l" 11="\'+i+\'"><B D="\'+j.s(\'11\')+\'" 28="" /></a>\')}n{1b.J(\'<a z="7-1l" 11="\'+i+\'"><B D="\'+j.s(\'D\').2n(3.1R,3.1P)+\'" 28="" /></a>\')}}n{1b.J(\'<a z="7-1l" 11="\'+i+\'">\'+i+\'</a>\')}}$(\'.7-M a:1B(\'+4.f+\')\',5).1n(\'1o\');$(\'.7-M a\',5).1J(\'1I\',9(){6(4.N)I m;6($(g).2e(\'1o\'))I m;S(l);l=\'\';5.e(\'W\',\'V(\'+4.t.s(\'D\')+\') R-Y\');4.f=$(g).s(\'11\')-1;F(5,d,3,\'1l\')})}6(3.1M){$(2q).2A(9(1L){6(1L.1Z==\'2C\'){6(4.N)I m;S(l);l=\'\';4.f-=2;F(5,d,3,\'1C\')}6(1L.1Z==\'2D\'){6(4.N)I m;S(l);l=\'\';F(5,d,3,\'1A\')}})}6(3.1T){5.25(9(){4.1k=Q;S(l);l=\'\'},9(){4.1k=m;6(l==\'\'&&!3.1i){l=1v(9(){F(5,d,3,m)},3.1m)}})}5.2E(\'7:Z\',9(){4.N=m;$(d).E(9(){6($(g).K(\'a\')){$(g).e(\'P\',\'1h\')}});6($(d[4.f]).K(\'a\')){$(d[4.f]).e(\'P\',\'1w\')}6(l==\'\'&&!4.1k&&!3.1i){l=1v(9(){F(5,d,3,m)},3.1m)}3.1U.1z(g)})});9 F(5,d,3,19){b 4=5.1S(\'7:4\');6((!4||4.1N)&&!19)I m;3.1W.1z(g);6(!19){5.e(\'W\',\'V(\'+4.t.s(\'D\')+\') R-Y\')}n{6(19==\'1C\'){5.e(\'W\',\'V(\'+4.t.s(\'D\')+\') R-Y\')}6(19==\'1A\'){5.e(\'W\',\'V(\'+4.t.s(\'D\')+\') R-Y\')}}4.f++;6(4.f==4.U){4.f=0;3.1V.1z(g)}6(4.f<0)4.f=(4.U-1);6($(d[4.f]).K(\'B\')){4.t=$(d[4.f])}n{4.t=$(d[4.f]).1g(\'B:1s\')}6(3.M){$(\'.7-M a\',5).2F(\'1o\');$(\'.7-M a:1B(\'+4.f+\')\',5).1n(\'1o\')}6(4.t.s(\'16\')!=\'\'){6($(\'.7-H\',5).e(\'P\')==\'1w\'){$(\'.7-H p\',5).22(3.q,9(){$(g).1y(4.t.s(\'16\'));$(g).1x(3.q)})}n{$(\'.7-H p\',5).1y(4.t.s(\'16\'))}$(\'.7-H\',5).1x(3.q)}n{$(\'.7-H\',5).22(3.q)}b i=0;$(\'.7-c\',5).E(9(){b G=X.27(5.w()/3.h);$(g).e({x:\'O\',y:\'0\',W:\'V(\'+4.t.s(\'D\')+\') R-Y -\'+((G+(i*G))-G)+\'13 0%\'});i++});6(3.k==\'1t\'){b 10=2G 2B("1K","14","1F","17","1E","12","1D","1r");4.o=10[X.26(X.1t()*(10.1j+1))];6(4.o==2y)4.o=\'1r\'}6(3.k.2o(\',\')!=-1){b 10=3.k.2r(\',\');4.o=$.2z(10[X.26(X.1t()*10.1j)])}4.N=Q;6(3.k==\'2p\'||3.k==\'1K\'||4.o==\'1K\'||3.k==\'14\'||4.o==\'14\'){b u=0;b i=0;b h=$(\'.7-c\',5);6(3.k==\'14\'||4.o==\'14\')h=$(\'.7-c\',5).1e();h.E(9(){b c=$(g);c.e(\'1G\',\'O\');6(i==3.h-1){L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q,\'\',9(){5.18(\'7:Z\')})},(r+u))}n{L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q)},(r+u))}u+=1u;i++})}n 6(3.k==\'2t\'||3.k==\'1F\'||4.o==\'1F\'||3.k==\'17\'||4.o==\'17\'){b u=0;b i=0;b h=$(\'.7-c\',5);6(3.k==\'17\'||4.o==\'17\')h=$(\'.7-c\',5).1e();h.E(9(){b c=$(g);c.e(\'23\',\'O\');6(i==3.h-1){L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q,\'\',9(){5.18(\'7:Z\')})},(r+u))}n{L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q)},(r+u))}u+=1u;i++})}n 6(3.k==\'1E\'||3.k==\'2u\'||4.o==\'1E\'||3.k==\'12\'||4.o==\'12\'){b u=0;b i=0;b v=0;b h=$(\'.7-c\',5);6(3.k==\'12\'||4.o==\'12\')h=$(\'.7-c\',5).1e();h.E(9(){b c=$(g);6(i==0){c.e(\'1G\',\'O\');i++}n{c.e(\'23\',\'O\');i=0}6(v==3.h-1){L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q,\'\',9(){5.18(\'7:Z\')})},(r+u))}n{L(9(){c.A({x:\'r%\',y:\'1.0\'},3.q)},(r+u))}u+=1u;v++})}n 6(3.k==\'1D\'||4.o==\'1D\'){b u=0;b i=0;$(\'.7-c\',5).E(9(){b c=$(g);b 1H=c.w();c.e({1G:\'O\',x:\'r%\',w:\'O\'});6(i==3.h-1){L(9(){c.A({w:1H,y:\'1.0\'},3.q,\'\',9(){5.18(\'7:Z\')})},(r+u))}n{L(9(){c.A({w:1H,y:\'1.0\'},3.q)},(r+u))}u+=1u;i++})}n 6(3.k==\'1r\'||4.o==\'1r\'){b i=0;$(\'.7-c\',5).E(9(){$(g).e(\'x\',\'r%\');6(i==3.h-1){$(g).A({y:\'1.0\'},(3.q*2),\'\',9(){5.18(\'7:Z\')})}n{$(g).A({y:\'1.0\'},(3.q*2))}i++})}}};$.1f.1q.2c={k:\'1t\',h:15,q:2x,1m:2w,1a:0,T:Q,2d:Q,M:Q,20:m,1Q:m,1R:\'.1O\',1P:\'2v.1O\',1M:Q,1T:Q,1i:m,1Y:0.8,1W:9(){},1U:9(){},1V:9(){}};$.1f.1e=[].1e})(2s);',62,167,'|||settings|vars|slider|if|nivo||function||var|slice|kids|css|currentSlide|this|slices||child|effect|timer|false|else|randAnim||animSpeed|100|attr|currentImage|timeBuff||width|height|opacity|class|animate|img|div|src|each|nivoRun|sliceWidth|caption|return|append|is|setTimeout|controlNav|running|0px|display|true|no|clearInterval|directionNav|totalSlides|url|background|Math|repeat|animFinished|anims|rel|sliceUpDownLeft|px|sliceDownLeft||title|sliceUpLeft|trigger|nudge|startSlide|nivoControl|childWidth|childHeight|reverse|fn|find|none|manualAdvance|length|paused|control|pauseTime|addClass|active|link|nivoSlider|fade|first|random|50|setInterval|block|fadeIn|html|call|next|eq|prev|fold|sliceUpDown|sliceUpRight|top|origWidth|click|live|sliceDownRight|event|keyboardNav|stop|jpg|controlNavThumbsReplace|controlNavThumbsFromRel|controlNavThumbsSearch|data|pauseOnHover|afterChange|slideshowEnd|beforeChange|options|captionOpacity|keyCode|controlNavThumbs|left|fadeOut|bottom|hide|hover|floor|round|alt|nextNav|prevNav|for|defaults|directionNavHide|hasClass|Prev|relative|position|extend|children|imageLink|show|Next|replace|indexOf|sliceDown|window|split|jQuery|sliceUp|sliceUpDownRight|_thumb|3000|500|undefined|trim|keypress|Array|37|39|bind|removeClass|new'.split('|'),0,{}))
/*
 * jQuery Nivo Slider v2.5.2
 * http://nivo.dev7studios.com
 *
 * Copyright 2011, Gilbert Pellegrom
 * Free to use and abuse under the MIT license.
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * March 2010
 */

(function($) {

    var NivoSlider = function(element, options){
		//Defaults are below
		var settings = $.extend({}, $.fn.nivoSlider.defaults, options);

        //Useful variables. Play carefully.
        var vars = {
            currentSlide: 0,
            currentImage: '',
            totalSlides: 0,
            randAnim: '',
            running: false,
            paused: false,
            stop: false
        };
    
        //Get this slider
        var slider = $(element);
        slider.data('nivo:vars', vars);
        slider.css('position','relative');
        slider.addClass('nivoSlider');
        
        //Find our slider children
        var kids = slider.children();
        kids.each(function() {
            var child = $(this);
            var link = '';
            if(!child.is('img')){
                if(child.is('a')){
                    child.addClass('nivo-imageLink');
                    link = child;
                }
                child = child.find('img:first');
            }
            //Get img width & height
            var childWidth = child.width();
            if(childWidth == 0) childWidth = child.attr('width');
            var childHeight = child.height();
            if(childHeight == 0) childHeight = child.attr('height');
            //Resize the slider
            if(childWidth > slider.width()){
                slider.width(childWidth);
            }
            if(childHeight > slider.height()){
                slider.height(childHeight);
            }
            if(link != ''){
                link.css('display','none');
            }
            child.css('display','none');
            vars.totalSlides++;
        });
        
        //Set startSlide
        if(settings.startSlide > 0){
            if(settings.startSlide >= vars.totalSlides) settings.startSlide = vars.totalSlides - 1;
            vars.currentSlide = settings.startSlide;
        }
        
        //Get initial image
        if($(kids[vars.currentSlide]).is('img')){
            vars.currentImage = $(kids[vars.currentSlide]);
        } else {
            vars.currentImage = $(kids[vars.currentSlide]).find('img:first');
        }
        
        //Show initial link
        if($(kids[vars.currentSlide]).is('a')){
            $(kids[vars.currentSlide]).css('display','block');
        }
        
        //Set first background
        slider.css('background','url("'+ vars.currentImage.attr('src') +'") no-repeat');

        //Create caption
        slider.append(
            $('<div class="nivo-caption"><p></p></div>').css({ display:'none', opacity:settings.captionOpacity })
        );			
		
		// Process caption function
		var processCaption = function(settings){
			var nivoCaption = $('.nivo-caption', slider);
			var overlayImage1 = '';
			var overlayImage = '';
			if(vars.currentImage.attr('title') != '' && vars.currentImage.attr('title') != undefined){
				var title = vars.currentImage.attr('title');
				if(title.substr(0,1) == '#') title = $(title).html();	
				
				
				if(title != '')
				{
					elHref = $(title);
					linkText = elHref.html();
					res = linkText.search("MADE IN THE USA");
					show3DImage = linkText.search("3D");
					if(show3DImage != -1){
					
						var top = '235px';
						var left = '8px';
						overlayImage1 = '<div id="ror"  class="views-admin-links" style="position:absolute;top:'+top+'; left:'+left+';"><img title="" class="tooltip" id="overlay3D"  src="/ragnousa/sites/default/files/3d.png"/></div>';
					
					}else{
						var overlayImage = '';
						var overlayImage1 = '';
					}
					//elHref.html().replace('3D' , '');
				
					if(res != -1){
					
						titleNew = elHref.html().replace('MADE IN THE USA' , '');  
						titleNew = titleNew.replace('3D' , '');  
						hrefText = elHref.attr('href');                        
						leftText = '<div style="float:left;width:100%;"><div style="float:left;">'+overlayImage+'<a href="#">MADE IN THE USA</a></div>';
						rightText = '<div id="title" style="float:right;"><a href="'+ hrefText +'">' + titleNew + '</a></div></div>';
						title = leftText + rightText;
					}else{
						titleNew = elHref.html().replace('MADE IN THE USA' , '');  
						titleNew = titleNew.replace('3D' , '');  
						hrefText = elHref.attr('href');                        
						leftText = '<div style="float:left;width:100%;"><div style="float:left;">'+overlayImage+'</div>';
						rightText = '<div id="title" style="float:right;"><a href="'+ hrefText +'">' + titleNew + '</a></div></div>';
						title = leftText + rightText;
					}
											
				}
				$('#columns').css('z-index','0');
				if(nivoCaption.css('display') == 'block'){
					nivoCaption.find('p').fadeOut(settings.animSpeed, function(){
						$('.nivo-slice').append(overlayImage1);
						$(this).html(title);
						$(this).fadeIn(settings.animSpeed);
						tooltip();
					});
				} else {
					$('#views-nivo-slider-series_room_images-block_1').append(overlayImage1);
					//$('.nivo-slice').append(overlayImage1);
					nivoCaption.find('p').html(title);
					nivoCaption.find('p').fadeIn(settings.animSpeed);
					tooltip();
					
				}					
				nivoCaption.fadeIn(settings.animSpeed);
				tooltip();
			} else {
			
				nivoCaption.fadeOut(settings.animSpeed);
				tooltip();
			}

		}
		
        //Process initial  caption
        processCaption(settings);
        
        //In the words of Super Mario "let's a go!"
        var timer = 0;
        if(!settings.manualAdvance && kids.length > 1){
            timer = setInterval(function(){ nivoRun(slider, kids, settings, false); }, settings.pauseTime);
        }

        //Add Direction nav
        if(settings.directionNav){
            slider.append('<div class="nivo-directionNav"><a class="nivo-prevNav">'+ settings.prevText +'</a><a class="nivo-nextNav">'+ settings.nextText +'</a></div>');
            
            //Hide Direction nav
            if(settings.directionNavHide){
                $('.nivo-directionNav', slider).hide();
                slider.hover(function(){
                    $('.nivo-directionNav', slider).show();
                }, function(){
                    $('.nivo-directionNav', slider).hide();
                });
            }
            
            $('a.nivo-prevNav', slider).live('click', function(){
                if(vars.running) return false;
                clearInterval(timer);
                timer = '';
                vars.currentSlide -= 2;
                nivoRun(slider, kids, settings, 'prev');
            });
            
            $('a.nivo-nextNav', slider).live('click', function(){
                if(vars.running) return false;
                clearInterval(timer);
                timer = '';
                nivoRun(slider, kids, settings, 'next');
            });
        }
        
        //Add Control nav
        if(settings.controlNav){
            var nivoControl = $('<div class="nivo-controlNav"></div>');
            slider.append(nivoControl);
            for(var i = 0; i < kids.length; i++){
                if(settings.controlNavThumbs){
                    var child = kids.eq(i);
                    if(!child.is('img')){
                        child = child.find('img:first');
                    }
                    if (settings.controlNavThumbsFromRel) {
                        nivoControl.append('<a class="nivo-control" rel="'+ i +'"><img src="'+ child.attr('rel') + '" alt="" /></a>');
                    } else {
                        nivoControl.append('<a class="nivo-control" rel="'+ i +'"><img src="'+ child.attr('src').replace(settings.controlNavThumbsSearch, settings.controlNavThumbsReplace) +'" alt="" /></a>');
                    }
                } else {
                    nivoControl.append('<a class="nivo-control" rel="'+ i +'">'+ (i + 1) +'</a>');
                }
                
            }
            //Set initial active link
            $('.nivo-controlNav a:eq('+ vars.currentSlide +')', slider).addClass('active');
            
            $('.nivo-controlNav a', slider).live('click', function(){
                if(vars.running) return false;
                if($(this).hasClass('active')) return false;
                clearInterval(timer);
                timer = '';
                slider.css('background','url("'+ vars.currentImage.attr('src') +'") no-repeat');
                vars.currentSlide = $(this).attr('rel') - 1;
                nivoRun(slider, kids, settings, 'control');
            });
        }
        
        //Keyboard Navigation
        if(settings.keyboardNav){
            $(window).keypress(function(event){
                //Left
                if(event.keyCode == '37'){
                    if(vars.running) return false;
                    clearInterval(timer);
                    timer = '';
                    vars.currentSlide-=2;
                    nivoRun(slider, kids, settings, 'prev');
                }
                //Right
                if(event.keyCode == '39'){
                    if(vars.running) return false;
                    clearInterval(timer);
                    timer = '';
                    nivoRun(slider, kids, settings, 'next');
                }
            });
        }
        
        //For pauseOnHover setting
        if(settings.pauseOnHover){
            slider.hover(function(){
                vars.paused = true;
                clearInterval(timer);
                timer = '';
            }, function(){
                vars.paused = false;
                //Restart the timer
                if(timer == '' && !settings.manualAdvance){
                    timer = setInterval(function(){ nivoRun(slider, kids, settings, false); }, settings.pauseTime);
                }
            });
        }
        
        //Event when Animation finishes
        slider.bind('nivo:animFinished', function(){ 
            vars.running = false; 
            //Hide child links
            $(kids).each(function(){
                if($(this).is('a')){
                    $(this).css('display','none');
                }
            });
            //Show current link
            if($(kids[vars.currentSlide]).is('a')){
                $(kids[vars.currentSlide]).css('display','block');
            }
            //Restart the timer
            if(timer == '' && !vars.paused && !settings.manualAdvance){
                timer = setInterval(function(){ nivoRun(slider, kids, settings, false); }, settings.pauseTime);
            }
            //Trigger the afterChange callback
            settings.afterChange.call(this);
        });
        
        // Add slices for slice animations
        var createSlices = function(slider, settings, vars){
            for(var i = 0; i < settings.slices; i++){
				var sliceWidth = Math.round(slider.width()/settings.slices);
				if(i == settings.slices-1){
					slider.append(
						$('<div class="nivo-slice"></div>').css({ 
							left:(sliceWidth*i)+'px', width:(slider.width()-(sliceWidth*i))+'px',
							height:'0px', 
							opacity:'0', 
							background: 'url("'+ vars.currentImage.attr('src') +'") no-repeat -'+ ((sliceWidth + (i * sliceWidth)) - sliceWidth) +'px 0%'
						})
					);
				} else {
					slider.append(
						$('<div class="nivo-slice"></div>').css({ 
							left:(sliceWidth*i)+'px', width:sliceWidth+'px',
							height:'0px', 
							opacity:'0', 
							background: 'url("'+ vars.currentImage.attr('src') +'") no-repeat -'+ ((sliceWidth + (i * sliceWidth)) - sliceWidth) +'px 0%'
						})
					);
				}
			}
        }
		
		// Add boxes for box animations
		var createBoxes = function(slider, settings, vars){
			var boxWidth = Math.round(slider.width()/settings.boxCols);
			var boxHeight = Math.round(slider.height()/settings.boxRows);
			
			for(var rows = 0; rows < settings.boxRows; rows++){
				for(var cols = 0; cols < settings.boxCols; cols++){
					if(cols == settings.boxCols-1){
						slider.append(
							$('<div class="nivo-box"></div>').css({ 
								opacity:0,
								left:(boxWidth*cols)+'px', 
								top:(boxHeight*rows)+'px',
								width:(slider.width()-(boxWidth*cols))+'px',
								height:boxHeight+'px',
								background: 'url("'+ vars.currentImage.attr('src') +'") no-repeat -'+ ((boxWidth + (cols * boxWidth)) - boxWidth) +'px -'+ ((boxHeight + (rows * boxHeight)) - boxHeight) +'px'
							})
						);
					} else {
						slider.append(
							$('<div class="nivo-box"></div>').css({ 
								opacity:0,
								left:(boxWidth*cols)+'px', 
								top:(boxHeight*rows)+'px',
								width:boxWidth+'px',
								height:boxHeight+'px',
								background: 'url("'+ vars.currentImage.attr('src') +'") no-repeat -'+ ((boxWidth + (cols * boxWidth)) - boxWidth) +'px -'+ ((boxHeight + (rows * boxHeight)) - boxHeight) +'px'
							})
						);
					}
				}
			}
		}

        // Private run method
		var nivoRun = function(slider, kids, settings, nudge){
			//Get our vars
			var vars = slider.data('nivo:vars');
            
            //Trigger the lastSlide callback
            if(vars && (vars.currentSlide == vars.totalSlides - 1)){ 
				settings.lastSlide.call(this);
			}
            
            // Stop
			if((!vars || vars.stop) && !nudge) return false;
			
			//Trigger the beforeChange callback
			settings.beforeChange.call(this);
					
			//Set current background before change
			if(!nudge){
				slider.css('background','url("'+ vars.currentImage.attr('src') +'") no-repeat');
			} else {
				if(nudge == 'prev'){
					slider.css('background','url("'+ vars.currentImage.attr('src') +'") no-repeat');
				}
				if(nudge == 'next'){
					slider.css('background','url("'+ vars.currentImage.attr('src') +'") no-repeat');
				}
			}
			vars.currentSlide++;
            //Trigger the slideshowEnd callback
			if(vars.currentSlide == vars.totalSlides){ 
				vars.currentSlide = 0;
				settings.slideshowEnd.call(this);
			}
			if(vars.currentSlide < 0) vars.currentSlide = (vars.totalSlides - 1);
			//Set vars.currentImage
			if($(kids[vars.currentSlide]).is('img')){
				vars.currentImage = $(kids[vars.currentSlide]);
			} else {
				vars.currentImage = $(kids[vars.currentSlide]).find('img:first');
			}
			
			//Set active links
			if(settings.controlNav){
				$('.nivo-controlNav a', slider).removeClass('active');
				$('.nivo-controlNav a:eq('+ vars.currentSlide +')', slider).addClass('active');
			}
			
			//Process caption
			processCaption(settings);
			
			// Remove any slices from last transition
			$('.nivo-slice', slider).remove();
			
			// Remove any boxes from last transition
			$('.nivo-box', slider).remove();
			
			if(settings.effect == 'random'){
				var anims = new Array('sliceDownRight','sliceDownLeft','sliceUpRight','sliceUpLeft','sliceUpDown','sliceUpDownLeft','fold','fade',
                'boxRandom','boxRain','boxRainReverse','boxRainGrow','boxRainGrowReverse');
				vars.randAnim = anims[Math.floor(Math.random()*(anims.length + 1))];
				if(vars.randAnim == undefined) vars.randAnim = 'fade';
			}
            
            //Run random effect from specified set (eg: effect:'fold,fade')
            if(settings.effect.indexOf(',') != -1){
                var anims = settings.effect.split(',');
                vars.randAnim = anims[Math.floor(Math.random()*(anims.length))];
				if(vars.randAnim == undefined) vars.randAnim = 'fade';
            }
		
			//Run effects
			vars.running = true;
			if(settings.effect == 'sliceDown' || settings.effect == 'sliceDownRight' || vars.randAnim == 'sliceDownRight' ||
				settings.effect == 'sliceDownLeft' || vars.randAnim == 'sliceDownLeft'){
				createSlices(slider, settings, vars);
				var timeBuff = 0;
				var i = 0;
				var slices = $('.nivo-slice', slider);
				if(settings.effect == 'sliceDownLeft' || vars.randAnim == 'sliceDownLeft') slices = $('.nivo-slice', slider)._reverse();
				
				slices.each(function(){
					var slice = $(this);
					slice.css({ 'top': '0px' });
					if(i == settings.slices-1){
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed, '', function(){ slider.trigger('nivo:animFinished'); });
						}, (100 + timeBuff));
					} else {
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed);
						}, (100 + timeBuff));
					}
					timeBuff += 50;
					i++;
				});
			} 
			else if(settings.effect == 'sliceUp' || settings.effect == 'sliceUpRight' || vars.randAnim == 'sliceUpRight' ||
					settings.effect == 'sliceUpLeft' || vars.randAnim == 'sliceUpLeft'){
				createSlices(slider, settings, vars);
				var timeBuff = 0;
				var i = 0;
				var slices = $('.nivo-slice', slider);
				if(settings.effect == 'sliceUpLeft' || vars.randAnim == 'sliceUpLeft') slices = $('.nivo-slice', slider)._reverse();
				
				slices.each(function(){
					var slice = $(this);
					slice.css({ 'bottom': '0px' });
					if(i == settings.slices-1){
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed, '', function(){ slider.trigger('nivo:animFinished'); });
						}, (100 + timeBuff));
					} else {
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed);
						}, (100 + timeBuff));
					}
					timeBuff += 50;
					i++;
				});
			} 
			else if(settings.effect == 'sliceUpDown' || settings.effect == 'sliceUpDownRight' || vars.randAnim == 'sliceUpDown' || 
					settings.effect == 'sliceUpDownLeft' || vars.randAnim == 'sliceUpDownLeft'){
				createSlices(slider, settings, vars);
				var timeBuff = 0;
				var i = 0;
				var v = 0;
				var slices = $('.nivo-slice', slider);
				if(settings.effect == 'sliceUpDownLeft' || vars.randAnim == 'sliceUpDownLeft') slices = $('.nivo-slice', slider)._reverse();
				
				slices.each(function(){
					var slice = $(this);
					if(i == 0){
						slice.css('top','0px');
						i++;
					} else {
						slice.css('bottom','0px');
						i = 0;
					}
					
					if(v == settings.slices-1){
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed, '', function(){ slider.trigger('nivo:animFinished'); });
						}, (100 + timeBuff));
					} else {
						setTimeout(function(){
							slice.animate({ height:'100%', opacity:'1.0' }, settings.animSpeed);
						}, (100 + timeBuff));
					}
					timeBuff += 50;
					v++;
				});
			} 
			else if(settings.effect == 'fold' || vars.randAnim == 'fold'){
				createSlices(slider, settings, vars);
				var timeBuff = 0;
				var i = 0;
				
				$('.nivo-slice', slider).each(function(){
					var slice = $(this);
					var origWidth = slice.width();
					slice.css({ top:'0px', height:'100%', width:'0px' });
					if(i == settings.slices-1){
						setTimeout(function(){
							slice.animate({ width:origWidth, opacity:'1.0' }, settings.animSpeed, '', function(){ slider.trigger('nivo:animFinished'); });
						}, (100 + timeBuff));
					} else {
						setTimeout(function(){
							slice.animate({ width:origWidth, opacity:'1.0' }, settings.animSpeed);
						}, (100 + timeBuff));
					}
					timeBuff += 50;
					i++;
				});
			}  
			else if(settings.effect == 'fade' || vars.randAnim == 'fade'){
				createSlices(slider, settings, vars);
				
				var firstSlice = $('.nivo-slice:first', slider);
                firstSlice.css({
                    'height': '100%',
                    'width': slider.width() + 'px'
                });
    
				firstSlice.animate({ opacity:'1.0' }, (settings.animSpeed*2), '', function(){ slider.trigger('nivo:animFinished'); });
			}          
            else if(settings.effect == 'slideInRight' || vars.randAnim == 'slideInRight'){
				createSlices(slider, settings, vars);
				
                var firstSlice = $('.nivo-slice:first', slider);
                firstSlice.css({
                    'height': '100%',
                    'width': '0px',
                    'opacity': '1'
                });

                firstSlice.animate({ width: slider.width() + 'px' }, (settings.animSpeed*2), '', function(){ slider.trigger('nivo:animFinished'); });
            }
            else if(settings.effect == 'slideInLeft' || vars.randAnim == 'slideInLeft'){
				createSlices(slider, settings, vars);
				
                var firstSlice = $('.nivo-slice:first', slider);
                firstSlice.css({
                    'height': '100%',
                    'width': '0px',
                    'opacity': '1',
                    'left': '',
                    'right': '0px'
                });

                firstSlice.animate({ width: slider.width() + 'px' }, (settings.animSpeed*2), '', function(){ 
                    // Reset positioning
                    firstSlice.css({
                        'left': '0px',
                        'right': ''
                    });
                    slider.trigger('nivo:animFinished'); 
                });
            }
			else if(settings.effect == 'boxRandom' || vars.randAnim == 'boxRandom'){
				createBoxes(slider, settings, vars);
				
				var totalBoxes = settings.boxCols * settings.boxRows;
				var i = 0;
				var timeBuff = 0;
				
				var boxes = shuffle($('.nivo-box', slider));
				boxes.each(function(){
					var box = $(this);
					if(i == totalBoxes-1){
						setTimeout(function(){
							box.animate({ opacity:'1' }, settings.animSpeed, '', function(){ slider.trigger('nivo:animFinished'); });
						}, (100 + timeBuff));
					} else {
						setTimeout(function(){
							box.animate({ opacity:'1' }, settings.animSpeed);
						}, (100 + timeBuff));
					}
					timeBuff += 20;
					i++;
				});
			}
			else if(settings.effect == 'boxRain' || vars.randAnim == 'boxRain' || settings.effect == 'boxRainReverse' || vars.randAnim == 'boxRainReverse' || 
                    settings.effect == 'boxRainGrow' || vars.randAnim == 'boxRainGrow' || settings.effect == 'boxRainGrowReverse' || vars.randAnim == 'boxRainGrowReverse'){
				createBoxes(slider, settings, vars);
				
				var totalBoxes = settings.boxCols * settings.boxRows;
				var i = 0;
				var timeBuff = 0;
				
				// Split boxes into 2D array
				var rowIndex = 0;
				var colIndex = 0;
				var box2Darr = new Array();
				box2Darr[rowIndex] = new Array();
				var boxes = $('.nivo-box', slider);
				if(settings.effect == 'boxRainReverse' || vars.randAnim == 'boxRainReverse' ||
                   settings.effect == 'boxRainGrowReverse' || vars.randAnim == 'boxRainGrowReverse'){
					boxes = $('.nivo-box', slider)._reverse();
				}
				boxes.each(function(){
					box2Darr[rowIndex][colIndex] = $(this);
					colIndex++;
					if(colIndex == settings.boxCols){
						rowIndex++;
						colIndex = 0;
						box2Darr[rowIndex] = new Array();
					}
				});
				
				// Run animation
				for(var cols = 0; cols < (settings.boxCols * 2); cols++){
					var prevCol = cols;
					for(var rows = 0; rows < settings.boxRows; rows++){
						if(prevCol >= 0 && prevCol < settings.boxCols){
							/* Due to some weird JS bug with loop vars 
							being used in setTimeout, this is wrapped
							with an anonymous function call */
							(function(row, col, time, i, totalBoxes) {
								var box = $(box2Darr[row][col]);
                                var w = box.width();
                                var h = box.height();
                                if(settings.effect == 'boxRainGrow' || vars.randAnim == 'boxRainGrow' ||
                                   settings.effect == 'boxRainGrowReverse' || vars.randAnim == 'boxRainGrowReverse'){
                                    box.width(0).height(0);
                                }
								if(i == totalBoxes-1){
									setTimeout(function(){
										box.animate({ opacity:'1', width:w, height:h }, settings.animSpeed/1.3, '', function(){ slider.trigger('nivo:animFinished'); });
									}, (100 + time));
								} else {
									setTimeout(function(){
										box.animate({ opacity:'1', width:w, height:h }, settings.animSpeed/1.3);
									}, (100 + time));
								}
							})(rows, prevCol, timeBuff, i, totalBoxes);
							i++;
						}
						prevCol--;
					}
					timeBuff += 100;
				}
			}
		}
		
		// Shuffle an array
		var shuffle = function(arr){
			for(var j, x, i = arr.length; i; j = parseInt(Math.random() * i), x = arr[--i], arr[i] = arr[j], arr[j] = x);
			return arr;
		}
        
        // For debugging
        var trace = function(msg){
            if (this.console && typeof console.log != "undefined")
                console.log(msg);
        }
        
        // Start / Stop
        this.stop = function(){
            if(!$(element).data('nivo:vars').stop){
                $(element).data('nivo:vars').stop = true;
                trace('Stop Slider');
            }
        }
        
        this.start = function(){
            if($(element).data('nivo:vars').stop){
                $(element).data('nivo:vars').stop = false;
                trace('Start Slider');
            }
        }
        
        //Trigger the afterLoad callback
        settings.afterLoad.call(this);
		
		return this;
    };
        
    $.fn.nivoSlider = function(options) {
    
        return this.each(function(key, value){
            var element = $(this);
            // Return early if this element already has a plugin instance
            if (element.data('nivoslider')) return element.data('nivoslider');
            // Pass options to plugin constructor
            var nivoslider = new NivoSlider(this, options);
            // Store plugin object in this element's data
            element.data('nivoslider', nivoslider);
        });

	};
	
	//Default settings
	$.fn.nivoSlider.defaults = {
		effect: 'random',
		slices: 15,
		boxCols: 8,
		boxRows: 4,
		animSpeed: 500,
		pauseTime: 3000,
		startSlide: 0,
		directionNav: true,
		directionNavHide: true,
		controlNav: true,
		controlNavThumbs: false,
        controlNavThumbsFromRel: false,
		controlNavThumbsSearch: '.jpg',
		controlNavThumbsReplace: '_thumb.jpg',
		keyboardNav: true,
		pauseOnHover: true,
		manualAdvance: false,
		captionOpacity: 0.8,
		prevText: 'Prev',
		nextText: 'Next',
		beforeChange: function(){},
		afterChange: function(){},
		slideshowEnd: function(){},
        lastSlide: function(){},
        afterLoad: function(){}
	};
	
	$.fn._reverse = [].reverse;
	
})(jQuery);