<?php 
global $proCount;
$proCount++ ;

print l( $fields[ 'field_product_image_fid' ]->content, "node/{$fields[ 'field_product_image_fid' ]->handler->view->result[$proCount - 1]->nid}/lightbox2", array( 'attributes' => array( 'rel' => 'lightframe[|width:767px;height:502px;]', 'title' => '* Images shown with multiple tiles to demonstrate variation in design.' ), 'html' => true ) ); ?>
<span class="tile-title"><?php print $fields[ 'title' ]->content; ?></span>
