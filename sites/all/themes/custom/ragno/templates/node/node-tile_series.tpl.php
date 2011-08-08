<div id="node-<?php print $node->nid; ?>" class="<?php print $nodeclasses; ?>">
  <div class="node-content">
        
  	<?php if (!empty($node->content['body']['#value'])): ?>
  		<div class="field field-type-text field-field-description">
                        <?php if(!empty($technology_type)) print "<h3>" . $technology_type . "</h3>"; ?>
  			<?php print $content; ?>
  		</div>
  	<?php endif;?>
  	<?php if ($featured_icons): ?>
  		<div id="featured-icons" class="section region"><?php print $featured_icons;?></div>
  	<?php endif;?>
  	<?php if ( !empty( $node->field_sizes) ): ?>
  		<div class="field field-type-text field-field-subtitle">
                  Field Tile Sizes
  		</div>
  	<?php endif;?>
  	<?php /*if ( !empty( $node->field_subtitle) ): ?>
  		<div class="field field-type-text field-field-subtitle">
  			<?php print $node->field_subtitle[0]['value']; ?>
  		</div>
  	<?php endif;*/?>
	<?php 
	/*	echo "<PRE>";
		print_r($node);
		die();*/
	?>
	
  	<?php if (!empty($node->field_sizes)): ?>
  		<div class="field field-type-text field-field-sizes">
  			<div class="field-items"><?php print $sizes_list; ?></div>
  		</div>
  	<?php endif;?>	
  	<?php if (!empty($node->field_tech_spec)):
			
			if(isset($taxonomy['taxonomy_term_64'])){
				$carePage = "care-maintenance";
			}else{
				$carePage = "care";
			}
			$nodes = node_load($node->field_related_catalog[0]['nid']);	
			
	?>
  		<div class="field field-type-filefield field-field-tech-spec">
  			<div class="field-label"><?php // print_r ($node->content['field_tech_spec']['field']['#title']); ?><a href="<?php print base_path() . $node->field_tech_spec[0]['filepath']; ?>" target="_blank">Series Overview</a></div>
  			<div class="field-items"><div class="filefield-item"><div>Printer Friendly Version</div></div></div>
  		</div>
  	<?php endif;?>   
  	<div class="field field-type-filefield">
  		<div class="field-label"><a href="<?php print base_path() . $nodes->field_catalog_file[0]['filepath']; ?>" target="_blank">catalog</a></div>
		
		<div class="field-items"><div class="filefield-item">View The Product Catalog Online</div></div>
  	</div> 	
  	<div class="field field-type-filefield">
  		<div class="field-label"><a href="<?php print base_path() .$carePage;?>">CARE &amp; MAINTENANCE</a></div>
  		<div class="field-items"><div class="filefield-item">View Care &amp; Maintenance Recommendations</div></div>
  	</div>
  	<div class="field field-type-filefield">
  		<div class="field-label"><a href="<?php print base_path();?>idea-center">Idea Center</a></div>
  		<div class="field-items"><div class="filefield-item">View Room Scenes For Design Ideas</div></div>
  	</div>
  	<div class="field field-type-filefield">
  		<div class="field-label"><a href="<?php print base_path();?>home-owner">Homeowner Collections</a></div>
  		<div class="field-items"><div class="filefield-item">Go Back To Home Owner Collections</div></div>
  	</div>
  	<div class="field field-type-filefield">
  		<div class="field-label"><a href="<?php print base_path();?>professional">Professional Collections</a></div>
  		<div class="field-items"><div class="filefield-item">Go Back To Professional Collections</div></div>
  	</div>
  	<div class="field field-type-filefield field-last">
  		<div class="field-label"><a href="<?php print base_path();?>directory/all">Where to buy</a></div>
  		<div class="field-items"><div class="filefield-item">Find Locations Near You</div></div>
  	</div>
  </div>
</div> 
