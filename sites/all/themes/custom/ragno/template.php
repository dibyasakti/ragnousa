<?php

function ragno_theme(&$existing, $type, $theme, $path) {

    // Current theme path.
    $path = drupal_get_path('theme', 'ragno');

    // Theme overrides and new themable elements.
    return array(
        'user_login' => array(
            'arguments' => array('form' => NULL),
            'path' => "{$path}/templates/general",
            'template' => 'user-login',
        ),
        'user_pass' => array(
            'arguments' => array('form' => NULL),
            'path' => "{$path}/templates/general",
            'template' => 'user-recover',
        ),
    );
}

function ragno_preprocess_user_pass(&$vars) {

    // Changes field title.
    $vars['form']['name']['#title'] = 'Username';
}

function ragno_preprocess_user_login(&$vars) {

    // Removes descriptions, as we don't need them.
    unset($vars['form']['name']['#description']);
    unset($vars['form']['pass']['#description']);

    // Changes title of username field.
    $vars['form']['name']['#title'] = 'Username';

    // Wraps submit button.
    //$vars['form']['submit']['#prefix'] = '<div class="form-actions">';
    //$vars['form']['submit']['#suffix'] = '</div>';
}

function ragno_preprocess_block(&$vars) {

    // Preprocesses based on region.
    if (function_exists($func = "ragno_preprocess_block_" . $vars['block']->region)) {
        $func($vars);
    }
}

function ragno_preprocess_block_content_top(&$vars) {

    switch ($vars['block']->delta) {

        // Rotator
        case 'home_rotator-block_2':
            $vars['block']->grid = 'grid_9';
            break;

        // Featured blocks right.
        case 'e8426cee27c5cd95b3cb3920bd0b13dd';
            $vars['block']->grid = 'grid_3';
            break;

        // Featured blocks right.
        case 'f5d07559fdf0555ae2b73fac18c19fc8';
            $vars['block']->grid = 'grid_12';
            break;

        // For home owners top left.
        case '764923929d0c7d27335006efb544952d':
            $vars['block']->grid = 'grid_6 alpha TopLeftFeatured';
            break;

        // For home owners top right.
        case 'adcc5ee7257cf6900d04da76ce6c6ba3':
            $vars['block']->grid = 'grid_6 omega HomeOwnerFeatured HomeOwnerFeaturedTopRight';
            break;

        // For professionals bottom.
        case '58a45cb96ec42bb5d9b53b8fbb4ddf01':
        case '83e663a14b2414bb92a866fbfb26574b':
            $vars['block']->grid = 'grid_12 alpha omega BottomFeatured';
            break;

        // Professionals top left.
        case '692cdb41937de43a05e1215bff1d10c3':
            $vars['block']->grid = 'grid_3 alpha ProfessionalFeatured ProfessionalFeaturedTopLeft';
            break;

        // Professionals top center.
        case '24f13613e129acf0ac336a99191b69ea':
            $vars['block']->grid = 'grid_6 ProfessionalFeatured ProfessionalFeaturedTopCenter';
            break;

        // Professionals top right.
        case '541f10e1da0c2a4087809ff71ee6510a':
            $vars['block']->grid = 'grid_3 omega ProfessionalFeatured ProfessionalFeaturedTopRight';
            break;

        // Environment top left.
        case '988fe8b80131db0ec8bd27603b25128a';
            $vars['block']->grid = 'grid_6 alpha EnvironmentFeatured EnvironmentFeaturedTop EnvironmentFeaturedTopLeft';
            break;

        // Environment top right.
        case '2d3ae114cc63e78b6446833a2bb9fa3e';
            $vars['block']->grid = 'grid_6 omega EnvironmentFeatured EnvironmentFeaturedTop EnvironmentFeaturedTopRight';
            break;

        // Environment bottom left.
        case '80a3c1edc2999cf1ffefaf4ad4019a57':
            $vars['block']->grid = 'grid_9 alpha EnvironmentFeatured EnvironmentFeaturedBottom EnvironmentFeaturedBottomLeft';
            break;

        // Environment bottom right.
        case '7502c4c584dd8aa31fb5194c7181fd36':
            $vars['block']->grid = 'grid_3 omega EnvironmentFeatured EnvironmentBottom EnvironmentFeaturedBottomRight';
            break;

        // Who is RAGNO top.
        case '22e9c5b23fc786ae4cdc3d540f064344':
          $vars['block']->grid = 'grid_12 alpha omega WhoRAGNOFeatured WhoRAGNOFeaturedTop';
          break;

        // Who is RAGNO bottom left.
        case '1c7c348c0283dfccdd2d7c4984f492a1':
          $vars['block']->grid = 'grid_9 alpha WhoRAGNOFeatured WhoRAGNOFeaturedBottom WhoRAGNOFeaturedBottomLeft';
          break;
          
        // Who is RAGNO bottom left.
        case '7c17791fcfc8f96b138ffd93eb3347a1':
          $vars['block']->grid = 'grid_3 omega WhoRAGNOFeatured WhoRAGNOFeaturedBottom WhoRAGNOFeaturedBottomRight';
          break;   
          
        // Who is Why Tile top left
        case '5ae1fbbb900c4918b303fa889e3f71b8':
          $vars['block']->grid = 'grid_6 alpha WhyTileFeatured WhyTileFeaturedFeaturedTop WhyTileFeaturedFeaturedTopLeft';
          break;             
          
        // Who is Why Tile top right
        case '163b156b1253517b27527561df31d95a':
          $vars['block']->grid = 'grid_6 omega WhyTileFeatured WhyTileFeaturedFeaturedTop WhyTileFeaturedFeaturedTopRight';
          break;             
                    
        // Who is Why Tile bottom
        case 'eec226e0e7a06be3078c87eb221ddc9d':
          $vars['block']->grid = 'grid_12 alpha omega WhyTileFeatured WhyTileFeaturedFeaturedBottom';
          break;            
                    
    }
    
}

