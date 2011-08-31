<style type="text/css">
	.viewer
            {
                width: 58%;
                height: 377px;
				margin-left: 321px;
				*margin-left: 0px;
				
                border: 1px solid black;
                position: absolute;
            }
            
            .wrapper
            {
                overflow: hidden;
            }
</style>
<div id="node-<?php print $node->nid; ?>" class="<?php print $nodeclasses; ?>">
  <div class="clearfix container_12">
    <div class="Left grid_4">
      <h1><?php print $title; ?></h1>
      <h2><?php //print $node->field_product_code[ 0 ][ 'value' ]; ?></h2>
      <?php print $sizes; ?>
      <h2 class="Subsection"><?php print t( 'Technology' ); ?></h2>
      <?php print $technology; ?>
      <h2 class="Subsection"><?php print t( 'Applications' ); ?></h2>
      <?php print $application; ?>
      <?php if ($featured_icons): ?>
	  		<div id="featured-icons" class="section region"><?php print $featured_icons;?></div>
	  	<?php endif;?>
    </div>
    
	<div class="Right grid_6">
      <?php  print theme( 'imagecache', 'tile_product', $node->field_product_image[ 0 ][ 'filepath' ],  $node->field_product_image[ 0 ][ 'data' ][ 'alt' ],  $node->field_product_image[ 0 ][ 'data' ][ 'title' ] ); ?>
    </div>
	
	

		<div id="viewer" class="viewer"></div>
		
	

	
  </div>
</div>