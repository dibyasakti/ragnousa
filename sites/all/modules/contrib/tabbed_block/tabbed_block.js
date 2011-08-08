Drupal.tabbed_block = function(){
  //init tabs
  $(".tabbed-block").each(function(){
    tabbed_block_tab(this);
  });
  $(".block-tabbed_block").each(function(){
    if ( Drupal.settings.tabbed_block[ $(this).attr("id").substr(19,1) ].ajax == 1 ) {
      tabbed_block_ajax(this);
    };
    frag = tabbed_block_get_cookie($(this).attr("id"));
    if( frag ) {
      $('#'+frag).parent().trigger("click");
    }
  });
}

function tabbed_block_ajax(obj){
  //init ajax
  $(obj).children(".content").append("<a href='#' class='tabbed_block-ajax'>refresh</a>")
  
  $(obj).children(".content").children(".tabbed_block-ajax").click(function(){
  
    id = $(this).parent().parent().attr("id");
    $(this).parent().parent().addClass("tabbed_block-click");
    $(this).parent(".content").html("<i class='description'>Loading</i>");
    $.ajax({
      type: "POST",
      //base path is defined in tabbed_block.module
      url: Drupal.settings.basePath+"tabbed_block/menu",
      data: "id="+id,
      success: function (data) {
        data = Drupal.parseJson(data);
        $(".tabbed_block-click"+" .content").html( data.content );
        tabbed_block_ajax(".tabbed_block-click");
        tabbed_block_tab(".tabbed_block-click .tabbed-block");
        frag = tabbed_block_get_cookie(($(".tabbed_block-click").attr("id")));
        $(".tabbed_block-click").find(".tabbed_block-nav").children("li").eq(frag.substr(-1)).trigger("click");
        $(".tabbed_block-click").removeClass("tabbed_block-click");
      },
      error: function (){
        $(".tabbed_block-click"+" .content").html( "Sorry, there is an error occured." );
        tabs_ajax(".tabbed_block-click");
        tabs(".tabbed_block-click .tabbed-block");
        $(".tabbed_block-click").removeClass("tabbed_block-click");
      }
    });
  });
}

function tabbed_block_tab( id ){
	//add classes
	$(id).children("ul").addClass("tabbed_block-nav");
	$(id).children("ul").children("li").eq(0).addClass("tabbed_block-selected");
	
	//init clicks methods on tab-heads
	$(id).children("ul").children("li").click(function(){

      //content
      //get the clicked tab element to find the content to display
      click = $(this).children("a").attr("id");
      
      $(this).parent().siblings("div").each(function(){
        $(this).addClass("tabbed_block-hide");
        $(this).css("display","none");
      });
      
      eval( '$("#content-"+click).' + Drupal.settings.tabbed_block[click.substr(8,1)].effects );
      $("#content-"+click).removeClass("tabbed_block-hide");
  	
      // head
      $(this).addClass("tabbed_block-selected");
      $(this).siblings(".tabbed_block-selected").removeClass("tabbed_block-selected");
      
      // cookies
      tabbed_block_set_cookie( "block-tabbed_block-"+click.substr(8,1) , click );
      return false; 
	});
	
	//init tab-content
	$(id).children("div").addClass("tabbed_block-container tabbed_block-hide");
	$(id).children("div").eq(0).removeClass("tabbed_block-hide");
}

function tabbed_block_set_cookie(c_name,value,expiredays)
{
  var exdate=new Date()
  exdate.setDate(exdate.getDate()+expiredays)
  document.cookie=c_name+ "=" +escape(value)+
  ((expiredays==null) ? "" : ";expires="+exdate.toGMTString())
}

function tabbed_block_get_cookie(c_name){
  if (document.cookie.length>0)
    {
    c_start=document.cookie.indexOf(c_name + "=")
    if (c_start!=-1)
      { 
      c_start=c_start + c_name.length+1; 
      c_end=document.cookie.indexOf(";",c_start)
      if (c_end==-1) c_end=document.cookie.length
      return unescape(document.cookie.substring(c_start,c_end))
      } 
    }
  return ""
}

if (Drupal.jsEnabled) {
  $(document).ready(Drupal.tabbed_block);
}