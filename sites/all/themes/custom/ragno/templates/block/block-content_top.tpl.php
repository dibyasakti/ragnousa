<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="clear-block block block-<?php print $block->module ?><?php if( $block->grid ){ print " {$block->grid}"; }?>">
  <div class="block_content_wrapper">
  <?php if (!empty($block->subject)): ?>
    <h2><?php print $block->subject ?></h2>
  <?php endif;?>
    <div class="content"><?php print $block->content ?></div>
  </div>
</div>