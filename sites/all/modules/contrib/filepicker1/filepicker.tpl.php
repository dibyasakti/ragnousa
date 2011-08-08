<?php

/**
 * @file
 * template for filepicker iframe.
 */

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?php echo $head_title ?></title>
  <?php echo $styles ?>
  <?php echo $scripts ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>
<body id="filepicker">
  <div id="main">
    <div class="tabs"><?php echo $tabs ?></div>
    <div id="filep">
      <?php echo $messages ?>
      <?php echo $content; ?>
    </div>
  </div>
</body>
</html>