function ragno_preprocess_node(&$vars) {

    // Gets the node reference
    $n = $vars['node'];

// Array with Node classes
    $nodeclasses = array('node', 'node' . str_replace(' ', '', ucwords(str_replace('_', ' ', str_replace('-', ' ', $n->type)))));
    if ($vars['sticky']) {
        $nodeclasses[] = 'sticky';
    }
    if (!$vars['status']) {
        $nodeclasses[] = 'node-unpublished';
    }

    // Depending on node type...
    switch ($n->type) {

        case 'tile_series':

            // List to theme.
            $list = array();
            $count = 0;
 
            //For each obtained element...
             foreach( $n->field_sizes as $key => $value ){
              $info = $value['value'];
              $zebra = ($count % 2) ? 'odd' : 'even';
              $list[ ] = array( 'data' => "{$info}" , 'class' => "{$zebra}" );
              $count++;
              } 

            // Themes elements.
            $searches = theme('item_list', $list, null, 'ul');
            $vars['sizes_list'] = $searches; 

            // Defines template var.
            $vars['featured_icons'] = '<!-- No Associated Icons -->';

            // If there are associated icons...
            if ($n->field_associated_icons[0]['nid']) {

                // Element list.
                $list = array();
                $i = 0;

                // For each icon...
                foreach ($n->field_associated_icons as $icon) {

                    // Loads icon.
                    $icon = node_load($icon['nid']);
                    $list[] = '<div class="icon icon-' . ( ( $i % 5 ) + 1 ) . '">' . theme('image', $icon->field_icon_image[0]['filepath'], $icon->title, $icon->title) . '<span>' . str_replace('-', ' ', $icon->title) . '</span>' . '</div>';
                    $i++;
                }

                // Cleans markup.
                $vars['content'] = check_markup($n->content['body']['#value'], $n->format, false);

                // Replaces default content.
                $vars['featured_icons'] = theme('item_list', $list, null, 'ul');

                foreach($n->taxonomy as $term){
                    if($term->vid == 8) {
                        $vars['technology_type'] = $term->name;
                        break;
                    }
                }

            }

            break;

        case 'tile_product':

            // List to theme.
            $list = array();

            //For each obtained element...
            /*foreach ($n->field_sizes as $f) {
                $list[] = array('data' => $f['value']);
            }

            // Themes elements.
            $sizes = theme('item_list', $list, null, 'ul');*/

            // If there is data.
            if( $n->field_code_and_size[ 'data' ] ){
            
              foreach ($n->field_code_and_size['data'] as $row ) {
                  if($row[0] && $row[1])
                      $list[] = array('data' => $row[0] . " - " . $row[1]);
              } 

            }
            
            // Themes size list.
            $sizes = theme('item_list', $list, null, 'ul');
            $vars['sizes'] = $sizes;

            //$vars['featured_iconos'] = theme('blocks', 'left_icons');
				    // If there are associated icons...
            if ($n->field_associated_icons[0]['nid']) {

                // Element list.
                $list = array();
                $i = 0;

                // For each icon...
                foreach ($n->field_associated_icons as $icon) {

                    // Loads icon.
                    $icon = node_load($icon['nid']);
                    $list[] = '<div class="icon icon-' . ( ( $i % 5 ) + 1 ) . '">' . theme('image', $icon->field_icon_image[0]['filepath'], $icon->title, $icon->title) . '<span>' . str_replace('-', ' ', $icon->title) . '</span>' . '</div>';
                    $i++;
                }

                // Cleans markup.
                $vars['content'] = check_markup($n->content['body']['#value'], $n->format, false);

                // Replaces default content.
                $vars['featured_icons'] = theme('item_list', $list, null, 'ul');
            }
            
            $technologies = array( );
            $productTypes = array( );
            
            // Taxonomies.
            foreach( $n->taxonomy as $t ){
            
              // Techonology type
              if( $t->vid == 8 ){
                $technologies[ ] = $t->name;
              }else if( $t->vid == 1 ){
                $productTypes[ ] = $t->name; 
              }              
              
            }
            
            // Adds them to template.
            $vars[ 'technology' ] = theme( 'item_list', $technologies, null, 'ul' );
            $vars[ 'application' ] = theme( 'item_list', $productTypes, null, 'ul' );
            
            
            break;

        case 'webform':
            $nodeclasses[] = 'clearfix';
            break;
    }

    // Applied node classes
    $vars['nodeclasses'] = join(' ', $nodeclasses);

    // If content is being displayed in a lightbox, the admin menu is disabled.
    if (arg(2) == 'lightbox2') {
        admin_menu_suppress(true);
    }
}

