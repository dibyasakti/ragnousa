

( function( $ ){

	
	function InitializaeExternalLinks( ){
		
		// Selects external links to open on new tab.
		$( 'a.external' ).attr( 'target', 'blank' );
		
	};
  
  function ProductFinderTitleLinks( ){
    
    //Selects all titles and anchors of the list
    var titles = $(".page-product-finder .views-field-title .field-content" );
    var anchors = $(".page-product-finder .views-field-field-product-image-fid .field-content a.imagefield" ); 
    
    //If someone clicks the title
    titles.click ( function(){
      var i = parseInt ( titles.index( $( this ) ) );
      anchors.eq( i ).trigger('click');                         
    }); 
        
  };
  
  function ProductTileLightbox(){
    $('#bottomNavClose').css({'background-color': '#803713', color: '#9eacad'});
    $('#imageDataContainer').css({'background': 'none'});
  }
	
  function InitializeUserLoginOrPasswordForm( ){
	  
	  /*$( '#user-login-form-wrapper .form-actions, #user-pass .form-submit' ).css( { outline: 'none', width: 1, height: 1, display: 'block', overflow: 'hidden', opacity: 0 } );*/
	  
  }
  
  function InitializeSeriesPage( ){
	  
	  // Activation of lightframe element when clicking title.
	  $( 'div.view-series-products .tile-title' ).click( function( ){ $( this ).prev( ).trigger( 'click' ); }  )
	  
  }
  
  function InitializeStandardPage( ){
	  
	$( '#columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
/*	$( '.section-technical-home .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	$( '.section-ragno-usa .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	
	$( '.section-why-choose-tile .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	$( '.section-sustainable-future .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	$( '.section-leed .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	$( '.section-ragno-elements .node-type-page #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	
	
	$( '.section-technical #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	

	$( '.section-pattern-designs #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	*/


	$( '.section-specifications-form #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	

	
	$( '.node-type-page #columns #sidebar-left #block-menu-menu-environment-menu li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );
	
  }
  
  function InitializeStoryPage( ){
	  
	$( '.node-type-story #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
		$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
	} );	  
	  
  }
  
  function InitializeFAQPage( ){
	  
		/*$( '.page-faq #columns #sidebar-left #block-menu-menu-standard-page-left-nav li a' ).each( function( ){
			$( this ).after( $( '<span></span>' ).html( $( this ).attr( 'title' )  ) ) ;
		} );	  */
		  
	  }  	
  
  
	function InitializePage( ){
	
		InitializaeExternalLinks( );
		ProductFinderTitleLinks( );
		InitializeUserLoginOrPasswordForm( );
		InitializeSeriesPage( );
		ProductTileLightbox();
		InitializeStandardPage( );
		InitializeStoryPage( );
		InitializeFAQPage( );
		
		
		var href = jQuery(location).attr('href');
		
		var elements = href.split('/');
		
		if(elements[5] == 'shade-variation' && elements[4] == 'technical'){
			$('.views-row-1 div').html($('.views-row-1 div').html() + '<img style="margin-top:5px;margin-left:-2px;" src ="/ragnousa/sites/default/files/V1.jpg" width="47" height="41">');	
			$('.views-row-2 div').html($('.views-row-2 div').html() + '<img style="margin-top:5px;margin-left:-2px;" src ="/ragnousa/sites/default/files/V2.jpg" width="47" height="41">');	
			$('.views-row-3 div').html($('.views-row-3 div').html() + '<img  style="margin-top:5px;margin-left:-2px;" src ="/ragnousa/sites/default/files/V3.jpg" width="47" height="41">');	
			$('.views-row-4 div').html($('.views-row-4 div').html() + '<img  style="margin-top:5px;margin-left:-2px;" src ="/ragnousa/sites/default/files/V4.jpg" width="47" height="41">');	
		}

		if(elements[5] == 'environmental-attributes' && elements[4] == 'technical'){
			$('.views-row-2').remove();
			$('.views-row-3').remove();
		
			$('.views-field-title span').html('% Minimum Pre-Consumer Recycled Content');
			$('.views-field-body div').html('Material that is diverted from the waste stream during a manufacturing process which is then bought or traded and incorporated into another manufacturing process.');
			$('.imagecache').each( function(index, Element){
				var urls = $(this).attr('src');
				urlArray = urls.split('/');
				urlArray[urlArray.length - 1]= 'recycledgeneral-mod_0.jpg';
				var newUrl = urlArray.join('/');
				$(this).attr('src',newUrl);

			});
		}
		
		
		
	};
	
	$( function( ){ InitializePage( ); 
	
		$('.pager-link').each(function(index){
			$(this).attr('href',$('.hidden',this).html());
			$('.hidden',this).html('');
		});
		$('.pager-link').mouseenter(function(){
			$('.pager-link').click(function(){
				window.location=$(this).attr('href'); 
			});		
		});
		
		if( $('#fragment0-0')){
		
      var prevURl = $(location).attr('href');;
      var substr = prevURl .split('#');
      if(substr[substr.length - 1] == 'decorative-tile'){
         $('#fragment0-1').trigger('click');
      }else{
         $('#fragment0-0').trigger('click');
      }
		}
		
		$('[id^=fragment]').each(function(){
		 $(this).html($(this).html().replace(' ','<br/>'));     

		});
		

	
	} );
	
} )( jQuery );

this.tooltip = function(){	
	/* CONFIG */		
		xOffset = 10;
		yOffset = 20;		
		// these 2 variable determine popup's distance from the cursor
		// you might want to adjust to get the right result		
	/* END CONFIG */		
	$(".tooltip").hover(function(e){	
								  
	 $("body").append("<p id='tooltip' >Ragno's state-of-the-art 3d printing technique, uses the latest in digital print technology, allowing for infinite design capabilities unique to Ragno. Ragno is the only manufacturer in the US that can do digital print up to 360 dpi, direct to tile. At this maximum resolution and with the unique grayscale printing technique, Ragno reaches finer, crisper and smoother definition for  printed designs than other digital products. A stunning palette of more than 100 square feet with no repetition, at maximum resolution, can be achieved.</p>");
		$("#tooltip")
			.css("top","440" + "px")
			.css("left",(e.pageX + yOffset) + "px")
			.fadeIn("fast");		
    },
	function(){	
		$("#tooltip").remove();
    });	
	$("#tooltip").mousemove(function(e){
		$("#tooltip")
			.css("top","440" + "px")
			.css("left",(e.pageX + yOffset) + "px");
	});			
};



// starting the script on page load
$(document).ready(function(){
	tooltip();
	
	if(document.getElementById('user-login-form-wrapper')){
	
		$('#block-menu-menu-user-interaction li.last').css('display','none');
		$('#block-menu-menu-user-interaction li').addClass('last');
		$('#block-menu-menu-user-interaction li.first').removeClass('last');

	}else{
	
		$('#block-menu-menu-user-interaction li').css('display','none');
		$('#block-menu-menu-user-interaction li.last').css('display','block');
		$('#block-menu-menu-user-interaction li.first').css('display','block');
	
	}
	
	
	/* 	
	$('.grid_6').gzoom({
			sW: 440,
			sH: 386,
			lW: 1240,
			lH: 1000,
			lighbox : false
	});
	 */	
	var imgSrc = $('.imagecache').attr('src');
	$(".grid_6").html('');
	$(".grid_6").remove();
	 /* $(".grid_6").iviewer(
		{
			src: imgSrc , 
			update_on_resize: false,
			zoom: 100,
			initCallback: function ()
			{
			   var object = this;
			   $("#in").click(function(){ object.zoom_by(1);}); 
			   $("#out").click(function(){ object.zoom_by(-1);}); 
			   $("#fit").click(function(){ object.fit();}); 
			   $("#orig").click(function(){  object.set_zoom(100); }); 
			   $("#update").click(function(){ object.update_container_info();});
						console.log(this.img_object.display_width); //works*
								 console.log(object.img_object.display_width); //getting undefined.*

			},
			

			//                       onMouseMove: function(object, coords) { },
			//                       onStartDrag: function(object, coords) { return false; }, //this image will not be dragged
			//                       onDrag: function(object, coords) { }
		});
	$(".grid_6").attr('style','overflow:hidden')
	$(".grid_6 img").attr('style','position:absolute; margin-left:320px;');	
	$(".grid_6 img").addClass('imagecache');
	$(".grid_6 img").addClass('imagecache-tile_product');
	$(".grid_6 img").attr('width','440');
	$(".grid_6 img").attr('height','386');
	//	 $(".grid_6 img").addClass
	//imagecache imagecache-tile_product width="440" height="386"
	 */
	 
	
                   $("#viewer").iviewer(
                       {
                       src: imgSrc, 
                       update_on_resize: false,
                       zoom: 98,
                       initCallback: function ()
                       {
                           var object = this;
                           $("#in").click(function(){ object.zoom_by(1);}); 
                           $("#out").click(function(){ object.zoom_by(-1);}); 
                           $("#fit").click(function(){ object.fit();}); 
                           $("#orig").click(function(){  object.set_zoom(100); }); 
                           $("#update").click(function(){ object.update_container_info();});
						            //console.log(this.img_object.display_width); //works*
									         //console.log(object.img_object.display_width); //getting undefined.*

                       },
                        onFinishLoad: function()
                        {
				$("#viewer").data('viewer').setCoords(-500,-500);
                            //this.setCoords(-0, -500);
                        }

//                       onMouseMove: function(object, coords) { },
//                       onStartDrag: function(object, coords) { return false; }, //this image will not be dragged
//                       onDrag: function(object, coords) { }
                  });


                  var iviewer = {};
                  $("#viewer2").iviewer(
                  {
                      src: "test_image2.jpg",
                      initCallback: function()
                      {
                        iviewer = this;
                      }
                  });

                  $("#chimg").click(function()
                  {
                    iviewer.loadImage("test_image.jpg");
                    return false;
                  });

                  
           
	 
	
});