function ragno_preprocess_page(&$vars) {

    // If it is the user registration page...
    if (arg(0) == 'user' && arg(1) == 'register') {
        drupal_goto('register', null, null, 301);
    }

    // If this is a node page, adds a specific page template.
    if ($vars['node']) {

      $vars['template_files'][] = "page-{$vars['node']->type}";
    
      // We assign a special class for pages that are not the front. This in order to style the left menu.
      if( !$vars[ 'is_front' ] && $vars[ 'node' ]->type == 'page' && !$vars[ 'content_top' ] ){
        $vars[ 'classes' ] .= ' page-not-front-no-top';  
        
        // If it is a page inside technical section.
        if( arg( 0, $_REQUEST[ 'q' ] ) == 'technical' ){
        
          $vars[ 'title' ] = t( 'Technical Information' );
          $vars[ 'content' ] = '<h2>' . drupal_get_title( ) . '</h2>' . $vars[ 'content' ];
          
        }
        
      }
    
    }

    // If user login or remember password page...
    if (arg(0) == 'user' && (!arg(1) || arg(1) == 'password' )) {

        // Removes tabs. This will only get in the way of our navigation scheme, at least for this section.
        unset($vars['tabs']);

        // Creates list and appends it to content.
        $vars['content'] .= '<div class="clearfix">' . $vars['user_links'] . '</div>';
    
    }
    
    
}

function ragno_views_mini_pager($tags = array(), $limit = 10, $element = 0, $parameters = array(), $quantity = 9) {
    global $pager_page_array, $pager_total;

    // Calculate various markers within this pager piece:
    // Middle is used to "center" pages around the current page.
    $pager_middle = ceil($quantity / 2);
    // current is the page we are currently paged to
    $pager_current = $pager_page_array[$element] + 1;
    // max is the maximum page number
    $pager_max = $pager_total[$element];
    // End of marker calculations.


    $li_previous = theme('pager_previous', (isset($tags[1]) ? $tags[1] : t('��')), $limit, $element, 1, $parameters);
    if (empty($li_previous)) {
        $li_previous = "&nbsp;";
    }

    $li_next = theme('pager_next', (isset($tags[3]) ? $tags[3] : t('��')), $limit, $element, 1, $parameters);
    if (empty($li_next)) {
        $li_next = "&nbsp;";
    }

    if ($pager_total[$element] > 1) {
        $items[] = array(
            'class' => 'pager-previous',
            'data' => $li_previous,
        );

        $items[] = array(
            'class' => 'pager-current',
            'data' => t('<div>Page</div><div class="center-info"><span>@current</span></div><div> of @max</div>', array('@current' => $pager_current, '@max' => $pager_max)),
        );

        $items[] = array(
            'class' => 'pager-next',
            'data' => $li_next,
        );
        return theme('item_list', $items, NULL, 'ul', array('class' => 'pager'));
    }
    
}

function ragno_preprocess_views_view_list( &$vars ){

  // Defines function names.
  $funcDisplay = "_ragno_preprocess_views_view_list_{$vars[ 'view' ]->name}_{$vars[ 'view' ]->current_display}";
  
  // Checks if specific function for template exists, otherwise checks if default name exists.
  if( function_exists( $funcDisplay ) ){
    $funcDisplay( $vars );
  }
  
}

/**
 * Who is RAGNO page display at top needs 2 columns, each 6 grids in length.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_8( &$vars ){

  // 6 column width grid.
  foreach( $vars[ 'classes' ] as &$c ){
    $c .= ' grid_6';
  }
  
  // First and last.
  $vars[ 'classes' ][ 0 ] .= ' alpha';
  $vars[ 'classes' ][ sizeof( $vars[ 'classes' ] ) - 1 ] .= ' omega';  
  
}

/**
 * Home owner block display at top right needs 2 columns, each 3 grids in width.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_2( &$vars ){

  // 3 column width grid.
  foreach( $vars[ 'classes' ] as &$c ){
    $c .= ' grid_3';
  }
  
  // First and last.
  $vars[ 'classes' ][ 0 ] .= ' alpha';
  $vars[ 'classes' ][ sizeof( $vars[ 'classes' ] ) - 1 ] .= ' omega';    

}

/**
 * Home owner block display at bottom needs 2 columns, each 3 grids in width.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_5( &$vars ){

  // We need exactly the same characteristics of block 2.  
  _ragno_preprocess_views_view_list_series_type_featured_blocks_block_2( $vars );
  
}

/**
 * Who is RAGNO block display at top needs 2 columns, each 3 grids in width.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_6( &$vars ){

  // We need exactly the same characteristics of block 2.  
  _ragno_preprocess_views_view_list_series_type_featured_blocks_block_2( $vars );
  
}


/**
 * Who is RAGNO block display at top needs 2 columns, each 3 grids in width.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_12( &$vars ){

  // We need exactly the same characteristics of block 2.  
  _ragno_preprocess_views_view_list_series_type_featured_blocks_block_2( $vars );
  
}

/**
 * Who is RAGNO page display at top needs 4 columns, each 3 grids in width.
 */
function _ragno_preprocess_views_view_list_series_type_featured_blocks_block_13( &$vars ){

  // We need exactly the same characteristics of block 2.
  _ragno_preprocess_views_view_list_series_type_featured_blocks_block_2( $vars );
  
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function ragno_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    $frontpage = variable_get('site_frontpage', 'node');


    if($breadcrumb[1] == 'Home') unset($breadcrumb[0]);

    return '<div class="breadcrumb">'. implode(' » ', $breadcrumb) .'</div>';
  }
}
